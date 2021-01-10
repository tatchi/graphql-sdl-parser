%{
  open Ast
%}

/* Token definitions */
%token LBRACE
%token RBRACE
%token COLON
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
  | Name COLON Name { {name=$1;type_=NamedType($3);loc=$loc} }

EnumTypeDefinition:
  | ENUM name=Name { {name; loc=$loc } }
  ;

Name:
  | IDENTIFIER { Name({value=$1; loc=$loc}) }
  ;