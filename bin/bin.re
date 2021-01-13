print_endline(
  Graphql_sdl_parser.pp(
    {|
   " my descript\nion "
    type User {
      username: String
    }
  |},
  ),
);
