%{

#include <stdio.h>
#include <stdlib.h>

#include "num.h"

enum unit g_output_format;
int g_print_unit;

%}

%union {
  int64_t intval;
  double floatval;
  enum unit unit;
  struct num num;
}

%token<intval> T_INT
%token<floatval> T_FLOAT
%token<unit> T_UNIT

%token T_PLUS T_MINUS T_MULTIPLY T_DIVIDE T_LEFT T_RIGHT
%token T_NEWLINE T_QUIT
%left T_PLUS T_MINUS
%left T_MULTIPLY T_DIVIDE

%type<num> expr

%start calc

%%

calc:
    | calc line
;

line: T_NEWLINE
    | expr T_NEWLINE { num_print(&$1, g_output_format, g_print_unit); }
    ;

expr: T_INT T_UNIT          { num_init(&$$);
                              $$.intval = $1;
                              $$.type = TYPE_INT;
                              $$.unit = $2;
                              num_assign(&$$, &$$);
                            }
    | T_FLOAT T_UNIT        { num_init(&$$);
                              $$.floatval = $1;
                              $$.type = TYPE_FLOAT;
                              $$.unit = $2;
                              num_assign(&$$, &$$);
                            }
    | expr T_PLUS expr      { num_add(&$$, &$1, &$3); }
    | expr T_MINUS expr     { num_sub(&$$, &$1, &$3); }
    /* | expr T_MULTIPLY expr  { num_mul(&$$, &$1, &$3); } */
    /* | expr T_DIVIDE expr    { num_div(&$$, &$1, &$3); } */
    | T_LEFT expr T_RIGHT   { num_init(&$$); num_assign(&$$, &$2); }
;

%%

