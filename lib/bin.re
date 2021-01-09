open Graphql_sdl_parser;
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
  try(Parser.document(Lexer.read_token, lexbuf)) {
  | Lexer.SyntaxError(msg) =>
    let error_msg = Fmt.str("%s: %s@.", print_error_position(lexbuf), msg);
    print_endline(error_msg);
    exit(-1);
  | Parser.Error =>
    let error_msg =
      Fmt.str(
        "%s: syntax error. Token: %s",
        print_error_position(lexbuf),
        Lexing.lexeme(lexbuf),
      );
    print_endline(error_msg);
    exit(-1);
  };

let lexbuf = Lexing.from_string({|type User {
  username
}
type Second|});

let ast = parse_program(lexbuf);

let json = Ast.toJson(ast);

print_endline(Yojson.Safe.pretty_to_string(json));
