print_endline(
  Graphql_sdl_parser.pp(
    {|directive @skip(if: Boolean!) on FIELD | FRAGMENT_SPREAD | INLINE_FRAGMENT|},
  ),
);
