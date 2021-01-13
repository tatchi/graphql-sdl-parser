let%expect_test _ = {
  print_endline(
    Graphql_sdl_parser.pp(
      {|
     "Hello" 
    type User implements Character & Admin {
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
          "interfaces": [
            {
              "kind": "NamedType",
              "name": {
                "kind": "Name",
                "value": "Ville",
                "loc": { "start": 26, "end": 31 }
              },
              "loc": { "start": 26, "end": 31 }
            },
            {
              "kind": "NamedType",
              "name": {
                "kind": "Name",
                "value": "lol",
                "loc": { "start": 34, "end": 37 }
              },
              "loc": { "start": 34, "end": 37 }
            }
          ],
          "fields": [
            {
              "kind": "FieldDefinition",
              "name": {
                "kind": "Name",
                "value": "username",
                "loc": { "start": 46, "end": 54 }
              },
              "type": {
                "kind": "NonNullType",
                "type": {
                  "kind": "NamedType",
                  "name": {
                    "kind": "Name",
                    "value": "String",
                    "loc": { "start": 56, "end": 62 }
                  },
                  "loc": { "start": 56, "end": 62 }
                },
                "loc": { "start": 56, "end": 63 }
              },
              "loc": { "start": 46, "end": 63 }
            },
            {
              "kind": "FieldDefinition",
              "name": {
                "kind": "Name",
                "value": "age",
                "loc": { "start": 70, "end": 73 }
              },
              "type": {
                "kind": "NonNullType",
                "type": {
                  "kind": "ListType",
                  "type": {
                    "kind": "NonNullType",
                    "type": {
                      "kind": "NamedType",
                      "name": {
                        "kind": "Name",
                        "value": "Int",
                        "loc": { "start": 76, "end": 79 }
                      },
                      "loc": { "start": 76, "end": 79 }
                    },
                    "loc": { "start": 76, "end": 80 }
                  },
                  "loc": { "start": 75, "end": 81 }
                },
                "loc": { "start": 75, "end": 82 }
              },
              "loc": { "start": 70, "end": 82 }
            }
          ],
          "loc": { "start": 5, "end": 88 }
        }
      ],
      "loc": { "start": 5, "end": 91 }
    }
  |}
};
