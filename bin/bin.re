print_endline(
  Graphql_sdl_parser.pp(
    {|type User {
  name: String @lol(id: 5)
}|},
  ),
);

