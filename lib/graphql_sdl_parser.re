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
