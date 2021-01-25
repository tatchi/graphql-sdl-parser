print_endline(
  Graphql_sdl_parser.pp(
    {|input ReviewInput @dir(a: 5) {
  stars: Int! = 5
  commentary: String @innerDir
}|},
  ),
);
