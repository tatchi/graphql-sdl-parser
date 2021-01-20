print_endline(
  Graphql_sdl_parser.pp(
    {|type User @ dir(id: 1 id2: 2) {
  name: String
}|},
  ),
);

