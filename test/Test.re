let%expect_test _ = {
  print_endline(
    Graphql_sdl_parser.pp(
      {|" single line descript\nion "
        type User implements Character & Admin {
          "field description"
          username: String!
          age: #comment in the middle
          [Int!]!
          name("argument description" id: [String!], id2: Int): String!
          city(id: [String!], id2: Int): String!
        }
        """
        multi
        line
        description
        """
        type Planet
        # this is a comment
        type User2 {
          name1("input value description" id: String = []): String
          #another comment here
          name2(age: Int = [1, 2, [inner], { a: true }]): String
          name3(age: Int = [1, 2, [inner], { a: true, b: { c: inner } }]): String
        }
        type User3 @dir1(id: "myId", id2: [arr]) @dir2(id: { a: 1, b: 2 }) @dir3 {
          name(id: Int @idDirective(user: "Marc"), id2: Int @dir2, id3: Int): String
        }
        type User4 {
          name: String @dir(id: 6)
        }

        "EnumTypeDefinition description"
        enum colors @myDirective(count: 6) {
          "EnumValueDefinition description"
          BLACK @dir(id: "xjs")
          RED
        }

        interface Person implements Character @topDir {
          name: String @dir(id: 5)
        }

        union SearchResult @dir(a:6) = A | B




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
              "directives": [],
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
                        "loc": { "start": 186, "end": 189 }
                      },
                      "loc": { "start": 186, "end": 189 }
                    },
                    "loc": { "start": 186, "end": 190 }
                  },
                  "loc": { "start": 185, "end": 191 }
                },
                "loc": { "start": 185, "end": 192 }
              },
              "arguments": [],
              "directives": [],
              "loc": { "start": 136, "end": 192 }
            },
            {
              "kind": "FieldDefinition",
              "name": {
                "kind": "Name",
                "value": "name",
                "loc": { "start": 203, "end": 207 }
              },
              "type": {
                "kind": "NonNullType",
                "type": {
                  "kind": "NamedType",
                  "name": {
                    "kind": "Name",
                    "value": "String",
                    "loc": { "start": 257, "end": 263 }
                  },
                  "loc": { "start": 257, "end": 263 }
                },
                "loc": { "start": 257, "end": 264 }
              },
              "arguments": [
                {
                  "description": {
                    "kind": "StringValue",
                    "value": "argument description",
                    "block": false,
                    "loc": { "start": 208, "end": 230 }
                  },
                  "kind": "InputValueDefinition",
                  "name": {
                    "kind": "Name",
                    "value": "id",
                    "loc": { "start": 231, "end": 233 }
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
                          "loc": { "start": 236, "end": 242 }
                        },
                        "loc": { "start": 236, "end": 242 }
                      },
                      "loc": { "start": 236, "end": 243 }
                    },
                    "loc": { "start": 235, "end": 244 }
                  },
                  "directives": [],
                  "loc": { "start": 208, "end": 244 }
                },
                {
                  "kind": "InputValueDefinition",
                  "name": {
                    "kind": "Name",
                    "value": "id2",
                    "loc": { "start": 246, "end": 249 }
                  },
                  "type": {
                    "kind": "NamedType",
                    "name": {
                      "kind": "Name",
                      "value": "Int",
                      "loc": { "start": 251, "end": 254 }
                    },
                    "loc": { "start": 251, "end": 254 }
                  },
                  "directives": [],
                  "loc": { "start": 244, "end": 254 }
                }
              ],
              "directives": [],
              "loc": { "start": 192, "end": 264 }
            },
            {
              "kind": "FieldDefinition",
              "name": {
                "kind": "Name",
                "value": "city",
                "loc": { "start": 275, "end": 279 }
              },
              "type": {
                "kind": "NonNullType",
                "type": {
                  "kind": "NamedType",
                  "name": {
                    "kind": "Name",
                    "value": "String",
                    "loc": { "start": 306, "end": 312 }
                  },
                  "loc": { "start": 306, "end": 312 }
                },
                "loc": { "start": 306, "end": 313 }
              },
              "arguments": [
                {
                  "kind": "InputValueDefinition",
                  "name": {
                    "kind": "Name",
                    "value": "id",
                    "loc": { "start": 280, "end": 282 }
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
                          "loc": { "start": 285, "end": 291 }
                        },
                        "loc": { "start": 285, "end": 291 }
                      },
                      "loc": { "start": 285, "end": 292 }
                    },
                    "loc": { "start": 284, "end": 293 }
                  },
                  "directives": [],
                  "loc": { "start": 280, "end": 293 }
                },
                {
                  "kind": "InputValueDefinition",
                  "name": {
                    "kind": "Name",
                    "value": "id2",
                    "loc": { "start": 295, "end": 298 }
                  },
                  "type": {
                    "kind": "NamedType",
                    "name": {
                      "kind": "Name",
                      "value": "Int",
                      "loc": { "start": 300, "end": 303 }
                    },
                    "loc": { "start": 300, "end": 303 }
                  },
                  "directives": [],
                  "loc": { "start": 293, "end": 303 }
                }
              ],
              "directives": [],
              "loc": { "start": 264, "end": 313 }
            }
          ],
          "directives": [],
          "loc": { "start": 0, "end": 323 }
        },
        {
          "description": {
            "kind": "StringValue",
            "value":
              "\n        multi\n        line\n        description\n        ",
            "block": true,
            "loc": { "start": 332, "end": 394 }
          },
          "kind": "ObjectTypeDefinition",
          "name": {
            "kind": "Name",
            "value": "Planet",
            "loc": { "start": 408, "end": 414 }
          },
          "interfaces": [],
          "fields": [],
          "directives": [],
          "loc": { "start": 332, "end": 414 }
        },
        {
          "kind": "ObjectTypeDefinition",
          "name": {
            "kind": "Name",
            "value": "User2",
            "loc": { "start": 456, "end": 461 }
          },
          "interfaces": [],
          "fields": [
            {
              "kind": "FieldDefinition",
              "name": {
                "kind": "Name",
                "value": "name1",
                "loc": { "start": 474, "end": 479 }
              },
              "type": {
                "kind": "NamedType",
                "name": {
                  "kind": "Name",
                  "value": "String",
                  "loc": { "start": 524, "end": 530 }
                },
                "loc": { "start": 524, "end": 530 }
              },
              "arguments": [
                {
                  "description": {
                    "kind": "StringValue",
                    "value": "input value description",
                    "block": false,
                    "loc": { "start": 480, "end": 505 }
                  },
                  "defaultValue": {
                    "kind": "ListValue",
                    "values": [],
                    "loc": { "start": 519, "end": 521 }
                  },
                  "kind": "InputValueDefinition",
                  "name": {
                    "kind": "Name",
                    "value": "id",
                    "loc": { "start": 506, "end": 508 }
                  },
                  "type": {
                    "kind": "NamedType",
                    "name": {
                      "kind": "Name",
                      "value": "String",
                      "loc": { "start": 510, "end": 516 }
                    },
                    "loc": { "start": 510, "end": 516 }
                  },
                  "directives": [],
                  "loc": { "start": 480, "end": 521 }
                }
              ],
              "directives": [],
              "loc": { "start": 463, "end": 530 }
            },
            {
              "kind": "FieldDefinition",
              "name": {
                "kind": "Name",
                "value": "name2",
                "loc": { "start": 573, "end": 578 }
              },
              "type": {
                "kind": "NamedType",
                "name": {
                  "kind": "Name",
                  "value": "String",
                  "loc": { "start": 621, "end": 627 }
                },
                "loc": { "start": 621, "end": 627 }
              },
              "arguments": [
                {
                  "defaultValue": {
                    "kind": "ListValue",
                    "values": [
                      {
                        "kind": "IntValue",
                        "value": 1,
                        "loc": { "start": 591, "end": 592 }
                      },
                      {
                        "kind": "IntValue",
                        "value": 2,
                        "loc": { "start": 594, "end": 595 }
                      },
                      {
                        "kind": "ListValue",
                        "values": [
                          {
                            "kind": "EnumValue",
                            "value": "inner",
                            "loc": { "start": 598, "end": 603 }
                          }
                        ],
                        "loc": { "start": 597, "end": 604 }
                      },
                      {
                        "ObjectValue": "ObjectField",
                        "fields": [
                          {
                            "kind": "ObjectField",
                            "name": {
                              "kind": "Name",
                              "value": "a",
                              "loc": { "start": 608, "end": 609 }
                            },
                            "value": {
                              "kind": "BooleanValue",
                              "value": true,
                              "loc": { "start": 611, "end": 615 }
                            },
                            "loc": { "start": 608, "end": 615 }
                          }
                        ],
                        "loc": { "start": 606, "end": 617 }
                      }
                    ],
                    "loc": { "start": 590, "end": 618 }
                  },
                  "kind": "InputValueDefinition",
                  "name": {
                    "kind": "Name",
                    "value": "age",
                    "loc": { "start": 579, "end": 582 }
                  },
                  "type": {
                    "kind": "NamedType",
                    "name": {
                      "kind": "Name",
                      "value": "Int",
                      "loc": { "start": 584, "end": 587 }
                    },
                    "loc": { "start": 584, "end": 587 }
                  },
                  "directives": [],
                  "loc": { "start": 579, "end": 618 }
                }
              ],
              "directives": [],
              "loc": { "start": 530, "end": 627 }
            },
            {
              "kind": "FieldDefinition",
              "name": {
                "kind": "Name",
                "value": "name3",
                "loc": { "start": 638, "end": 643 }
              },
              "type": {
                "kind": "NamedType",
                "name": {
                  "kind": "Name",
                  "value": "String",
                  "loc": { "start": 703, "end": 709 }
                },
                "loc": { "start": 703, "end": 709 }
              },
              "arguments": [
                {
                  "defaultValue": {
                    "kind": "ListValue",
                    "values": [
                      {
                        "kind": "IntValue",
                        "value": 1,
                        "loc": { "start": 656, "end": 657 }
                      },
                      {
                        "kind": "IntValue",
                        "value": 2,
                        "loc": { "start": 659, "end": 660 }
                      },
                      {
                        "kind": "ListValue",
                        "values": [
                          {
                            "kind": "EnumValue",
                            "value": "inner",
                            "loc": { "start": 663, "end": 668 }
                          }
                        ],
                        "loc": { "start": 662, "end": 669 }
                      },
                      {
                        "ObjectValue": "ObjectField",
                        "fields": [
                          {
                            "kind": "ObjectField",
                            "name": {
                              "kind": "Name",
                              "value": "a",
                              "loc": { "start": 673, "end": 674 }
                            },
                            "value": {
                              "kind": "BooleanValue",
                              "value": true,
                              "loc": { "start": 676, "end": 680 }
                            },
                            "loc": { "start": 673, "end": 680 }
                          },
                          {
                            "kind": "ObjectField",
                            "name": {
                              "kind": "Name",
                              "value": "b",
                              "loc": { "start": 682, "end": 683 }
                            },
                            "value": {
                              "ObjectValue": "ObjectField",
                              "fields": [
                                {
                                  "kind": "ObjectField",
                                  "name": {
                                    "kind": "Name",
                                    "value": "c",
                                    "loc": { "start": 687, "end": 688 }
                                  },
                                  "value": {
                                    "kind": "EnumValue",
                                    "value": "inner",
                                    "loc": { "start": 690, "end": 695 }
                                  },
                                  "loc": { "start": 687, "end": 695 }
                                }
                              ],
                              "loc": { "start": 685, "end": 697 }
                            },
                            "loc": { "start": 682, "end": 697 }
                          }
                        ],
                        "loc": { "start": 671, "end": 699 }
                      }
                    ],
                    "loc": { "start": 655, "end": 700 }
                  },
                  "kind": "InputValueDefinition",
                  "name": {
                    "kind": "Name",
                    "value": "age",
                    "loc": { "start": 644, "end": 647 }
                  },
                  "type": {
                    "kind": "NamedType",
                    "name": {
                      "kind": "Name",
                      "value": "Int",
                      "loc": { "start": 649, "end": 652 }
                    },
                    "loc": { "start": 649, "end": 652 }
                  },
                  "directives": [],
                  "loc": { "start": 644, "end": 700 }
                }
              ],
              "directives": [],
              "loc": { "start": 627, "end": 709 }
            }
          ],
          "directives": [],
          "loc": { "start": 414, "end": 719 }
        },
        {
          "kind": "ObjectTypeDefinition",
          "name": {
            "kind": "Name",
            "value": "User3",
            "loc": { "start": 733, "end": 738 }
          },
          "interfaces": [],
          "fields": [
            {
              "kind": "FieldDefinition",
              "name": {
                "kind": "Name",
                "value": "name",
                "loc": { "start": 813, "end": 817 }
              },
              "type": {
                "kind": "NamedType",
                "name": {
                  "kind": "Name",
                  "value": "String",
                  "loc": { "start": 881, "end": 887 }
                },
                "loc": { "start": 881, "end": 887 }
              },
              "arguments": [
                {
                  "kind": "InputValueDefinition",
                  "name": {
                    "kind": "Name",
                    "value": "id",
                    "loc": { "start": 818, "end": 820 }
                  },
                  "type": {
                    "kind": "NamedType",
                    "name": {
                      "kind": "Name",
                      "value": "Int",
                      "loc": { "start": 822, "end": 825 }
                    },
                    "loc": { "start": 822, "end": 825 }
                  },
                  "directives": [
                    {
                      "kind": "Directive",
                      "name": {
                        "kind": "Name",
                        "value": "idDirective",
                        "loc": { "start": 827, "end": 838 }
                      },
                      "arguments": [
                        {
                          "kind": "Argument",
                          "name": {
                            "kind": "Name",
                            "value": "user",
                            "loc": { "start": 839, "end": 843 }
                          },
                          "value": {
                            "kind": "StringValue",
                            "value": "Marc",
                            "block": false,
                            "loc": { "start": 845, "end": 851 }
                          },
                          "loc": { "start": 839, "end": 851 }
                        }
                      ],
                      "loc": { "start": 826, "end": 852 }
                    }
                  ],
                  "loc": { "start": 818, "end": 852 }
                },
                {
                  "kind": "InputValueDefinition",
                  "name": {
                    "kind": "Name",
                    "value": "id2",
                    "loc": { "start": 854, "end": 857 }
                  },
                  "type": {
                    "kind": "NamedType",
                    "name": {
                      "kind": "Name",
                      "value": "Int",
                      "loc": { "start": 859, "end": 862 }
                    },
                    "loc": { "start": 859, "end": 862 }
                  },
                  "directives": [
                    {
                      "kind": "Directive",
                      "name": {
                        "kind": "Name",
                        "value": "dir2",
                        "loc": { "start": 864, "end": 868 }
                      },
                      "arguments": [],
                      "loc": { "start": 863, "end": 868 }
                    }
                  ],
                  "loc": { "start": 852, "end": 868 }
                },
                {
                  "kind": "InputValueDefinition",
                  "name": {
                    "kind": "Name",
                    "value": "id3",
                    "loc": { "start": 870, "end": 873 }
                  },
                  "type": {
                    "kind": "NamedType",
                    "name": {
                      "kind": "Name",
                      "value": "Int",
                      "loc": { "start": 875, "end": 878 }
                    },
                    "loc": { "start": 875, "end": 878 }
                  },
                  "directives": [],
                  "loc": { "start": 868, "end": 878 }
                }
              ],
              "directives": [],
              "loc": { "start": 802, "end": 887 }
            }
          ],
          "directives": [
            {
              "kind": "Directive",
              "name": {
                "kind": "Name",
                "value": "dir1",
                "loc": { "start": 740, "end": 744 }
              },
              "arguments": [
                {
                  "kind": "Argument",
                  "name": {
                    "kind": "Name",
                    "value": "id",
                    "loc": { "start": 745, "end": 747 }
                  },
                  "value": {
                    "kind": "StringValue",
                    "value": "myId",
                    "block": false,
                    "loc": { "start": 749, "end": 755 }
                  },
                  "loc": { "start": 745, "end": 755 }
                },
                {
                  "kind": "Argument",
                  "name": {
                    "kind": "Name",
                    "value": "id2",
                    "loc": { "start": 757, "end": 760 }
                  },
                  "value": {
                    "kind": "ListValue",
                    "values": [
                      {
                        "kind": "EnumValue",
                        "value": "arr",
                        "loc": { "start": 763, "end": 766 }
                      }
                    ],
                    "loc": { "start": 762, "end": 767 }
                  },
                  "loc": { "start": 757, "end": 767 }
                }
              ],
              "loc": { "start": 739, "end": 768 }
            },
            {
              "kind": "Directive",
              "name": {
                "kind": "Name",
                "value": "dir2",
                "loc": { "start": 770, "end": 774 }
              },
              "arguments": [
                {
                  "kind": "Argument",
                  "name": {
                    "kind": "Name",
                    "value": "id",
                    "loc": { "start": 775, "end": 777 }
                  },
                  "value": {
                    "ObjectValue": "ObjectField",
                    "fields": [
                      {
                        "kind": "ObjectField",
                        "name": {
                          "kind": "Name",
                          "value": "a",
                          "loc": { "start": 781, "end": 782 }
                        },
                        "value": {
                          "kind": "IntValue",
                          "value": 1,
                          "loc": { "start": 784, "end": 785 }
                        },
                        "loc": { "start": 781, "end": 785 }
                      },
                      {
                        "kind": "ObjectField",
                        "name": {
                          "kind": "Name",
                          "value": "b",
                          "loc": { "start": 787, "end": 788 }
                        },
                        "value": {
                          "kind": "IntValue",
                          "value": 2,
                          "loc": { "start": 790, "end": 791 }
                        },
                        "loc": { "start": 787, "end": 791 }
                      }
                    ],
                    "loc": { "start": 779, "end": 793 }
                  },
                  "loc": { "start": 775, "end": 793 }
                }
              ],
              "loc": { "start": 769, "end": 794 }
            },
            {
              "kind": "Directive",
              "name": {
                "kind": "Name",
                "value": "dir3",
                "loc": { "start": 796, "end": 800 }
              },
              "arguments": [],
              "loc": { "start": 795, "end": 800 }
            }
          ],
          "loc": { "start": 719, "end": 897 }
        },
        {
          "kind": "ObjectTypeDefinition",
          "name": {
            "kind": "Name",
            "value": "User4",
            "loc": { "start": 911, "end": 916 }
          },
          "interfaces": [],
          "fields": [
            {
              "kind": "FieldDefinition",
              "name": {
                "kind": "Name",
                "value": "name",
                "loc": { "start": 929, "end": 933 }
              },
              "type": {
                "kind": "NamedType",
                "name": {
                  "kind": "Name",
                  "value": "String",
                  "loc": { "start": 935, "end": 941 }
                },
                "loc": { "start": 935, "end": 941 }
              },
              "arguments": [],
              "directives": [
                {
                  "kind": "Directive",
                  "name": {
                    "kind": "Name",
                    "value": "dir",
                    "loc": { "start": 943, "end": 946 }
                  },
                  "arguments": [
                    {
                      "kind": "Argument",
                      "name": {
                        "kind": "Name",
                        "value": "id",
                        "loc": { "start": 947, "end": 949 }
                      },
                      "value": {
                        "kind": "IntValue",
                        "value": 6,
                        "loc": { "start": 951, "end": 952 }
                      },
                      "loc": { "start": 947, "end": 952 }
                    }
                  ],
                  "loc": { "start": 942, "end": 953 }
                }
              ],
              "loc": { "start": 918, "end": 953 }
            }
          ],
          "directives": [],
          "loc": { "start": 897, "end": 963 }
        },
        {
          "description": {
            "kind": "StringValue",
            "value": "EnumTypeDefinition description",
            "block": false,
            "loc": { "start": 973, "end": 1005 }
          },
          "kind": "EnumTypeDefinition",
          "name": {
            "kind": "Name",
            "value": "colors",
            "loc": { "start": 1019, "end": 1025 }
          },
          "directives": [
            {
              "kind": "Directive",
              "name": {
                "kind": "Name",
                "value": "myDirective",
                "loc": { "start": 1027, "end": 1038 }
              },
              "arguments": [
                {
                  "kind": "Argument",
                  "name": {
                    "kind": "Name",
                    "value": "count",
                    "loc": { "start": 1039, "end": 1044 }
                  },
                  "value": {
                    "kind": "IntValue",
                    "value": 6,
                    "loc": { "start": 1046, "end": 1047 }
                  },
                  "loc": { "start": 1039, "end": 1047 }
                }
              ],
              "loc": { "start": 1026, "end": 1048 }
            }
          ],
          "values": [
            {
              "description": {
                "kind": "StringValue",
                "value": "EnumValueDefinition description",
                "block": false,
                "loc": { "start": 1061, "end": 1094 }
              },
              "kind": "EnumValueDefinition",
              "name": {
                "kind": "Name",
                "value": "BLACK",
                "loc": { "start": 1105, "end": 1110 }
              },
              "directives": [
                {
                  "kind": "Directive",
                  "name": {
                    "kind": "Name",
                    "value": "dir",
                    "loc": { "start": 1112, "end": 1115 }
                  },
                  "arguments": [
                    {
                      "kind": "Argument",
                      "name": {
                        "kind": "Name",
                        "value": "id",
                        "loc": { "start": 1116, "end": 1118 }
                      },
                      "value": {
                        "kind": "StringValue",
                        "value": "xjs",
                        "block": false,
                        "loc": { "start": 1120, "end": 1125 }
                      },
                      "loc": { "start": 1116, "end": 1125 }
                    }
                  ],
                  "loc": { "start": 1111, "end": 1126 }
                }
              ],
              "loc": { "start": 1061, "end": 1126 }
            },
            {
              "kind": "EnumValueDefinition",
              "name": {
                "kind": "Name",
                "value": "RED",
                "loc": { "start": 1137, "end": 1140 }
              },
              "directives": [],
              "loc": { "start": 1126, "end": 1140 }
            }
          ],
          "loc": { "start": 973, "end": 1150 }
        },
        {
          "kind": "InterfaceTypeDefinition",
          "name": {
            "kind": "Name",
            "value": "Person",
            "loc": { "start": 1170, "end": 1176 }
          },
          "interfaces": [
            {
              "kind": "NamedType",
              "name": {
                "kind": "Name",
                "value": "Character",
                "loc": { "start": 1188, "end": 1197 }
              },
              "loc": { "start": 1188, "end": 1197 }
            }
          ],
          "fields": [
            {
              "kind": "FieldDefinition",
              "name": {
                "kind": "Name",
                "value": "name",
                "loc": { "start": 1218, "end": 1222 }
              },
              "type": {
                "kind": "NamedType",
                "name": {
                  "kind": "Name",
                  "value": "String",
                  "loc": { "start": 1224, "end": 1230 }
                },
                "loc": { "start": 1224, "end": 1230 }
              },
              "arguments": [],
              "directives": [
                {
                  "kind": "Directive",
                  "name": {
                    "kind": "Name",
                    "value": "dir",
                    "loc": { "start": 1232, "end": 1235 }
                  },
                  "arguments": [
                    {
                      "kind": "Argument",
                      "name": {
                        "kind": "Name",
                        "value": "id",
                        "loc": { "start": 1236, "end": 1238 }
                      },
                      "value": {
                        "kind": "IntValue",
                        "value": 5,
                        "loc": { "start": 1240, "end": 1241 }
                      },
                      "loc": { "start": 1236, "end": 1241 }
                    }
                  ],
                  "loc": { "start": 1231, "end": 1242 }
                }
              ],
              "loc": { "start": 1207, "end": 1242 }
            }
          ],
          "directives": [
            {
              "kind": "Directive",
              "name": {
                "kind": "Name",
                "value": "topDir",
                "loc": { "start": 1199, "end": 1205 }
              },
              "arguments": [],
              "loc": { "start": 1198, "end": 1205 }
            }
          ],
          "loc": { "start": 1150, "end": 1252 }
        },
        {
          "kind": "UnionTypeDefinition",
          "name": {
            "kind": "Name",
            "value": "SearchResult",
            "loc": { "start": 1268, "end": 1280 }
          },
          "types": [
            {
              "kind": "NamedType",
              "name": {
                "kind": "Name",
                "value": "A",
                "loc": { "start": 1293, "end": 1294 }
              },
              "loc": { "start": 1293, "end": 1294 }
            },
            {
              "kind": "NamedType",
              "name": {
                "kind": "Name",
                "value": "B",
                "loc": { "start": 1297, "end": 1298 }
              },
              "loc": { "start": 1297, "end": 1298 }
            }
          ],
          "directives": [
            {
              "kind": "Directive",
              "name": {
                "kind": "Name",
                "value": "dir",
                "loc": { "start": 1282, "end": 1285 }
              },
              "arguments": [
                {
                  "kind": "Argument",
                  "name": {
                    "kind": "Name",
                    "value": "a",
                    "loc": { "start": 1286, "end": 1287 }
                  },
                  "value": {
                    "kind": "IntValue",
                    "value": 6,
                    "loc": { "start": 1288, "end": 1289 }
                  },
                  "loc": { "start": 1286, "end": 1289 }
                }
              ],
              "loc": { "start": 1281, "end": 1290 }
            }
          ],
          "loc": { "start": 1252, "end": 1298 }
        }
      ],
      "loc": { "start": 0, "end": 1303 }
    }
  |}
};
