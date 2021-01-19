type loc = (Lexing.position, Lexing.position);

type name = {
  value: string,
  loc,
};

type namedType = {
  name,
  loc,
};
type stringValue = {
  value: string,
  block: bool,
  loc,
};
type booleanValue = {
  value: bool,
  loc,
};
type intValue = {
  value: int,
  loc,
};
type nullValue = {loc};
type floatValue = {
  value: float,
  loc,
};
type enumValue = {
  value: string,
  loc,
};
type listValue = {
  values: list(value),
  loc,
}
and objectField = {
  name,
  value,
  loc,
}
and objectValue = {
  fields: list(objectField),
  loc,
}
and value =
  | StringValue(stringValue)
  | BooleanValue(booleanValue)
  | IntValue(intValue)
  | FloatValue(floatValue)
  | EnumValue(enumValue)
  | NullValue(nullValue)
  | ListValue(listValue);

[@warning "-30"]
type namedOrListFieldType =
  | NamedFieldType(namedType)
  | ListFieldType({
      type_: fieldType,
      loc,
    })
and fieldType =
  | NullableFieldType(namedOrListFieldType)
  | NonNullableFieldType({
      type_: namedOrListFieldType,
      loc,
    });

type inputValueDefinition = {
  name,
  type_: fieldType,
  description: option(stringValue),
  loc,
  defaultValue: option(value),
  // directives
};

type fieldDefinition = {
  name,
  type_: fieldType,
  description: option(stringValue),
  arguments: list(inputValueDefinition),
  loc,
};

type objectType = {
  name,
  description: option(stringValue),
  fields: list(fieldDefinition),
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

let stringValueToJson = (stringValue: stringValue) => {
  `Assoc([
    ("kind", `String("StringValue")),
    ("value", `String(stringValue.value)),
    ("block", `Bool(stringValue.block)),
    locToJson(stringValue.loc),
  ]);
};

let booleanValueToJson = (booleanValue: booleanValue) => {
  `Assoc([
    ("kind", `String("BooleanValue")),
    ("value", `Bool(booleanValue.value)),
    locToJson(booleanValue.loc),
  ]);
};

let intValueToJson = (intValue: intValue) => {
  `Assoc([
    ("kind", `String("IntValue")),
    ("value", `Int(intValue.value)),
    locToJson(intValue.loc),
  ]);
};

let floatValueToJson = (floatValue: floatValue) => {
  `Assoc([
    ("kind", `String("FloatValue")),
    ("value", `Float(floatValue.value)),
    locToJson(floatValue.loc),
  ]);
};
let nullValueToJson = (nullValue: nullValue) => {
  `Assoc([("kind", `String("NullValue")), locToJson(nullValue.loc)]);
};

let enumValueToJson = (enumValue: enumValue) =>
  `Assoc([
    ("kind", `String("EnumValue")),
    ("value", `String(enumValue.value)),
    locToJson(enumValue.loc),
  ]);

let rec listValueToJson = (listValue: listValue) => {
  `Assoc([
    ("kind", `String("ListValue")),
    ("values", `List(listValue.values |> List.map(valueToJson))),
    locToJson(listValue.loc),
  ]);
}
and valueToJson = (value: value) =>
  switch (value) {
  | StringValue(stringValue) => stringValueToJson(stringValue)
  | BooleanValue(booleanValue) => booleanValueToJson(booleanValue)
  | IntValue(intValue) => intValueToJson(intValue)
  | FloatValue(floatValue) => floatValueToJson(floatValue)
  | NullValue(nullValue) => nullValueToJson(nullValue)
  | ListValue(listValue) => listValueToJson(listValue)
  | EnumValue(enumValue) => enumValueToJson(enumValue)
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

let rec listOrNamedFieldToJson = listOrNamedField => {
  switch (listOrNamedField) {
  | NamedFieldType(namedFieldType) => namedTypeToJson(namedFieldType)
  | ListFieldType(listFieldType) =>
    `Assoc([
      ("kind", `String("ListType")),
      ("type", fieldTypeToJson(listFieldType.type_)),
      locToJson(listFieldType.loc),
    ])
  };
}
and fieldTypeToJson = fieldType =>
  switch (fieldType) {
  | NullableFieldType(nullableFieldType) =>
    listOrNamedFieldToJson(nullableFieldType)
  | NonNullableFieldType(nonNullableFIeldType) =>
    `Assoc([
      ("kind", `String("NonNullType")),
      ("type", listOrNamedFieldToJson(nonNullableFIeldType.type_)),
      locToJson(nonNullableFIeldType.loc),
    ])
  };

let inputValueDefinitionToJson = (inputValueDefinition: inputValueDefinition) => {
  let fields = [
    ("kind", `String("InputValueDefinition")),
    ("name", nameToJson(inputValueDefinition.name)),
    ("type", fieldTypeToJson(inputValueDefinition.type_)),
    locToJson(inputValueDefinition.loc),
  ];

  let fields =
    switch (inputValueDefinition.defaultValue) {
    | None => fields
    | Some(defaultValue) => [
        ("defaultValue", valueToJson(defaultValue)),
        ...fields,
      ]
    };

  switch (inputValueDefinition.description) {
  | None => `Assoc(fields)
  | Some(description) =>
    `Assoc([("description", stringValueToJson(description)), ...fields])
  };
};

let fieldDefinitionToJson = (field: fieldDefinition) => {
  let fields = [
    ("kind", `String("FieldDefinition")),
    ("name", nameToJson(field.name)),
    ("type", fieldTypeToJson(field.type_)),
    (
      "arguments",
      `List(field.arguments |> List.map(inputValueDefinitionToJson)),
    ),
    locToJson(field.loc),
  ];
  switch (field.description) {
  | None => `Assoc(fields)
  | Some(description) =>
    `Assoc([("description", stringValueToJson(description)), ...fields])
  };
};

let objectToJson = (object_: objectType) => {
  let fields = [
    ("kind", `String("ObjectTypeDefinition")),
    ("name", nameToJson(object_.name)),
    ("interfaces", `List(object_.interfaces |> List.map(namedTypeToJson))),
    ("fields", `List(object_.fields |> List.map(fieldDefinitionToJson))),
    locToJson(object_.loc),
  ];
  switch (object_.description) {
  | None => `Assoc(fields)
  | Some(description) =>
    `Assoc([("description", stringValueToJson(description)), ...fields])
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
