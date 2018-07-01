%option noyywrap

%{
#include <stdio.h>
#include "num.h"

#define YY_DECL int yylex()

#include "parser.tab.h"

%}

%%

[ \t]	; // ignore all whitespace

[bB][iI][tT][sS]? {
    yylval.lexunit.unit = UNIT_BITS;
    yylval.lexunit.name = "bits";
    return T_UNIT;
}

in|IN|to|TO {
  return T_IN;
}

[mM]?[bB][tT][cC] {
  int ism = yytext[0] == 'm' || yytext[0] == 'M';
  yylval.lexunit.unit = ism? UNIT_MBTC : UNIT_BTC;
  yylval.lexunit.name = ism? "mBTC" : "BTC";
  return T_UNIT;
}

fiat|FIAT|alt|ALT|usd|USD|cur|CUR|other|OTHER {
  yylval.lexunit.unit = UNIT_OTHER;
  yylval.lexunit.name = yytext;
  return T_UNIT;
}

[fF][iI][nN][nN][eE][yY]?[sS]? {
  yylval.lexunit.unit = UNIT_FINNEY;
  yylval.lexunit.name = "finneys";
  return T_UNIT;
}

[mM]?[sS][aA][tT][sS]? {
  int ism = yytext[0] == 'm' || yytext[0] == 'M';
  yylval.lexunit.unit = ism ? UNIT_MSATOSHI : UNIT_SATOSHI;
  yylval.lexunit.name = ism ? "msats" : "sats";
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
