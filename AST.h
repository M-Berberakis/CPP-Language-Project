#ifndef AST_H
#define AST_H
//AST_7
struct ASTnode
	{
		enum { ekID, ekNUM, ekBinExpression, ekASSIGN, ekWHILE, ekCALL, ekSTATE, ekLastElement 
		} kind;
		union
		{
			double val;
			char* name;
			struct
			{
				struct ASTnode * left, * right;
				char* op;
			} expression;
			struct
			{
				char* name;
				struct ASTnode* right;
			} assignment;
			struct
			{
				int count;
				struct ASTnode** statements;
			} statements;
			struct
			{
				struct ASTnode* cond;
				struct ASTnode* statements;
			} whileStatement;
			struct
			{
				char* name;
				struct ASTnode* param;
			} functionCall;
			
		} data;
	};

struct ASTnode* makeAssignment(char* name, struct ASTnode* expr);
struct ASTnode* makeMinusNum(struct ASTnode* expr);
struct ASTnode* makePlusNum(struct ASTnode* expr);
struct ASTnode* makeExpByNum(double val);
struct ASTnode* makeExpByName(char* name);
struct ASTnode* makeExpression(struct ASTnode* left, struct ASTnode* right, char* op);
struct ASTnode* makeStatements(struct ASTnode* result, struct ASTnode* toAppend);
struct ASTnode* makeWhile(struct ASTnode* cond, struct ASTnode* exec);
struct ASTnode* makeFunctionCall(char* name, struct ASTnode* param);

char* getNodeKindName(int kind);

#endif