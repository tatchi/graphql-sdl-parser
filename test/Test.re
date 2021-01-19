let%expect_test _ = {
  print_endline(
    Graphql_sdl_parser.pp(
      {|
    " single line descript\nion "
    type User implements Character & Admin {
      "field description"
      username: String!
      age: [Int!]!
      name("argument description"id: [String!] id2: Int): String!
      city(id: [String!],, id2: Int): String!
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
            "loc": { "start": 5, "end": 34 }
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
              "description": {
                "kind": "StringValue",
                "value": "field description",
                "block": false,
                "loc": { "start": 86, "end": 105 }
              },
              "kind": "FieldDefinition",
              "name": {
                "kind": "Name",
                "value": "username",
                "loc": { "start": 112, "end": 120 }
              },
              "type": {
                "kind": "NonNullType",
                "type": {
                  "kind": "NamedType",
                  "name": {
                    "kind": "Name",
                    "value": "String",
                    "loc": { "start": 122, "end": 128 }
                  },
                  "loc": { "start": 122, "end": 128 }
                },
                "loc": { "start": 122, "end": 129 }
              },
              "arguments": [],
              "loc": { "start": 86, "end": 129 }
            },
            {
              "kind": "FieldDefinition",
              "name": {
                "kind": "Name",
                "value": "age",
                "loc": { "start": 136, "end": 139 }
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
                        "loc": { "start": 142, "end": 145 }
                      },
                      "loc": { "start": 142, "end": 145 }
                    },
                    "loc": { "start": 142, "end": 146 }
                  },
                  "loc": { "start": 141, "end": 147 }
                },
                "loc": { "start": 141, "end": 148 }
              },
              "arguments": [],
              "loc": { "start": 129, "end": 148 }
            },
            {
              "kind": "FieldDefinition",
              "name": {
                "kind": "Name",
                "value": "name",
                "loc": { "start": 155, "end": 159 }
              },
              "type": {
                "kind": "NonNullType",
                "type": {
                  "kind": "NamedType",
                  "name": {
                    "kind": "Name",
                    "value": "String",
                    "loc": { "start": 207, "end": 213 }
                  },
                  "loc": { "start": 207, "end": 213 }
                },
                "loc": { "start": 207, "end": 214 }
              },
              "arguments": [
                {
                  "description": {
                    "kind": "StringValue",
                    "value": "argument description",
                    "block": false,
                    "loc": { "start": 160, "end": 182 }
                  },
                  "kind": "InputValueDefinition",
                  "name": {
                    "kind": "Name",
                    "value": "id",
                    "loc": { "start": 182, "end": 184 }
                  },
                  "type": {
                    "kind": "ListType",
                    "type": {
                      "kind": "NonNullType",
                      "type": {
                        "kind": "NamedType",
                        "name": {
                          "kind": "Name",
                          "value": "String",
                          "loc": { "start": 187, "end": 193 }
                        },
                        "loc": { "start": 187, "end": 193 }
                      },
                      "loc": { "start": 187, "end": 194 }
                    },
                    "loc": { "start": 186, "end": 195 }
                  },
                  "loc": { "start": 160, "end": 195 }
                },
                {
                  "kind": "InputValueDefinition",
                  "name": {
                    "kind": "Name",
                    "value": "id2",
                    "loc": { "start": 196, "end": 199 }
                  },
                  "type": {
                    "kind": "NamedType",
                    "name": {
                      "kind": "Name",
                      "value": "Int",
                      "loc": { "start": 201, "end": 204 }
                    },
                    "loc": { "start": 201, "end": 204 }
                  },
                  "loc": { "start": 195, "end": 204 }
                }
              ],
              "loc": { "start": 148, "end": 214 }
            },
            {
              "kind": "FieldDefinition",
              "name": {
                "kind": "Name",
                "value": "city",
                "loc": { "start": 221, "end": 225 }
              },
              "type": {
                "kind": "NonNullType",
                "type": {
                  "kind": "NamedType",
                  "name": {
                    "kind": "Name",
                    "value": "String",
                    "loc": { "start": 253, "end": 259 }
                  },
                  "loc": { "start": 253, "end": 259 }
                },
                "loc": { "start": 253, "end": 260 }
              },
              "arguments": [
                {
                  "kind": "InputValueDefinition",
                  "name": {
                    "kind": "Name",
                    "value": "id",
                    "loc": { "start": 226, "end": 228 }
                  },
                  "type": {
                    "kind": "ListType",
                    "type": {
                      "kind": "NonNullType",
                      "type": {
                        "kind": "NamedType",
                        "name": {
                          "kind": "Name",
                          "value": "String",
                          "loc": { "start": 231, "end": 237 }
                        },
                        "loc": { "start": 231, "end": 237 }
                      },
                      "loc": { "start": 231, "end": 238 }
                    },
                    "loc": { "start": 230, "end": 239 }
                  },
                  "loc": { "start": 226, "end": 239 }
                },
                {
                  "kind": "InputValueDefinition",
                  "name": {
                    "kind": "Name",
                    "value": "id2",
                    "loc": { "start": 242, "end": 245 }
                  },
                  "type": {
                    "kind": "NamedType",
                    "name": {
                      "kind": "Name",
                      "value": "Int",
                      "loc": { "start": 247, "end": 250 }
                    },
                    "loc": { "start": 247, "end": 250 }
                  },
                  "loc": { "start": 241, "end": 250 }
                }
              ],
              "loc": { "start": 214, "end": 260 }
            }
          ],
          "loc": { "start": 5, "end": 266 }
        },
        {
          "description": {
            "kind": "StringValue",
            "value": "multi \n    line\n    description",
            "block": true,
            "loc": { "start": 271, "end": 308 }
          },
          "kind": "ObjectTypeDefinition",
          "name": {
            "kind": "Name",
            "value": "Planet",
            "loc": { "start": 318, "end": 324 }
          },
          "interfaces": [],
          "fields": [],
          "loc": { "start": 271, "end": 324 }
        }
      ],
      "loc": { "start": 5, "end": 327 }
    }
  |}
};
