%{
  open Ast
%}

/* Token definitions */
%token TYPE
%token ENUM
%token <string> IDENTIFIER
%token EOF


/* Specify starting production */
%start document

%type <document> document

%% /* Start grammar productions */

document: 
  | definitions=list(Definition) EOF { {definitions} }
  ;

Definition:
  | TypeDefinition { TypeDefinition($1) }
  ;

TypeDefinition:
  | ObjectTypeDefinition { Object($1) }
  | EnumTypeDefinition { Enum($1) }
  ;

ObjectTypeDefinition:
  | TYPE name=Name { {name } }
  ;

EnumTypeDefinition:
  | ENUM name=Name { {name } }
  ;

Name:
  | IDENTIFIER { Name({value=$1}) }
  ;