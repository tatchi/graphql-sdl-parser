print_endline(
  Graphql_sdl_parser.pp(
    {|type User @dir(a: 5) {
  name(id: Int @dirMyId(user: "marc") id2: Int): String
}|},
  ),
);

