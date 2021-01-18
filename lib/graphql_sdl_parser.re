let print_error_position = lexbuf => {
  open Lexing;
  let pos = lexbuf.lex_curr_p;
  Fmt.str(
    "Line:%d Position:%d",
    pos.pos_lnum,
    pos.pos_cnum - pos.pos_bol + 1,
  );
};

let parse_program = lexbuf =>
  try(Graphql_schema_parser.document(Graphql_schema_lexer.read_token, lexbuf)) {
  | Graphql_schema_lexer.SyntaxError(msg) =>
    let error_msg = Fmt.str("%s: %s@.", print_error_position(lexbuf), msg);
    print_endline(error_msg);
    exit(-1);
  | Graphql_schema_parser.Error =>
    let error_msg =
      Fmt.str(
        "%s: syntax error. Token: %s",
        print_error_position(lexbuf),
        Lexing.lexeme(lexbuf),
      );
    print_endline(error_msg);
    exit(-1);
  };

let parse = s => {
  Lexing.from_string(s) |> parse_program;
};

let pp = s => {
  parse(s) |> Ast.toJson |> Yojson.Safe.pretty_to_string;
};

/* This part concerns the table-based parser [UnitActionsParser]. */
module E = MenhirLib.ErrorReports;
module L = MenhirLib.LexerUtil;

module I = Graphql_schema_parser.MenhirInterpreter;

/* [env checkpoint] extracts a parser environment out of a checkpoint,
   which must be of the form [HandlingError env]. */

let env = checkpoint =>
  switch (checkpoint) {
  | I.HandlingError(env) => env
  | _ => assert(false)
  };

/* [state checkpoint] extracts the number of the current state out of a
   checkpoint. */

let state = (checkpoint): int =>
  switch (I.top(env(checkpoint))) {
  | Some([@implicit_arity] I.Element(s, _, _, _)) => I.number(s)
  | None =>
    /* Hmm... The parser is in its initial state. The incremental API
       currently lacks a way of finding out the number of the initial
       state. It is usually 0, so we return 0. This is unsatisfactory
       and should be fixed in the future. */
    0
  };

/* [show text (pos1, pos2)] displays a range of the input text [text]
   delimited by the positions [pos1] and [pos2]. */

let show = (text, positions) =>
  E.extract(text, positions) |> E.sanitize |> E.compress |> E.shorten(20); /* max width 43 */

/* [get text checkpoint i] extracts and shows the range of the input text that
   corresponds to the [i]-th stack cell. The top stack cell is numbered zero. */

let get = (text, checkpoint, i) =>
  switch (I.get(i, env(checkpoint))) {
  | Some([@implicit_arity] I.Element(_, _, pos1, pos2)) =>
    show(text, (pos1, pos2))
  | None =>
    /* The index is out of range. This should not happen if [$i]
       keywords are correctly inside the syntax error message
       database. The integer [i] should always be a valid offset
       into the known suffix of the stack. */
    "???"
  };

/* [succeed v] is invoked when the parser has succeeded and produced a
   semantic value [v]. In our setting, this cannot happen, since the
   table-based parser is invoked only when we know that there is a
   syntax error in the input file. */

let succeed = v => Ast.toJson(v) |> Yojson.Safe.pretty_to_string;

/* [fail text buffer checkpoint] is invoked when parser has encountered a
   syntax error. */

let fail = (text, buffer, checkpoint: I.checkpoint(_)) => {
  /* Indicate where in the input file the error occurred. */
  let location = L.range(E.last(buffer));
  /* Show the tokens just before and just after the error. */
  let indication =
    Printf.sprintf("Syntax error %s.\n", E.show(show(text), buffer));
  /* Fetch an error message from the database. */
  let message = Graphql_sdl_parser_messages.message(state(checkpoint));
  /* Expand away the $i keywords that might appear in the message. */
  let message = E.expand(get(text, checkpoint), message);
  /* Show these three components. */
  Printf.eprintf("%s%s%s%!", location, indication, message);
  exit(1);
};

let parse_with_errors = text => {
  /* Allocate and initialize a lexing buffer. */
  let lexbuf = Lexing.from_string(text);
  /* Wrap the lexer and lexbuf together into a supplier, that is, a
     function of type [unit -> token * position * position]. */
  let supplier =
    I.lexer_lexbuf_to_supplier(Graphql_schema_lexer.read_token, lexbuf);
  /* Equip the supplier with a two-place buffer that records the positions
     of the last two tokens. This is useful when a syntax error occurs, as
     these are the token just before and just after the error. */
  let (buffer, supplier) = E.wrap_supplier(supplier);
  /* Fetch the parser's initial checkpoint. */
  let checkpoint =
    Graphql_schema_parser.Incremental.document(lexbuf.lex_curr_p);
  /* Run the parser. */
  /* We do not handle [Lexer.Error] because we know that we will not
     encounter a lexical error during this second parsing run. */
  I.loop_handle(succeed, fail(text, buffer), supplier, checkpoint);
};
