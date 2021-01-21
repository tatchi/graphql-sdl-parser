print_endline(
  Graphql_sdl_parser.pp(
    {|type User @dir(id: 5) {
  name: String
}|},
  ),
);

