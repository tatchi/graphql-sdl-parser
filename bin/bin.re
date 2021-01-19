print_endline(
  Graphql_sdl_parser.pp(
    {|type User {
  name(id: String = {a: ["coucou"],, b: true,, c:shouldBeEnum}): String
}|},
  ),
);

