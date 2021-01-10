type loc = (Lexing.position, Lexing.position);

type nameType =
  | Name({
      value: string,
      loc,
    });

type fieldType =
  | NamedType({
      name: nameType,
      loc,
    })
  | ListType({
      type_: fieldType,
      loc,
    })
  | NonNullType({
      type_: fieldType,
      loc,
    });

type field = {
  name: nameType,
  type_: fieldType,
  loc,
};

type objectType = {
  name: nameType,
  fields: list(field),
  loc,
};
type enumType = {
  name: nameType,
  loc,
};

type typeDefinition =
  // | Scalar(ScalarType<'a, T>),
  | Object(objectType)
  | Enum(enumType);
// Interface(InterfaceType<'a, T>),
// Union(UnionType<'a, T>),
// InputObject(InputObjectType<'a, T>),
type definition =
  // | SchemaDefinition(string)
  | TypeDefinition(typeDefinition);
// | DirectiveDefinition(string);

type document = {
  definitions: list(definition),
  loc,
};

let locToJson = ((startPos, endPos): loc) => (
  "loc",
  `Assoc([
    ("start", `Int(startPos.pos_cnum)),
    ("end", `Int(endPos.pos_cnum)),
    // ("menhir", `String(MenhirLib.LexerUtil.range((startPos, endPos)))),
  ]),
);

let nameToJson = nameType =>
  switch (nameType) {
  | Name(name) =>
    `Assoc([
      ("kind", `String("Name")),
      ("value", `String(name.value)),
      locToJson(name.loc),
    ])
  };

let rec fieldTypeToJson = fieldType =>
  switch (fieldType) {
  | NamedType(namedType) =>
    `Assoc([
      ("kind", `String("NamedType")),
      ("name", nameToJson(namedType.name)),
      locToJson(namedType.loc),
    ])
  | ListType(listType) =>
    `Assoc([
      ("kind", `String("ListType")),
      ("type", fieldTypeToJson(listType.type_)),
      locToJson(listType.loc),
    ])
  | NonNullType(nonNullType) =>
    `Assoc([
      ("kind", `String("NonNullType")),
      ("type", fieldTypeToJson(nonNullType.type_)),
      locToJson(nonNullType.loc),
    ])
  };

let fieldToJson = (field: field) =>
  `Assoc([
    ("kind", `String("FieldDefinition")),
    ("name", nameToJson(field.name)),
    ("type", fieldTypeToJson(field.type_)),
    locToJson(field.loc),
  ]);

let objectToJson = (object_: objectType) => {
  `Assoc([
    ("kind", `String("ObjectTypeDefinition")),
    ("name", nameToJson(object_.name)),
    ("fields", `List(object_.fields |> List.map(fieldToJson))),
    locToJson(object_.loc),
  ]);
};

let enumToJson = enum =>
  `Assoc([
    ("kind", `String("EnumTypeDefinition")),
    ("name", nameToJson(enum.name)),
    locToJson(enum.loc),
  ]);

let typeDefinitionToJson = typeDefinition =>
  switch (typeDefinition) {
  | Object(object_) => objectToJson(object_)
  | Enum(enum) => enumToJson(enum)
  };

let definitionToJson = definition =>
  switch (definition) {
  | TypeDefinition(typeDefinition) => typeDefinitionToJson(typeDefinition)
  };

let toJson = document =>
  `Assoc([
    ("kind", `String("document")),
    (
      "definitions",
      `List(document.definitions |> List.map(definitionToJson)),
    ),
    locToJson(document.loc),
  ]);
