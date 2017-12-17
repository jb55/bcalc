
%{

#include <stdio.h>
#include <num.h>
#include <stdlib.h>

extern int yylex();
extern int yyparse();
extern FILE* yyin;

char buffer[255];

void yyerror(const char* s);
%}

%union {
  int64_t intval;
  double floatval;
  enum units unit;
}

%token<intval> T_INT
%token<floatval> T_FLOAT
%token<unit> T_UNIT
%token T_PLUS T_MINUS T_MULTIPLY T_DIVIDE T_LEFT T_RIGHT
%token T_NEWLINE T_QUIT
%left T_PLUS T_MINUS
%left T_MULTIPLY T_DIVIDE

%type<rval> expr

%start calc

%%

calc:
    | calc line
;

line: T_NEWLINE
    | expr T_NEWLINE { mpq_out_str(stdout, 10, $1); printf("\n"); }
;

expr: T_INT                 { ; }
    | expr T_PLUS expr      { mpq_add($$, $1, $3); }
    | expr T_MINUS expr     { mpq_sub($$, $1, $3); }
    | expr T_MULTIPLY expr  { mpq_mul($$, $1, $3); }
    | expr T_DIVIDE expr    { mpq_div($$, $1, $3); }
    | T_LEFT expr T_RIGHT   { mpq_init($$); mpq_set($$, $2); }
;

%%

int main() {
  yyin = stdin;

  do {
    yyparse();
  } while(!feof(yyin));

  return 0;
}

void yyerror(const char* s) {
  fprintf(stderr, "Parse error: %s\n", s);
  exit(1);
}
