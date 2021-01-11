let%expect_test _ = {
  print_endline(
    Graphql_sdl_parser.pp(
      {|
    type User {
      username: String!
      age: [Int!]!
    }
  |},
    ),
  );
  %expect
  {|
    {
      "kind": "document",
      "definitions": [
        {
          "kind": "ObjectTypeDefinition",
          "name": {
            "kind": "Name",
            "value": "User",
            "loc": { "start": 10, "end": 14 }
          },
          "fields": [
            {
              "kind": "FieldDefinition",
              "name": {
                "kind": "Name",
                "value": "username",
                "loc": { "start": 23, "end": 31 }
              },
              "type": {
                "kind": "NonNullType",
                "type": {
                  "kind": "NamedType",
                  "name": {
                    "kind": "Name",
                    "value": "String",
                    "loc": { "start": 33, "end": 39 }
                  },
                  "loc": { "start": 33, "end": 39 }
                },
                "loc": { "start": 33, "end": 40 }
              },
              "loc": { "start": 23, "end": 40 }
            }
          ],
          "loc": { "start": 5, "end": 46 }
        }
      ],
      "loc": { "start": 5, "end": 49 }
    }
  |}
};
