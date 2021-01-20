print_endline(
  Graphql_sdl_parser.pp(
    {|type User @dir, @dir2 @dir3 {
  name: String
}|},
  ),
);

