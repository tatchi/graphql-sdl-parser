print_endline(
  Graphql_sdl_parser.pp(
    {|"EnumTypeDefinition description"
enum colors {
  	"EnumValueDefinition description"
	BLACK
  RED
}|},
  ),
);
