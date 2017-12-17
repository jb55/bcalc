

%option noyywrap

%{
#include <stdio.h>
#include <gmp.h>

#define YY_DECL int yylex()
    extern YYSTYPE yylval;

#include "parser.tab.h"

%}

%%

[ \t]	; // ignore all whitespace

[mM]?[bB][tT][cC] {
  int ism = yytext[0] == 'm' || yytext[0] == 'M';
  yylval.unit = ism? UNIT_MBTC : UNIT_BTC;
  return T_UNIT;
}

[mM]?[sS][aA][tT][sS]? {
    int ism = yytext[0] == 'm' || yytext[0] == 'M';
    yylval.unit = ism ? UNIT_MSATOSHI : UNIT_SATOSHI;
    return T_UNIT;
}

[0-9]*\.[0-9]+ {
  double d = atof(yytext);
  yylval.dubs = d;
  return T_FLOAT;
}

[0-9]+		{
    mpq_init(yylval.rval);
    mpz_set_str(yylval.rval, yytext, 10);
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
