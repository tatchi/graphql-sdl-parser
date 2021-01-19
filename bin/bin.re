print_endline(
  Graphql_sdl_parser.pp(
    {|type User {
  name("argument definition"id: [String!] id2: Int): String!
}|},
  ),
);

