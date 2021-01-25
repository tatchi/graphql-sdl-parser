{
open Lexing
open Graphql_schema_parser
exception SyntaxError of string
let next_line lexbuf =
  let pos = lexbuf.lex_curr_p in
  lexbuf.lex_curr_p <-
    { pos with pos_bol = lexbuf.lex_curr_pos;
               pos_lnum = pos.pos_lnum + 1
    }
}

(* Define helper regexes *)
let digit = ['0'-'9']
let alpha = ['a'-'z' 'A'-'Z']
let int = '-'? digit+  (* regex for integers *)
let float = '-'? digit+ '.' digit+
let bool = "true" | "false"
let id = (alpha) (alpha|digit|'_')* (* regex for identifier *)
let whitespace = [' ' ',' '\t']+
let newline = '\r' | '\n' | "\r\n"
let string = "\"[^\"]*\""
let quoted = '"'([^'\n']*)'"'

rule read_token =
  parse
  | whitespace    { read_token lexbuf }
  | newline { next_line lexbuf; read_token lexbuf }
  | int { INT (int_of_string (Lexing.lexeme lexbuf))}
  | float { FLOAT (float_of_string (Lexing.lexeme lexbuf))}
  | bool { BOOL (bool_of_string (Lexing.lexeme lexbuf))}
  | '"' | "\"\"\"" {
    let start_pos = Lexing.lexeme_start_p lexbuf in
    let terminator = Lexing.lexeme lexbuf in
    read_string (Buffer.create 17) terminator start_pos lexbuf
  }
  | "{" { LBRACE }
  | "}" { RBRACE }
  | "[" { LBRACKET }
  | "]" { RBRACKET }
  | '(' { LPAREN }
  | ')' { RPAREN }
  | ":" { COLON }
  | "|" { PIPE }
  | "=" { EQUAL }
  | '@'   { AT }
  | "null" { NULL }
  | "!" { EXCLAMATION_MARK }
  | "type" { TYPE }
  | "interface" { INTERFACE }
  | "union" { UNION }
  | "enum" { ENUM }
  | "scalar" { SCALAR }
  | "implements" { IMPLEMENTS }
  | "input" { INPUT }
  | "&" { AMPERSAND }
  | id { IDENTIFIER (Lexing.lexeme lexbuf) }
  | "#" { read_single_line_comment lexbuf }
  | eof { EOF }
  | _ {raise (SyntaxError ("Lexer - Illegal character: " ^ Lexing.lexeme lexbuf)) }

  and read_single_line_comment = parse
  | newline { next_line lexbuf; read_token lexbuf } 
  | eof { EOF }
  | _ { read_single_line_comment lexbuf }

  and read_string buf terminator start_pos =
  parse
  | "\"\"\"" | '"' {
    lexbuf.lex_start_p <- start_pos;

    let lexeme = Lexing.lexeme lexbuf in

    if lexeme = terminator then
      if terminator = "\"" then
        SINGLE_LINE_STRING (Buffer.contents buf)
      else
        MULTI_LINE_STRING (Buffer.contents buf)
    else
      let _ = Buffer.add_string buf lexeme in
      read_string buf terminator start_pos lexbuf
  }
  | '\\' '/'  { Buffer.add_char buf '/'; read_string buf terminator start_pos lexbuf }
  | '\\' '\\' { Buffer.add_char buf '\\'; read_string buf terminator start_pos lexbuf }
  | '\\' 'b'  { Buffer.add_char buf '\b'; read_string buf terminator start_pos lexbuf }
  | '\\' 'f'  { Buffer.add_char buf '\012'; read_string buf terminator start_pos lexbuf }
  | '\\' 'n'  { Buffer.add_char buf '\n'; read_string buf terminator start_pos lexbuf }
  | '\\' 'r'  { Buffer.add_char buf '\r'; read_string buf terminator start_pos lexbuf }
  | '\\' 't'  { Buffer.add_char buf '\t'; read_string buf terminator start_pos lexbuf }
  | newline { if terminator = "\"" then
                raise (SyntaxError ("String is not terminated"))
              else
                Buffer.add_string buf (Lexing.lexeme lexbuf);
                read_string buf terminator start_pos lexbuf}
  | eof { raise (SyntaxError ("Lexer - Unexpected EOF - please terminate your comment.")) }
  | _  { Buffer.add_string buf (Lexing.lexeme lexbuf);
      read_string buf terminator start_pos lexbuf
    }