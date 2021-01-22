print_endline(
  Graphql_sdl_parser.pp(
    {|#this is a comment
  type User {
  name: String @lol(id: 5)
}|},
  ),
);

