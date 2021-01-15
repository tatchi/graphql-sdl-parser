print_endline(
  Graphql_sdl_parser.pp(
    {|"""muli 
line 
com\nment""" type User {"username comment"username: String}|},
  ),
);

