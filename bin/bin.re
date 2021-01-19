print_endline(
  Graphql_sdl_parser.pp(
    {|type User {
  name(id: String = -1): String
}|},
  ),
);

