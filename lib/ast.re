type loc = (Lexing.position, Lexing.position);

type name = {
  value: string,
  loc,
};

type namedType = {
  name,
  loc,
};

type listOrNamed =
  | Named(namedType)
  | List({
      type_: fieldType,
      loc,
    })
and fieldType =
  | Nullable(listOrNamed)
  | NonNullable({
      type_: listOrNamed,
      loc,
    });

type description = {
  value: string,
  block: bool,
  loc,
};

type field = {
  name,
  type_: fieldType,
  description: option(description),
  loc,
};

type objectType = {
  name,
  description: option(description),
  fields: list(field),
  interfaces: list(namedType),
  loc,
};
type enumType = {
  name,
  loc,
  directives: list(string),
  values: list(string),
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

let descriptionToJson = description => {
  `Assoc([
    ("kind", `String("StringValue")),
    ("value", `String(description.value)),
    ("block", `Bool(description.block)),
    locToJson(description.loc),
  ]);
};

let nameToJson = (name: name) =>
  `Assoc([
    ("kind", `String("Name")),
    ("value", `String(name.value)),
    locToJson(name.loc),
  ]);

let namedTypeToJson = (namedType: namedType) =>
  `Assoc([
    ("kind", `String("NamedType")),
    ("name", nameToJson(namedType.name)),
    locToJson(namedType.loc),
  ]);

let rec listOrNamedToJson = listOrNamed => {
  switch (listOrNamed) {
  | Named(namedType) => namedTypeToJson(namedType)
  | List(listType) =>
    `Assoc([
      ("kind", `String("ListType")),
      ("type", fieldTypeToJson(listType.type_)),
      locToJson(listType.loc),
    ])
  };
}
and fieldTypeToJson = fieldType =>
  switch (fieldType) {
  | Nullable(nullable) => listOrNamedToJson(nullable)
  | NonNullable(nonNullType) =>
    `Assoc([
      ("kind", `String("NonNullType")),
      ("type", listOrNamedToJson(nonNullType.type_)),
      locToJson(nonNullType.loc),
    ])
  };

let fieldToJson = (field: field) => {
  let fields = [
    ("kind", `String("FieldDefinition")),
    ("name", nameToJson(field.name)),
    ("type", fieldTypeToJson(field.type_)),
    locToJson(field.loc),
  ];
  switch (field.description) {
  | None => `Assoc(fields)
  | Some(description) =>
    `Assoc([("description", descriptionToJson(description)), ...fields])
  };
};

let objectToJson = (object_: objectType) => {
  let fields = [
    ("kind", `String("ObjectTypeDefinition")),
    ("name", nameToJson(object_.name)),
    ("interfaces", `List(object_.interfaces |> List.map(namedTypeToJson))),
    ("fields", `List(object_.fields |> List.map(fieldToJson))),
    locToJson(object_.loc),
  ];
  switch (object_.description) {
  | None => `Assoc(fields)
  | Some(description) =>
    `Assoc([("description", descriptionToJson(description)), ...fields])
  };
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
