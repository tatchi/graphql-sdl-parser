print_endline(
  Graphql_sdl_parser.pp(
    {|interface Person implements Character @topDir {
  name: String @dir(id: 5)
}|},
  ),
);
