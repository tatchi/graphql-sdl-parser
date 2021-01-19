print_endline(
  Graphql_sdl_parser.pp(
    {|type User {
  name(id: String = """he\nl
  lo
  world"""): String
}|},
  ),
);

