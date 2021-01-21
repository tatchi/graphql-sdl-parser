%{
  open Ast
%}

/* Token definitions */
%token LBRACE
%token RBRACE
%token LBRACKET
%token RBRACKET
%token LPAREN
%token RPAREN
%token COLON
%token COMMA
%token EXCLAMATION_MARK
%token EQUAL
%token AT
%token NULL
%token TYPE
%token ENUM
%token IMPLEMENTS
%token AMPERSAND
%token <string> SINGLE_LINE_STRING
%token <string> MULTI_LINE_STRING
%token <string> IDENTIFIER
%token <int> INT
%token <float> FLOAT
%token <bool> BOOL
%token EOF


/* Specify starting production */
%start document

%type <document> document

%% /* Start grammar productions */

document: 
  | definitions=nonempty_list(Definition) EOF { {definitions; loc=$loc} }
  ;

Definition:
  | TypeDefinition { TypeDefinition($1) }
  ;

TypeDefinition:
  | ObjectTypeDefinition { Object($1) }
  | EnumTypeDefinition { Enum($1) }
  ;

ObjectTypeDefinition:
  | description=option(StringValue) TYPE name=Name interfaces=loption(Implementations) directives=Directives fields=loption(Fields) { {name; fields; interfaces; directives;description; loc=$loc } }
  ;

Directives:
  | separated_list(COMMA*, Directive) { $1 }

Directive:
  | AT name=Name arguments=loption(OptDirectiveArguments) { {name;arguments;loc=$loc} }

OptDirectiveArguments:
  | LPAREN DirectiveArgumentList RPAREN { $2 }

DirectiveArgumentList:
  | DirectiveArgument { [$1] }
  | DirectiveArgumentList COMMA DirectiveArgument { $1@[$3] }

DirectiveArgument:
  | name=Name COLON value=Value { {name;value;loc=$loc} }

Implementations:
  | IMPLEMENTS separated_nonempty_list(AMPERSAND, NamedType) { $2 }
  ;

Fields:
  | LBRACE nonempty_list(Field) RBRACE { $2 }

Field: 
  | description=option(StringValue) name=Name arguments=loption(FieldArguments) COLON type_=FieldType { {name;description;type_;arguments;loc=$loc} }

FieldArguments:
  | LPAREN separated_nonempty_list(COMMA*, FieldArgument) RPAREN  { $2 }

FieldArgument:
  | description=option(StringValue) name=Name COLON type_=FieldType defaultValue=option(DefaultArgumentValue) { {name;description;type_;defaultValue;directives=[];loc=$loc} }


DefaultArgumentValue:
  | EQUAL Value { $2 }

Value:
  | NULL { NullValue({loc=$loc}) }
  | value=INT { IntValue({value;loc=$loc}) }
  | value=FLOAT { FloatValue({value;loc=$loc}) }
  | value=BOOL { BooleanValue({value;loc=$loc}) }
  | value=StringValue { StringValue(value) }
  | LBRACE fields=separated_list(COMMA*, ObjectField) RBRACE { ObjectValue({fields;loc=$loc}) }
  | LBRACKET values=separated_list(COMMA*, Value) RBRACKET { ListValue({values;loc=$loc}) }
  | value=IDENTIFIER { EnumValue({value;loc=$loc}) }

ObjectField:
  | name=Name COLON value=Value { {name;value;loc=$loc} }

StringValue:
  | SINGLE_LINE_STRING { {value=$1; block=false; loc=$loc} }
  | MULTI_LINE_STRING { {value=$1; block=true; loc=$loc} }

FieldType:
  | NullableFieldType { $1}
  | NonNullableFieldType { $1 }

NullableFieldType:
  | NamedOrListFieldType { NullableFieldType($1) }

NamedOrListFieldType:
  | NamedType { NamedFieldType($1) }
  | LBRACKET FieldType RBRACKET { ListFieldType({type_=$2; loc=$loc}) }

NonNullableFieldType:  
  | NamedOrListFieldType EXCLAMATION_MARK  { NonNullableFieldType({type_=$1; loc=$loc}) }
  ;

NamedType:
  | Name { {name=$1; loc=$loc} }
  ;
  
EnumTypeDefinition:
  | ENUM name=Name { {name; loc=$loc; directives=[]; values=[] } }
  ;

Name:
  | IDENTIFIER { {value=$1; loc=$loc} }
  ;