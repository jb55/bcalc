%option noyywrap

%{
#include <stdio.h>
#include <gmp.h>
#include "num.h"

#define YY_DECL int yylex()

#include "parser.tab.h"

%}

%%

[ \t]	; // ignore all whitespace

[bB][iI][tT][sS]? {
    yylval.unit = UNIT_BITS;
    return T_UNIT;
}

[mM]?[bB][tT][cC] {
  int ism = yytext[0] == 'm' || yytext[0] == 'M';
  yylval.unit = ism? UNIT_MBTC : UNIT_BTC;
  return T_UNIT;
}

[fF][iI][nN][nN][eE][yY]? {
  yylval.unit = UNIT_FINNEY;
  return T_UNIT;
}

[mM]?[sS][aA][tT][sS]? {
  int ism = yytext[0] == 'm' || yytext[0] == 'M';
  yylval.unit = ism ? UNIT_MSATOSHI : UNIT_SATOSHI;
  return T_UNIT;
}

[0-9]*\.[0-9]+ {
  double d = atof(yytext);
  yylval.floatval = d;
  return T_FLOAT;
}

[0-9]+ {
  yylval.intval = strtoll(yytext, NULL, 10);
  return T_INT;
}

\n		    {return T_NEWLINE;}
"+"		    {return T_PLUS;}
"-"		    {return T_MINUS;}
"*"		    {return T_MULTIPLY;}
"/"		    {return T_DIVIDE;}
"("		    {return T_LEFT;}
")"		    {return T_RIGHT;}

%%
