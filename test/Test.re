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
          name1("input value description" id: String = []): String
          name2(age: Int = [1, 2, [inner], { a: true }]): String
          name3(age: Int = [1, 2, [inner], { a: true, b: { c: inner } }]): String
        }
        type User3 @ dir1(id: "myId", id2: [arr]) @dir2(id: {a: 1 b:2 }), @dir3

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
          "directives": [],
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
          "directives": [],
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
                "value": "name1",
                "loc": { "start": 414, "end": 419 }
              },
              "type": {
                "kind": "NamedType",
                "name": {
                  "kind": "Name",
                  "value": "String",
                  "loc": { "start": 464, "end": 470 }
                },
                "loc": { "start": 464, "end": 470 }
              },
              "arguments": [
                {
                  "description": {
                    "kind": "StringValue",
                    "value": "input value description",
                    "block": false,
                    "loc": { "start": 420, "end": 445 }
                  },
                  "defaultValue": {
                    "kind": "ListValue",
                    "values": [],
                    "loc": { "start": 459, "end": 461 }
                  },
                  "kind": "InputValueDefinition",
                  "name": {
                    "kind": "Name",
                    "value": "id",
                    "loc": { "start": 446, "end": 448 }
                  },
                  "type": {
                    "kind": "NamedType",
                    "name": {
                      "kind": "Name",
                      "value": "String",
                      "loc": { "start": 450, "end": 456 }
                    },
                    "loc": { "start": 450, "end": 456 }
                  },
                  "loc": { "start": 420, "end": 461 }
                }
              ],
              "loc": { "start": 403, "end": 470 }
            },
            {
              "kind": "FieldDefinition",
              "name": {
                "kind": "Name",
                "value": "name2",
                "loc": { "start": 481, "end": 486 }
              },
              "type": {
                "kind": "NamedType",
                "name": {
                  "kind": "Name",
                  "value": "String",
                  "loc": { "start": 529, "end": 535 }
                },
                "loc": { "start": 529, "end": 535 }
              },
              "arguments": [
                {
                  "defaultValue": {
                    "kind": "ListValue",
                    "values": [
                      {
                        "kind": "IntValue",
                        "value": 1,
                        "loc": { "start": 499, "end": 500 }
                      },
                      {
                        "kind": "IntValue",
                        "value": 2,
                        "loc": { "start": 502, "end": 503 }
                      },
                      {
                        "kind": "ListValue",
                        "values": [
                          {
                            "kind": "EnumValue",
                            "value": "inner",
                            "loc": { "start": 506, "end": 511 }
                          }
                        ],
                        "loc": { "start": 505, "end": 512 }
                      },
                      {
                        "ObjectValue": "ObjectField",
                        "fields": [
                          {
                            "kind": "ObjectField",
                            "name": {
                              "kind": "Name",
                              "value": "a",
                              "loc": { "start": 516, "end": 517 }
                            },
                            "value": {
                              "kind": "BooleanValue",
                              "value": true,
                              "loc": { "start": 519, "end": 523 }
                            },
                            "loc": { "start": 516, "end": 523 }
                          }
                        ],
                        "loc": { "start": 514, "end": 525 }
                      }
                    ],
                    "loc": { "start": 498, "end": 526 }
                  },
                  "kind": "InputValueDefinition",
                  "name": {
                    "kind": "Name",
                    "value": "age",
                    "loc": { "start": 487, "end": 490 }
                  },
                  "type": {
                    "kind": "NamedType",
                    "name": {
                      "kind": "Name",
                      "value": "Int",
                      "loc": { "start": 492, "end": 495 }
                    },
                    "loc": { "start": 492, "end": 495 }
                  },
                  "loc": { "start": 487, "end": 526 }
                }
              ],
              "loc": { "start": 470, "end": 535 }
            },
            {
              "kind": "FieldDefinition",
              "name": {
                "kind": "Name",
                "value": "name3",
                "loc": { "start": 546, "end": 551 }
              },
              "type": {
                "kind": "NamedType",
                "name": {
                  "kind": "Name",
                  "value": "String",
                  "loc": { "start": 611, "end": 617 }
                },
                "loc": { "start": 611, "end": 617 }
              },
              "arguments": [
                {
                  "defaultValue": {
                    "kind": "ListValue",
                    "values": [
                      {
                        "kind": "IntValue",
                        "value": 1,
                        "loc": { "start": 564, "end": 565 }
                      },
                      {
                        "kind": "IntValue",
                        "value": 2,
                        "loc": { "start": 567, "end": 568 }
                      },
                      {
                        "kind": "ListValue",
                        "values": [
                          {
                            "kind": "EnumValue",
                            "value": "inner",
                            "loc": { "start": 571, "end": 576 }
                          }
                        ],
                        "loc": { "start": 570, "end": 577 }
                      },
                      {
                        "ObjectValue": "ObjectField",
                        "fields": [
                          {
                            "kind": "ObjectField",
                            "name": {
                              "kind": "Name",
                              "value": "a",
                              "loc": { "start": 581, "end": 582 }
                            },
                            "value": {
                              "kind": "BooleanValue",
                              "value": true,
                              "loc": { "start": 584, "end": 588 }
                            },
                            "loc": { "start": 581, "end": 588 }
                          },
                          {
                            "kind": "ObjectField",
                            "name": {
                              "kind": "Name",
                              "value": "b",
                              "loc": { "start": 590, "end": 591 }
                            },
                            "value": {
                              "ObjectValue": "ObjectField",
                              "fields": [
                                {
                                  "kind": "ObjectField",
                                  "name": {
                                    "kind": "Name",
                                    "value": "c",
                                    "loc": { "start": 595, "end": 596 }
                                  },
                                  "value": {
                                    "kind": "EnumValue",
                                    "value": "inner",
                                    "loc": { "start": 598, "end": 603 }
                                  },
                                  "loc": { "start": 595, "end": 603 }
                                }
                              ],
                              "loc": { "start": 593, "end": 605 }
                            },
                            "loc": { "start": 590, "end": 605 }
                          }
                        ],
                        "loc": { "start": 579, "end": 607 }
                      }
                    ],
                    "loc": { "start": 563, "end": 608 }
                  },
                  "kind": "InputValueDefinition",
                  "name": {
                    "kind": "Name",
                    "value": "age",
                    "loc": { "start": 552, "end": 555 }
                  },
                  "type": {
                    "kind": "NamedType",
                    "name": {
                      "kind": "Name",
                      "value": "Int",
                      "loc": { "start": 557, "end": 560 }
                    },
                    "loc": { "start": 557, "end": 560 }
                  },
                  "loc": { "start": 552, "end": 608 }
                }
              ],
              "loc": { "start": 535, "end": 617 }
            }
          ],
          "directives": [],
          "loc": { "start": 381, "end": 627 }
        },
        {
          "kind": "ObjectTypeDefinition",
          "name": {
            "kind": "Name",
            "value": "User3",
            "loc": { "start": 641, "end": 646 }
          },
          "interfaces": [],
          "fields": [],
          "directives": [
            {
              "kind": "Directive",
              "name": {
                "kind": "Name",
                "value": "dir1",
                "loc": { "start": 649, "end": 653 }
              },
              "arguments": [
                {
                  "kind": "Argument",
                  "name": {
                    "kind": "Name",
                    "value": "id",
                    "loc": { "start": 654, "end": 656 }
                  },
                  "value": {
                    "kind": "StringValue",
                    "value": "myId",
                    "block": false,
                    "loc": { "start": 658, "end": 664 }
                  },
                  "loc": { "start": 654, "end": 664 }
                },
                {
                  "kind": "Argument",
                  "name": {
                    "kind": "Name",
                    "value": "id2",
                    "loc": { "start": 666, "end": 669 }
                  },
                  "value": {
                    "kind": "ListValue",
                    "values": [
                      {
                        "kind": "EnumValue",
                        "value": "arr",
                        "loc": { "start": 672, "end": 675 }
                      }
                    ],
                    "loc": { "start": 671, "end": 676 }
                  },
                  "loc": { "start": 666, "end": 676 }
                }
              ],
              "loc": { "start": 647, "end": 677 }
            },
            {
              "kind": "Directive",
              "name": {
                "kind": "Name",
                "value": "dir2",
                "loc": { "start": 679, "end": 683 }
              },
              "arguments": [
                {
                  "kind": "Argument",
                  "name": {
                    "kind": "Name",
                    "value": "id",
                    "loc": { "start": 684, "end": 686 }
                  },
                  "value": {
                    "ObjectValue": "ObjectField",
                    "fields": [
                      {
                        "kind": "ObjectField",
                        "name": {
                          "kind": "Name",
                          "value": "a",
                          "loc": { "start": 689, "end": 690 }
                        },
                        "value": {
                          "kind": "IntValue",
                          "value": 1,
                          "loc": { "start": 692, "end": 693 }
                        },
                        "loc": { "start": 689, "end": 693 }
                      },
                      {
                        "kind": "ObjectField",
                        "name": {
                          "kind": "Name",
                          "value": "b",
                          "loc": { "start": 694, "end": 695 }
                        },
                        "value": {
                          "kind": "IntValue",
                          "value": 2,
                          "loc": { "start": 696, "end": 697 }
                        },
                        "loc": { "start": 694, "end": 697 }
                      }
                    ],
                    "loc": { "start": 688, "end": 699 }
                  },
                  "loc": { "start": 684, "end": 699 }
                }
              ],
              "loc": { "start": 678, "end": 700 }
            },
            {
              "kind": "Directive",
              "name": {
                "kind": "Name",
                "value": "dir3",
                "loc": { "start": 703, "end": 707 }
              },
              "arguments": [],
              "loc": { "start": 702, "end": 707 }
            }
          ],
          "loc": { "start": 627, "end": 707 }
        }
      ],
      "loc": { "start": 0, "end": 709 }
    }
  |}
};
