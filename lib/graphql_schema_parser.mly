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
%token <string> SINGLE_LINE_STRING
%token <string> MULTI_LINE_STRING
%token <string> IDENTIFIER
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
  | description=option(Description) TYPE name=Name interfaces=loption(Implementations) fields=loption(Fields) { {name; fields; interfaces; description; loc=$loc } }
  ;

Implementations:
  | IMPLEMENTS separated_nonempty_list(AMPERSAND, NamedType) { $2 }
  ;

Fields:
  | LBRACE nonempty_list(Field) RBRACE { $2 }

Field: 
  | description=option(Description) Name COLON FieldType { {name=$2;description;type_=$4;loc=$loc} }

Description:
  | SINGLE_LINE_STRING { {value=$1; block=false; loc=$loc} }
  | MULTI_LINE_STRING { {value=$1; block=true; loc=$loc} }

FieldType:
  | Nullable { $1}
  | NonNullable { $1 }

Nullable:
  | ListOrNamed { Nullable($1) }

ListOrNamed:
  | NamedType { Named($1) }
  | LBRACKET FieldType RBRACKET { List({type_=$2; loc=$loc}) }

NonNullable:  
  | ListOrNamed EXCLAMATION_MARK  { NonNullable({type_=$1; loc=$loc}) }
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