%{
//Parser 7
#include "AST.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>


FILE* yyin;
int yyerror();
extern int yylex();

#define YYDEBUG 1
/* Since the parser must return the AST, it must get a parameter where
* the AST can be stored. The type of the parameter will be void*. */
#define YYPARSE_PARAM astDest	
struct ASTnode* astDest;

extern void execAST(struct ExecEnviron* e, struct ASTnode* a);
extern struct ExecEnviron* createEnv();
void freeEnv(struct ExecEnviron* e);
	
%}

//%parse-param { struct ASTnode* astDest }

%error-verbose

%union symval
{
	double val;
	char* op;
	char* name;
	
	struct ASTnode* ast;
};

%token <val> NUMBER						/* A NUMBER token contains a number */
%token <name> NAME						/* A NAME token contains a variable */
%token <name> PRINT						/* A PRINT token contains an implementation of print function */

%token TRUE FALSE						/* Boolean keywords */
%token <op> EQ NEQ GEQ LEQ GRT LES		/* Comparison operators */
%token <op> AND OR NOT					/* Boolean operators */
%token <op> MINUS PLUS STAR DIV			/* Arithmetic operators */
%token SEMI ASSIGN 						/* Statement operators */
%token IF THEN ELSE WHILE DO			/* Statement keywords */
%token LP RP							/* Left and right parentheses */

%token BEG END							/* Block keywords */

%type <ast> program block statements statement assignment expression whileStatement functionCall

%start program

/* Associativity of operators in order of increasing precedence */
%right ASSIGN
%right SEMI
%left NOT
%left OR
%left AND
%left MINUS PLUS
%left STAR DIV
%nonassoc UPLUS UMINUS



%%
program
	:		statement SEMI					{ (*(struct ASTnode**)astDest) = $1; } 
	;

block
	:		BEG statements END				{ $$ = $2; }
	;

statements
	:		/* empty */						{ $$ = 0; }
	|		statements block SEMI			{ $$ = makeStatements($1, $2); }
	|		statements statement SEMI		{ $$ = makeStatements($1, $2); }
	;

statement
	:		assignment						{ $$ = $1; }
	|		block							{ $$ = $1; }
	|		whileStatement					{ $$ = $1; }
	|		functionCall					{ $$ = $1; }
 	;

assignment
	:		NAME ASSIGN expression			{ $$ = makeAssignment($1, $3); }
	;

whileStatement
	:		WHILE expression DO statement	{$$ = makeWhile($2, $4); }
	;

functionCall
	:		PRINT LP expression RP			{ $$ = makeFunctionCall($1, $3); }
	;

expression
	:		expression PLUS expression		{ $$ = makeExpression($1, $3, $2); }
	|		expression MINUS expression		{ $$ = makeExpression($1, $3, $2); }
	|		expression STAR expression		{ $$ = makeExpression($1, $3, $2); }
	|		expression DIV expression		{
												if ($3 == 0)
														yyerror("division by zero");
												else	$$ = makeExpression($1, $3, $2);  
											}
	|		expression EQ expression		{ $$ = makeExpression($1, $3, $2); }
	|		expression NEQ expression		{ $$ = makeExpression($1, $3, $2); }
	|		expression GEQ expression		{ $$ = makeExpression($1, $3, $2); }
	|		expression LEQ expression		{ $$ = makeExpression($1, $3, $2); }
	|		expression GRT expression		{ $$ = makeExpression($1, $3, $2); }
	|		expression LES expression		{ $$ = makeExpression($1, $3, $2); }
	|		expression AND expression		{ $$ = makeExpression($1, $3, $2); }
	|		expression OR expression		{ $$ = makeExpression($1, $3, $2); }
	|		expression NOT expression		{ $$ = makeExpression($1, $3, $2); }
	|		MINUS expression %prec UMINUS	{ $$ = makeMinusNum($2); }
	|		PLUS expression %prec UPLUS		{ $$ = makePlusNum($2); }
	|		LP expression RP				{ $$ = makePlusNum($2); }
	|		NUMBER							{ $$ = makeExpByNum($1); }
	|		NAME							{ $$ = makeExpByName($1); }
	;

%%


int parser_main(int argc, char* argv[])
{
	yydebug = 0;
	FILE* fp = NULL;
	if (argc == 2)
	{
		fopen_s(&fp, argv[1], "rb");
		
		if (fp == NULL)
		{
			perror("failed to open file.");
		}
		else
		{
			yyin = fp;
		}
	}
	
	struct ASTnode* a;
	
	yyparse(&a);
	printf("------\nAST completed!\n");

	/* Q&D WARNING: in production code this assert must be replaced by real error handling. */
	assert(a);
	struct ExecEnviron* e = createEnv();
	printf("------\nEnv created!\n");

	execAST(e, a);
	printf("------\nAST executed!\n"); 
	
	freeEnv(e);
	/* destroy the AST */

	getchar(); /* don't close the console */

	return 0;
}

int yyerror(const char* p)
{
	printf("%s\n", p);
	return 0;
}

