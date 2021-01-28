print_endline(
  Graphql_sdl_parser.pp(
    {|schema @dir(id: 5){
      query: Query
    }|},
  ),
);
