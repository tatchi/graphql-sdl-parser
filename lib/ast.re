type loc = (Lexing.position, Lexing.position);

type directiveLocation =
  | Query
  | Mutation
  | Subscription
  | Field
  | FragmentDefinition
  | FragmentSpread
  | InlineFragment
  | Schema
  | Scalar
  | Object
  | FieldDefinition
  | ArgumentDefinition
  | Interface
  | Union
  | Enum
  | EnumValue
  | InputObject
  | InputFieldDefinition;

let directiveLocationOfString = s =>
  switch (s) {
  | "QUERY" => Query
  | "MUTATION" => Mutation
  | "SUBSCRIPTION" => Subscription
  | "FIELD" => Field
  | "FRAGMENT_DEFINITION" => FragmentDefinition
  | "FRAGMENT_SPREAD" => FragmentSpread
  | "INLINE_FRAGMENT" => InlineFragment
  | "SCHEMA" => Schema
  | "SCALAR" => Scalar
  | "OBJECT" => Object
  | "FIELD_DEFINITION" => FieldDefinition
  | "ARGUMENT_DEFINITION" => ArgumentDefinition
  | "INTERFACE" => Interface
  | "UNION" => Union
  | "ENUM" => Enum
  | "ENUM_VALUE" => EnumValue
  | "INPUT_OBJECT" => InputObject
  | "INPUT_FIELD_DEFINITION" => InputFieldDefinition
  | _ => failwith("Invalid directive location")
  };

let directiveLocationToString = directiveLoc =>
  switch (directiveLoc) {
  | Query => "QUERY"
  | Mutation => "MUTATION"
  | Subscription => "SUBSCRIPTION"
  | Field => "FIELD"
  | FragmentDefinition => "FRAGMENT_DEFINITION"
  | FragmentSpread => "FRAGMENT_SPREAD"
  | InlineFragment => "INLINE_FRAGMENT"
  | Schema => "SCHEMA"
  | Scalar => "SCALAR"
  | Object => "OBJECT"
  | FieldDefinition => "FIELD_DEFINITION"
  | ArgumentDefinition => "ARGUMENT_DEFINITION"
  | Interface => "INTERFACE"
  | Union => "UNION"
  | Enum => "ENUM"
  | EnumValue => "ENUM_VALUE"
  | InputObject => "INPUT_OBJECT"
  | InputFieldDefinition => "INPUT_FIELD_DEFINITION"
  };

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
  | ListValue(listValue)
  | ObjectValue(objectValue);

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

type argument = {
  name,
  value,
  loc,
};

type directive = {
  name,
  arguments: list(argument),
  loc,
};

type directives = list(directive);
type description = option(stringValue);

type inputValueDefinition = {
  name,
  type_: fieldType,
  description,
  loc,
  defaultValue: option(value),
  directives,
};

type fieldDefinition = {
  name,
  type_: fieldType,
  description,
  arguments: list(inputValueDefinition),
  directives,
  loc,
};

type objectType = {
  name,
  description,
  fields: list(fieldDefinition),
  interfaces: list(namedType),
  directives,
  loc,
};

type interfaceType = {
  name,
  description,
  fields: list(fieldDefinition),
  interfaces: list(namedType),
  directives,
  loc,
};

type valueDefinition = {
  name,
  description,
  directives,
  loc,
};

type enumType = {
  name,
  description,
  directives,
  values: list(valueDefinition),
  loc,
};

type unionType = {
  name,
  description,
  directives,
  types_: list(namedType),
  loc,
};

type inputObjectType = {
  name,
  description,
  directives,
  fields: list(inputValueDefinition),
  loc,
};

type typeDefinition =
  | Object(objectType)
  | Enum(enumType)
  | Interface(interfaceType)
  | Union(unionType)
  | InputObject(inputObjectType)
  | Scalar(valueDefinition);

type directiveDefinition_location = {
  value: directiveLocation,
  loc,
};

type directiveDefinition = {
  name,
  description,
  arguments: list(inputValueDefinition),
  repeatable: bool,
  locations: list(directiveDefinition_location),
  loc,
};

type operation =
  | Query
  | Mutation
  | Subscription;

let operationToString = operation =>
  switch (operation) {
  | Query => "query"
  | Mutation => "mutation"
  | Subscription => "subscription"
  };

type operationTypeDefinition = {
  operation,
  type_: namedType,
  loc,
};

type schemaDefinition = {
  description,
  directives,
  operationTypes: list(operationTypeDefinition),
  loc,
};

type definition =
  | SchemaDefinition(schemaDefinition)
  | TypeDefinition(typeDefinition)
  | DirectiveDefinition(directiveDefinition);

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

let nameToJson = (name: name) =>
  `Assoc([
    ("kind", `String("Name")),
    ("value", `String(name.value)),
    locToJson(name.loc),
  ]);
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

let rec objectValueToJson = (objectValue: objectValue) =>
  `Assoc([
    ("ObjectValue", `String("ObjectField")),
    ("fields", `List(objectValue.fields |> List.map(objectFieldToJson))),
    locToJson(objectValue.loc),
  ])
and objectFieldToJson = (objectField: objectField) =>
  `Assoc([
    ("kind", `String("ObjectField")),
    ("name", nameToJson(objectField.name)),
    ("value", valueToJson(objectField.value)),
    locToJson(objectField.loc),
  ])

and listValueToJson = (listValue: listValue) => {
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
  | ObjectValue(objectValue) => objectValueToJson(objectValue)
  };

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

let argumentToJson = (argument: argument) =>
  `Assoc([
    ("kind", `String("Argument")),
    ("name", nameToJson(argument.name)),
    ("value", valueToJson(argument.value)),
    locToJson(argument.loc),
  ]);

let directiveToJson = (directive: directive) =>
  `Assoc([
    ("kind", `String("Directive")),
    ("name", nameToJson(directive.name)),
    ("arguments", `List(directive.arguments |> List.map(argumentToJson))),
    locToJson(directive.loc),
  ]);

let inputValueDefinitionToJson = (inputValueDefinition: inputValueDefinition) => {
  let fields = [
    ("kind", `String("InputValueDefinition")),
    ("name", nameToJson(inputValueDefinition.name)),
    ("type", fieldTypeToJson(inputValueDefinition.type_)),
    (
      "directives",
      `List(inputValueDefinition.directives |> List.map(directiveToJson)),
    ),
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
    ("directives", `List(field.directives |> List.map(directiveToJson))),
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
    ("directives", `List(object_.directives |> List.map(directiveToJson))),
    locToJson(object_.loc),
  ];
  switch (object_.description) {
  | None => `Assoc(fields)
  | Some(description) =>
    `Assoc([("description", stringValueToJson(description)), ...fields])
  };
};
let interfaceToJson = (interface: interfaceType) => {
  let fields = [
    ("kind", `String("InterfaceTypeDefinition")),
    ("name", nameToJson(interface.name)),
    (
      "interfaces",
      `List(interface.interfaces |> List.map(namedTypeToJson)),
    ),
    ("fields", `List(interface.fields |> List.map(fieldDefinitionToJson))),
    (
      "directives",
      `List(interface.directives |> List.map(directiveToJson)),
    ),
    locToJson(interface.loc),
  ];
  switch (interface.description) {
  | None => `Assoc(fields)
  | Some(description) =>
    `Assoc([("description", stringValueToJson(description)), ...fields])
  };
};

let unionToJson = (union: unionType) => {
  let fields = [
    ("kind", `String("UnionTypeDefinition")),
    ("name", nameToJson(union.name)),
    ("types", `List(union.types_ |> List.map(namedTypeToJson))),
    ("directives", `List(union.directives |> List.map(directiveToJson))),
    locToJson(union.loc),
  ];
  switch (union.description) {
  | None => `Assoc(fields)
  | Some(description) =>
    `Assoc([("description", stringValueToJson(description)), ...fields])
  };
};

let valueDefinitionToJson = (valueDef: valueDefinition, kind: string) => {
  let fields = [
    ("kind", `String(kind)),
    ("name", nameToJson(valueDef.name)),
    ("directives", `List(valueDef.directives |> List.map(directiveToJson))),
    locToJson(valueDef.loc),
  ];
  switch (valueDef.description) {
  | None => `Assoc(fields)
  | Some(description) =>
    `Assoc([("description", stringValueToJson(description)), ...fields])
  };
};

let enumValueDefinitionToJson = (valueDef: valueDefinition) =>
  valueDefinitionToJson(valueDef, "EnumValueDefinition");

let enumToJson = (enum: enumType) => {
  let fields = [
    ("kind", `String("EnumTypeDefinition")),
    ("name", nameToJson(enum.name)),
    ("directives", `List(enum.directives |> List.map(directiveToJson))),
    ("values", `List(enum.values |> List.map(enumValueDefinitionToJson))),
    locToJson(enum.loc),
  ];

  switch (enum.description) {
  | None => `Assoc(fields)
  | Some(description) =>
    `Assoc([("description", stringValueToJson(description)), ...fields])
  };
};

let inputObjectToJson = (inputObject: inputObjectType) => {
  let fields = [
    ("kind", `String("InputObjectTypeDefinition")),
    ("name", nameToJson(inputObject.name)),
    (
      "directives",
      `List(inputObject.directives |> List.map(directiveToJson)),
    ),
    (
      "fields",
      `List(inputObject.fields |> List.map(inputValueDefinitionToJson)),
    ),
    locToJson(inputObject.loc),
  ];

  switch (inputObject.description) {
  | None => `Assoc(fields)
  | Some(description) =>
    `Assoc([("description", stringValueToJson(description)), ...fields])
  };
};
let scalarToJson = (scalar: valueDefinition) =>
  valueDefinitionToJson(scalar, "ScalarTypeDefinition");

let typeDefinitionToJson = typeDefinition =>
  switch (typeDefinition) {
  | Object(object_) => objectToJson(object_)
  | Interface(interface) => interfaceToJson(interface)
  | Enum(enum) => enumToJson(enum)
  | Union(union) => unionToJson(union)
  | InputObject(inputObject) => inputObjectToJson(inputObject)
  | Scalar(scalar) => scalarToJson(scalar)
  };

let directiveLocationToJson =
    (directiveLocation: directiveDefinition_location) =>
  `Assoc([
    ("kind", `String("Name")),
    ("value", `String(directiveLocation.value |> directiveLocationToString)),
    locToJson(directiveLocation.loc),
  ]);

let directiveDefinitionToJson = (directiveDefinition: directiveDefinition) => {
  let fields = [
    ("kind", `String("DirectiveDefinition")),
    ("name", nameToJson(directiveDefinition.name)),
    (
      "arguments",
      `List(
        directiveDefinition.arguments |> List.map(inputValueDefinitionToJson),
      ),
    ),
    ("repeatable", `Bool(directiveDefinition.repeatable)),
    (
      "locations",
      `List(
        directiveDefinition.locations |> List.map(directiveLocationToJson),
      ),
    ),
    locToJson(directiveDefinition.loc),
  ];

  switch (directiveDefinition.description) {
  | None => `Assoc(fields)
  | Some(description) =>
    `Assoc([("description", stringValueToJson(description)), ...fields])
  };
};

let operationTypeToJson = (operationType: operationTypeDefinition) =>
  `Assoc([
    ("kind", `String("OperationTypeDefinition")),
    ("operation", `String(operationType.operation |> operationToString)),
    ("type", namedTypeToJson(operationType.type_)),
    locToJson(operationType.loc),
  ]);

let schemaDefinitionToJson = (schemaDefinition: schemaDefinition) => {
  let fields = [
    ("kind", `String("SchemaDefinition")),
    (
      "directives",
      `List(schemaDefinition.directives |> List.map(directiveToJson)),
    ),
    (
      "operationTypes",
      `List(
        schemaDefinition.operationTypes |> List.map(operationTypeToJson),
      ),
    ),
    locToJson(schemaDefinition.loc),
  ];

  switch (schemaDefinition.description) {
  | None => `Assoc(fields)
  | Some(description) =>
    `Assoc([("description", stringValueToJson(description)), ...fields])
  };
};

let definitionToJson = definition =>
  switch (definition) {
  | TypeDefinition(typeDefinition) => typeDefinitionToJson(typeDefinition)
  | DirectiveDefinition(directiveDefinition) =>
    directiveDefinitionToJson(directiveDefinition)
  | SchemaDefinition(schemaDefinition) =>
    schemaDefinitionToJson(schemaDefinition)
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
