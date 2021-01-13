%{
  open Ast
%}

/* Token definitions */
%token LBRACE
%token RBRACE
%token LBRACKET
%token RBRACKET
%token COLON
%token EXCLAMATION_MARK
%token TYPE
%token ENUM
%token IMPLEMENTS
%token AMPERSAND
%token <string> STRING
%token <string> IDENTIFIER
%token EOF


/* Specify starting production */
%start document

%type <document> document

%% /* Start grammar productions */

document: 
  | definitions=list(Definition) EOF { {definitions; loc=$loc} }
  ;

Definition:
  | TypeDefinition { TypeDefinition($1) }
  ;

TypeDefinition:
  | ObjectTypeDefinition { Object($1) }
  | EnumTypeDefinition { Enum($1) }
  ;

ObjectTypeDefinition:
  | description=option(Description) TYPE name=Name interfaces=loption(Implementations) fields=loption(Fields) { {name; fields; interfaces; description; loc=$loc } }
  ;

Description:
  | STRING { {value=$1; loc=$loc} }

Implementations:
  | IMPLEMENTS separated_nonempty_list(AMPERSAND, NamedType) { $2 }
  ;

Fields:
  | LBRACE nonempty_list(Field) RBRACE { $2 }

Field: 
  | Name COLON FieldType { {name=$1;type_=$3;loc=$loc} }

FieldType:
  | NamedType { NamedType($1) }
  | LBRACKET FieldType RBRACKET { ListType({type_=$2; loc=$loc}) }
  | FieldType EXCLAMATION_MARK  { NonNullType({type_=$1; loc=$loc} ) }
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