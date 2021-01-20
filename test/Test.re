let%expect_test _ = {
  print_endline(
    Graphql_sdl_parser.pp(
      {|" single line descript\nion "
        type User implements Character & Admin {
          "field description"
          username: String!
          age: [Int!]!
          name("argument description" id: [String!], id2: Int): String!
          city(id: [String!], id2: Int): String!
        }
        """
        multi
        line
        description
        """
        type Planet

        type User2 {
          name("input value description"id: String = []): String
          name(age: Int = [1, 2, [inner], { a: true }]): String
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
          "description": {
            "kind": "StringValue",
            "value": " single line descript\nion ",
            "block": false,
            "loc": { "start": 0, "end": 29 }
          },
          "kind": "ObjectTypeDefinition",
          "name": {
            "kind": "Name",
            "value": "User",
            "loc": { "start": 43, "end": 47 }
          },
          "interfaces": [
            {
              "kind": "NamedType",
              "name": {
                "kind": "Name",
                "value": "Character",
                "loc": { "start": 59, "end": 68 }
              },
              "loc": { "start": 59, "end": 68 }
            },
            {
              "kind": "NamedType",
              "name": {
                "kind": "Name",
                "value": "Admin",
                "loc": { "start": 71, "end": 76 }
              },
              "loc": { "start": 71, "end": 76 }
            }
          ],
          "fields": [
            {
              "description": {
                "kind": "StringValue",
                "value": "field description",
                "block": false,
                "loc": { "start": 89, "end": 108 }
              },
              "kind": "FieldDefinition",
              "name": {
                "kind": "Name",
                "value": "username",
                "loc": { "start": 119, "end": 127 }
              },
              "type": {
                "kind": "NonNullType",
                "type": {
                  "kind": "NamedType",
                  "name": {
                    "kind": "Name",
                    "value": "String",
                    "loc": { "start": 129, "end": 135 }
                  },
                  "loc": { "start": 129, "end": 135 }
                },
                "loc": { "start": 129, "end": 136 }
              },
              "arguments": [],
              "loc": { "start": 89, "end": 136 }
            },
            {
              "kind": "FieldDefinition",
              "name": {
                "kind": "Name",
                "value": "age",
                "loc": { "start": 147, "end": 150 }
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
                        "loc": { "start": 153, "end": 156 }
                      },
                      "loc": { "start": 153, "end": 156 }
                    },
                    "loc": { "start": 153, "end": 157 }
                  },
                  "loc": { "start": 152, "end": 158 }
                },
                "loc": { "start": 152, "end": 159 }
              },
              "arguments": [],
              "loc": { "start": 136, "end": 159 }
            },
            {
              "kind": "FieldDefinition",
              "name": {
                "kind": "Name",
                "value": "name",
                "loc": { "start": 170, "end": 174 }
              },
              "type": {
                "kind": "NonNullType",
                "type": {
                  "kind": "NamedType",
                  "name": {
                    "kind": "Name",
                    "value": "String",
                    "loc": { "start": 224, "end": 230 }
                  },
                  "loc": { "start": 224, "end": 230 }
                },
                "loc": { "start": 224, "end": 231 }
              },
              "arguments": [
                {
                  "description": {
                    "kind": "StringValue",
                    "value": "argument description",
                    "block": false,
                    "loc": { "start": 175, "end": 197 }
                  },
                  "kind": "InputValueDefinition",
                  "name": {
                    "kind": "Name",
                    "value": "id",
                    "loc": { "start": 198, "end": 200 }
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
                          "loc": { "start": 203, "end": 209 }
                        },
                        "loc": { "start": 203, "end": 209 }
                      },
                      "loc": { "start": 203, "end": 210 }
                    },
                    "loc": { "start": 202, "end": 211 }
                  },
                  "loc": { "start": 175, "end": 211 }
                },
                {
                  "kind": "InputValueDefinition",
                  "name": {
                    "kind": "Name",
                    "value": "id2",
                    "loc": { "start": 213, "end": 216 }
                  },
                  "type": {
                    "kind": "NamedType",
                    "name": {
                      "kind": "Name",
                      "value": "Int",
                      "loc": { "start": 218, "end": 221 }
                    },
                    "loc": { "start": 218, "end": 221 }
                  },
                  "loc": { "start": 212, "end": 221 }
                }
              ],
              "loc": { "start": 159, "end": 231 }
            },
            {
              "kind": "FieldDefinition",
              "name": {
                "kind": "Name",
                "value": "city",
                "loc": { "start": 242, "end": 246 }
              },
              "type": {
                "kind": "NonNullType",
                "type": {
                  "kind": "NamedType",
                  "name": {
                    "kind": "Name",
                    "value": "String",
                    "loc": { "start": 273, "end": 279 }
                  },
                  "loc": { "start": 273, "end": 279 }
                },
                "loc": { "start": 273, "end": 280 }
              },
              "arguments": [
                {
                  "kind": "InputValueDefinition",
                  "name": {
                    "kind": "Name",
                    "value": "id",
                    "loc": { "start": 247, "end": 249 }
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
                          "loc": { "start": 252, "end": 258 }
                        },
                        "loc": { "start": 252, "end": 258 }
                      },
                      "loc": { "start": 252, "end": 259 }
                    },
                    "loc": { "start": 251, "end": 260 }
                  },
                  "loc": { "start": 247, "end": 260 }
                },
                {
                  "kind": "InputValueDefinition",
                  "name": {
                    "kind": "Name",
                    "value": "id2",
                    "loc": { "start": 262, "end": 265 }
                  },
                  "type": {
                    "kind": "NamedType",
                    "name": {
                      "kind": "Name",
                      "value": "Int",
                      "loc": { "start": 267, "end": 270 }
                    },
                    "loc": { "start": 267, "end": 270 }
                  },
                  "loc": { "start": 261, "end": 270 }
                }
              ],
              "loc": { "start": 231, "end": 280 }
            }
          ],
          "loc": { "start": 0, "end": 290 }
        },
        {
          "description": {
            "kind": "StringValue",
            "value":
              "\n        multi\n        line\n        description\n        ",
            "block": true,
            "loc": { "start": 299, "end": 361 }
          },
          "kind": "ObjectTypeDefinition",
          "name": {
            "kind": "Name",
            "value": "Planet",
            "loc": { "start": 375, "end": 381 }
          },
          "interfaces": [],
          "fields": [],
          "loc": { "start": 299, "end": 381 }
        },
        {
          "kind": "ObjectTypeDefinition",
          "name": {
            "kind": "Name",
            "value": "User2",
            "loc": { "start": 396, "end": 401 }
          },
          "interfaces": [],
          "fields": [
            {
              "kind": "FieldDefinition",
              "name": {
                "kind": "Name",
                "value": "name",
                "loc": { "start": 414, "end": 418 }
              },
              "type": {
                "kind": "NamedType",
                "name": {
                  "kind": "Name",
                  "value": "String",
                  "loc": { "start": 462, "end": 468 }
                },
                "loc": { "start": 462, "end": 468 }
              },
              "arguments": [
                {
                  "description": {
                    "kind": "StringValue",
                    "value": "input value description",
                    "block": false,
                    "loc": { "start": 419, "end": 444 }
                  },
                  "defaultValue": {
                    "kind": "ListValue",
                    "values": [],
                    "loc": { "start": 457, "end": 459 }
                  },
                  "kind": "InputValueDefinition",
                  "name": {
                    "kind": "Name",
                    "value": "id",
                    "loc": { "start": 444, "end": 446 }
                  },
                  "type": {
                    "kind": "NamedType",
                    "name": {
                      "kind": "Name",
                      "value": "String",
                      "loc": { "start": 448, "end": 454 }
                    },
                    "loc": { "start": 448, "end": 454 }
                  },
                  "loc": { "start": 419, "end": 459 }
                }
              ],
              "loc": { "start": 403, "end": 468 }
            },
            {
              "kind": "FieldDefinition",
              "name": {
                "kind": "Name",
                "value": "name",
                "loc": { "start": 479, "end": 483 }
              },
              "type": {
                "kind": "NamedType",
                "name": {
                  "kind": "Name",
                  "value": "String",
                  "loc": { "start": 526, "end": 532 }
                },
                "loc": { "start": 526, "end": 532 }
              },
              "arguments": [
                {
                  "defaultValue": {
                    "kind": "ListValue",
                    "values": [
                      {
                        "kind": "IntValue",
                        "value": 1,
                        "loc": { "start": 496, "end": 497 }
                      },
                      {
                        "kind": "IntValue",
                        "value": 2,
                        "loc": { "start": 499, "end": 500 }
                      },
                      {
                        "kind": "ListValue",
                        "values": [
                          {
                            "kind": "EnumValue",
                            "value": "inner",
                            "loc": { "start": 503, "end": 508 }
                          }
                        ],
                        "loc": { "start": 502, "end": 509 }
                      },
                      {
                        "ObjectValue": "ObjectField",
                        "fields": [
                          {
                            "kind": "ObjectField",
                            "name": {
                              "kind": "Name",
                              "value": "a",
                              "loc": { "start": 513, "end": 514 }
                            },
                            "value": {
                              "kind": "BooleanValue",
                              "value": true,
                              "loc": { "start": 516, "end": 520 }
                            },
                            "loc": { "start": 513, "end": 520 }
                          }
                        ],
                        "loc": { "start": 511, "end": 522 }
                      }
                    ],
                    "loc": { "start": 495, "end": 523 }
                  },
                  "kind": "InputValueDefinition",
                  "name": {
                    "kind": "Name",
                    "value": "age",
                    "loc": { "start": 484, "end": 487 }
                  },
                  "type": {
                    "kind": "NamedType",
                    "name": {
                      "kind": "Name",
                      "value": "Int",
                      "loc": { "start": 489, "end": 492 }
                    },
                    "loc": { "start": 489, "end": 492 }
                  },
                  "loc": { "start": 484, "end": 523 }
                }
              ],
              "loc": { "start": 468, "end": 532 }
            }
          ],
          "loc": { "start": 381, "end": 542 }
        }
      ],
      "loc": { "start": 0, "end": 543 }
    }
  |}
};
