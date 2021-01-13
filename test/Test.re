let%expect_test _ = {
  print_endline(
    Graphql_sdl_parser.pp(
      {|
    " single line descript\nion "
    type User implements Character & Admin {
      username: String!
      age: [Int!]!
    }
    """multi 
    line
    description"""
    type Planet
  |},
    ),
  );
  %expect
  {|
    {
      "kind": "document",
      "definitions": [
        {
          "description": {
            "kind": "StringValue",
            "value": " single line descript\nion ",
            "block": false,
            "loc": { "start": 33, "end": 34 }
          },
          "kind": "ObjectTypeDefinition",
          "name": {
            "kind": "Name",
            "value": "User",
            "loc": { "start": 44, "end": 48 }
          },
          "interfaces": [
            {
              "kind": "NamedType",
              "name": {
                "kind": "Name",
                "value": "Character",
                "loc": { "start": 60, "end": 69 }
              },
              "loc": { "start": 60, "end": 69 }
            },
            {
              "kind": "NamedType",
              "name": {
                "kind": "Name",
                "value": "Admin",
                "loc": { "start": 72, "end": 77 }
              },
              "loc": { "start": 72, "end": 77 }
            }
          ],
          "fields": [
            {
              "kind": "FieldDefinition",
              "name": {
                "kind": "Name",
                "value": "username",
                "loc": { "start": 86, "end": 94 }
              },
              "type": {
                "kind": "NonNullType",
                "type": {
                  "kind": "NamedType",
                  "name": {
                    "kind": "Name",
                    "value": "String",
                    "loc": { "start": 96, "end": 102 }
                  },
                  "loc": { "start": 96, "end": 102 }
                },
                "loc": { "start": 96, "end": 103 }
              },
              "loc": { "start": 86, "end": 103 }
            },
            {
              "kind": "FieldDefinition",
              "name": {
                "kind": "Name",
                "value": "age",
                "loc": { "start": 110, "end": 113 }
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
                        "loc": { "start": 116, "end": 119 }
                      },
                      "loc": { "start": 116, "end": 119 }
                    },
                    "loc": { "start": 116, "end": 120 }
                  },
                  "loc": { "start": 115, "end": 121 }
                },
                "loc": { "start": 115, "end": 122 }
              },
              "loc": { "start": 110, "end": 122 }
            }
          ],
          "loc": { "start": 33, "end": 128 }
        },
        {
          "description": {
            "kind": "StringValue",
            "value": "multi \n    line\n    description",
            "block": true,
            "loc": { "start": 167, "end": 170 }
          },
          "kind": "ObjectTypeDefinition",
          "name": {
            "kind": "Name",
            "value": "Planet",
            "loc": { "start": 180, "end": 186 }
          },
          "interfaces": [],
          "fields": [],
          "loc": { "start": 167, "end": 186 }
        }
      ],
      "loc": { "start": 33, "end": 189 }
    }
  |}
};
