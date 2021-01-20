print_endline(
  Graphql_sdl_parser.pp(
    {|type User {
  name("description"id: String = {a: ""b:lol}): String
}|},
  ),
);

