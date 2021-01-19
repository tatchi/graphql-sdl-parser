print_endline(
  Graphql_sdl_parser.pp(
    {|type User {
  name(id: String = lol_cool): String
}|},
  ),
);

