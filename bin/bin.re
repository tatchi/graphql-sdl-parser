print_endline(
  Graphql_sdl_parser.pp(
    {|enum colors @myDirective(nb: 8) {
	BLACK @dir(id: 4)
  RED
}|},
  ),
);
