#include "AST.h"
#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include <assert.h>

#define PRINT_NODES 1
//AST_7
char* getNodeKindName(int kind)
{
	switch (kind)
	{
		case ekID				: return "Identifier";
		case ekNUM			: return "Number";
		case ekBinExpression	: return "BinExpression";
		case ekASSIGN		: return "Assignment";
		case ekWHILE			: return "WhileStmt";
		case ekCALL				: return "FunctionCall";
		case ekSTATE		: return "Statements";
		case ekLastElement		: return "LastElement";
		default					: return "?uknown";
	}
}


static void* checkAlloc (size_t sz)
{
	void* result = calloc(sz, 1);
	if (!result)
	{
		fprintf(stderr, "ASTnode allocation failed\n");
		exit(1);
	}
}

struct ASTnode* makeAssignment(char* name, struct ASTnode* expr)
{
	struct ASTnode* result = checkAlloc(sizeof(*result));
	result->kind = ekASSIGN;
	result->data.assignment.name = name;
	result->data.assignment.right = expr;
	if (PRINT_NODES) printf("makeASSIGN: %s, \t%s <- %s\n", getNodeKindName(ekASSIGN), name , getNodeKindName(expr->kind));
	return result;
}
struct ASTnode* makeMinusNum(struct ASTnode* expr)
{
	struct ASTnode* result = checkAlloc(sizeof(*result));
	result->kind = ekNUM;
	result->data.val = -expr->data.val;
	if (PRINT_NODES) printf("makeMinusNUM: %s, \tval: %d\n", getNodeKindName(ekNUM), -expr->data.val);
	return result;
}

struct ASTnode* makePlusNum(struct ASTnode* expr)
{
	struct ASTnode* result = checkAlloc(sizeof(*result));
	result->kind = ekNUM;
	result->data.val = expr->data.val;
	if (PRINT_NODES) printf("makePlusNUM: %s, \tval: %d\n", getNodeKindName(ekNUM), expr->data.val);
	return result;
}

struct ASTnode* makeExpByNum(double val)
{
	struct ASTnode* result = checkAlloc(sizeof(*result));
	result->kind = ekNUM;
	result->data.val = val;
	if (PRINT_NODES) printf("makeExpByNUM: %s, \tval: %f\n", getNodeKindName(ekNUM), val);
	return result;
}
struct ASTnode* makeExpByName(char* name)
{
	struct ASTnode* result = checkAlloc(sizeof(*result));
	result->kind = ekID;
	result->data.name = name;
	if (PRINT_NODES) printf("makeExpByNAME: %s, \tname: %s\n", getNodeKindName(ekID), name);
	return result;
}
struct ASTnode* makeExpression(struct ASTnode* left, struct ASTnode* right, char* op)
{
	struct ASTnode* result = checkAlloc(sizeof(*result));
	result->kind = ekBinExpression;
	result->data.expression.left = left;
	result->data.expression.right = right;
	result->data.expression.op = op;
	if (PRINT_NODES) printf("makeExpression: %s, \t %s %s %s\n", getNodeKindName(ekBinExpression), getNodeKindName(left->kind), op, getNodeKindName(right->kind));
	return result;
}
struct ASTnode* makeStatements(struct ASTnode* result, struct ASTnode* toAppend) 
{
	if (!result)
	{
		result = checkAlloc(sizeof(*result));
		result->kind = ekSTATE;
		result->data.statements.count = 0;
		result->data.statements.statements = 0;
	}
	assert(ekSTATE == result->kind);
	result->data.statements.count++;
	result->data.statements.statements = 
		realloc(result->data.statements.statements, result->data.statements.count*sizeof(*result->data.statements.statements));
	result->data.statements.statements[result->data.statements.count-1] = toAppend;
	if (PRINT_NODES) printf("makeSTATE: %s, \tcount: %d, \tappend: %s\n", getNodeKindName(ekSTATE), result->data.statements.count, getNodeKindName(toAppend->kind));
	return result;
}
struct ASTnode* makeWhile(struct ASTnode* cond, struct ASTnode* exec)
{
	struct ASTnode* result = checkAlloc(sizeof(*result));
	result->kind = ekWHILE;;
	result->data.whileStatement.cond = cond;
	result->data.whileStatement.statements = exec;
	if (PRINT_NODES) printf("makeWHILE: %s, \tcond: %s, \tparam: %s\n", getNodeKindName(ekWHILE), getNodeKindName(cond->kind), getNodeKindName(exec->kind));
	return result;
}
struct ASTnode* makeFunctionCall(char* name, struct ASTnode* param)
{
	struct ASTnode* result = checkAlloc(sizeof(*result));
	result->kind = ekCALL;
	result->data.functionCall.name = name;
	result->data.functionCall.param = param;
	if (PRINT_NODES) printf("makeCALL: %s, \tfunction: %s (%s)\n", getNodeKindName(ekCALL), name, getNodeKindName(param->kind));
	return result;
}

