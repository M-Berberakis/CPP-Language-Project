%{
//Lexer 7
#include "Parser.tab.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define fileno _fileno

%}

%option noyywrap

%%

([0-9]+|([0-9]*\.[0-9]+)([eE][-+]?[0-9]+)?) {
			yylval.val = atof(yytext);
			return NUMBER;
}
"{"		{ return BEG; }
"}"		{ return END; }
"IF"		{ return IF; }
"THEN"		{ return THEN; }
"ELSE"		{ return ELSE; }
"INCASE"		{ return WHILE; }
"REPEAT"		{ return DO; }
"PRINT"		{ yylval.name = _strdup(yytext); return PRINT; }
">>"		{ return ASSIGN; }
"TRUE"		{ return TRUE; }
"FALSE"		{ return FALSE; }
">="		{ yylval.op = _strdup(yytext); return GEQ; }
"<="		{ yylval.op = _strdup(yytext); return LEQ; }
"?="		{ yylval.op = _strdup(yytext); return EQ; }
"<>"		{ yylval.op = _strdup(yytext); return NEQ; }
">"			{ yylval.op = _strdup(yytext); return GRT; }
"<"			{ yylval.op = _strdup(yytext); return LES; }
"&&"		{ yylval.op = _strdup(yytext); return AND; }
"||"		{ yylval.op = _strdup(yytext); return OR; }
"!"			{ yylval.op = _strdup(yytext); return NOT; }

"("			{ return LP; }
")"			{ return RP; }

"+"			{ yylval.op = _strdup(yytext); return PLUS; }
"-"			{ yylval.op = _strdup(yytext); return MINUS; }
"*"			{ yylval.op = _strdup(yytext); return STAR; }
"/"			{ yylval.op = _strdup(yytext);  return DIV; }

"|"			{ return SEMI; }

[A-Za-z][A-Za-z0-9]* {
			yylval.name = _strdup(yytext);
			return NAME; 
}
#.*			{ /* one-line comment */ }
[\t ]+		{ ; /* ignore whitespace */ }
\n			{ ; /* return nothing for LF */ }
\r			{ ; /* return nothing for CR */ }
.           { printf("'%s' is uknown ", yytext); yyerror(" illegal character detected"); }

%%