#include "ASTexec.h"
#include "AST.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

//ASTexec 7.2
struct executionENV
{
	double x; /* Stores the value of the x variable, representing a simplistic environment without a full symbol table */
};


static double execTermExpression(struct executionENV* e, struct ASTnode* a);
static double execBinExpression(struct executionENV* e, struct ASTnode* a);
static void	execAssignment(struct executionENV* e, struct ASTnode* a);
static void	execWhile(struct executionENV* e, struct ASTnode* a);
static void execFunctionCall(struct executionENV* e, struct ASTnode* a);
static void	execStatements(struct executionENV* e, struct ASTnode* a);

/* Function pointers for evaluating AST nodes that produce values */
static double (*valExecs[])(struct executionENV* e, struct ASTnode* a) =
{
	execTermExpression,
	execTermExpression,
	execBinExpression,
	NULL,
	NULL,
	NULL,
	NULL
};

/* Function pointers for executing AST nodes that do not produce values */
static void (*runExecs[])(struct executionENV* e, struct ASTnode* a) =
{
	NULL, /* Identifiers and numbers are constants and do not require execution */
	NULL,
	NULL,
	execAssignment,
	execWhile,
	execFunctionCall,
	execStatements
};

static double dispatchExpression(struct executionENV* e, struct ASTnode* a)
{
	//printf("dispatchExpression: %s\t", getNodeKindName(a->kind));
	//printf("x = %d\n", e->x);

	assert(a);
	assert(valExecs[a->kind]);
	return valExecs[a->kind](e, a);
}

static void dispatchStatement(struct executionENV* e, struct ASTnode* a)
{
	//printf("dispatchStatement: %s\t", getNodeKindName(a->kind));
	//printf("x = %d\n", e->x);

	assert(a);
	assert(runExecs[a->kind]);
	runExecs[a->kind](e, a);
}


static void onlyName(const char* name, const char* reference, const char* kind)
{

	if (strcmp(reference, name))
	{
		printf("Error! This language only supports  %s '%s', not '%s'\n", kind, reference, name);
		exit(1);
	}
}

static void onlyX(const	char* name)
{
	//printf("onlyX: %s\n", name);
	onlyName(name, "x", "variable");
}

static void	onlyPrint(const	char* name)
{
	//printf("onlyPrint: %s\n", name);
	onlyName(name, "PRINT", "function");
}

static double execTermExpression(struct executionENV* e, struct ASTnode* a)
{
	printf("\t exe: %s", getNodeKindName(a->kind));
	// Handles both ID and NUM AST node kinds

	assert(a);
	double result = 0;
	if (ekNUM == a->kind)
	{
		result = a->data.val;
	}
	else
	{
		if (ekID == a->kind)
		{
			onlyX(a->data.name);
			assert(e);
			result = e->x;
		}

	}
	printf(" = %f\n", result);

	return result;
	printf("Error: tried to get the value of a non-expression(%d)\n", a->kind);
	exit(1);
}
static double execBinExpression(struct executionENV* e, struct ASTnode* a)
{
	printf("\t exe: %s\n", getNodeKindName(a->kind));

	assert(ekBinExpression == a->kind);
	const double left = dispatchExpression(e, a->data.expression.left);
	const double right = dispatchExpression(e, a->data.expression.right);
	char* op = a->data.expression.op;

	double result = 0;
	if (strcmp(op, "+") == 0) result = left + right;
	if (strcmp(op, "-") == 0) result = left - right;
	if (strcmp(op, "*") == 0) result = left * right;
	if (strcmp(op, "/") == 0) result = left / right;
	if (strcmp(op, ">") == 0) result = (left > right);
	if (strcmp(op, "<") == 0) result = (left < right);

	printf("\t OUTCOME: %f = %f %s %f\n", result, left, op, right);
	return result;

	printf("Error: Unknown operator:%s\n", a->data.expression.op); exit(1);
	/* no return here, as every switch case returns a value or exits */
}
static void	execAssignment(struct executionENV* e, struct ASTnode* a)
{
	printf("\t exe: %s", getNodeKindName(a->kind));
	printf(" Identifier: %s\n", a->data.assignment.name);

	assert(a);
	assert(ekASSIGN == a->kind);
	onlyX(a->data.assignment.name);
	assert(e);
	struct ASTnode* r = a->data.assignment.right;
	e->x = dispatchExpression(e, r);
}
static void	execWhile(struct executionENV* e, struct ASTnode* a)
{
	printf(">> exe: %s\n", getNodeKindName(a->kind));

	assert(a);
	assert(ekWHILE == a->kind);
	struct ASTnode* const c = a->data.whileStatement.cond;
	struct ASTnode* const s = a->data.whileStatement.statements;
	assert(c);
	assert(s);

	while (dispatchExpression(e, c))
	{
		dispatchStatement(e, s);
	}
	printf("<< While finished!\n");
}
static void execPrintCall(struct executionENV* e, struct ASTnode* a)
{
	printf("\t exe: PRINT %s\n", getNodeKindName(a->kind));

	double val = 0;
	if (a->kind == ekBinExpression) val = execBinExpression(e, a);
	if (a->kind == ekID) { onlyX(a->data.name);	assert(e);	val = e->x; }

	printf("=========\n%f\n=========\n", val);

}
static void execFunctionCall(struct executionENV* e, struct ASTnode* a)
{
	printf("\t exe: %s", getNodeKindName(a->kind));
	printf(" Function: %s\n", a->data.functionCall.name);

	assert(a);
	assert(ekCALL == a->kind);
	//onlyPrint(a->data.functionCall.name);
	if (strcmp(a->data.functionCall.name, "PRINT") == 0) execPrintCall(e, a->data.functionCall.param);

}
static void	execStatements(struct executionENV* e, struct ASTnode* a)
{
	printf(">> exe: %s count: %d\n", getNodeKindName(a->kind), a->data.statements.count);

	assert(a);
	assert(ekSTATE == a->kind);
	for (int i = 0; i < a->data.statements.count; i++)
	{
		dispatchStatement(e, a->data.statements.statements[i]);
	}
	printf("<< Statements sent!\n");
}

void execAST(struct executionENV* e, struct ASTnode* a)
{
	printf("------\nexe: AST\n");

	dispatchStatement(e, a);
}

struct executionENV* createEnv()
{
	assert(ekLastElement == (sizeof(valExecs) / sizeof(*valExecs)));
	assert(ekLastElement == (sizeof(runExecs) / sizeof(*runExecs)));
	return calloc(1, sizeof(struct executionENV));
}

void freeEnv(struct executionENV* e)
{
	free(e);
}



