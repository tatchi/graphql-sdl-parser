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
  | TYPE name=Name fields=loption(Fields) { {name; fields; loc=$loc } }
  ;

Fields:
  | LBRACE nonempty_list(Field) RBRACE { $2 }

Field: 
  | Name COLON FieldType { {name=$1;type_=$3;loc=$loc} }

FieldType:
  | NamedType { $1 }
  | ListType { $1 }
  | NonNullType { $1 }

ListType:
  | LBRACKET FieldType RBRACKET { ListType({type_=$2; loc=$loc}) }

NonNullType:
  | FieldType EXCLAMATION_MARK { NonNullType({type_=$1; loc=$loc}) }

NamedType:
  | Name { NamedType({name=$1; loc=$loc}) }

EnumTypeDefinition:
  | ENUM name=Name { {name; loc=$loc } }
  ;

Name:
  | IDENTIFIER { Name({value=$1; loc=$loc}) }
  ;