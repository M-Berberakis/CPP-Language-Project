#ifndef ASTEXEC_H
#define ASTEXEC_H
//ASTexec 7.2
struct ASTnode;
struct executionENV;

/* creates the execution engine */
struct executionENV* createEnv();

/* removes the executionENV */
void freeEnv(struct executionENV* e);

/* executes an AST */
void execAST(struct executionENV* e, struct ASTnode* a);

/* prints an AST */
//void printAST(struct executionENV* e, struct ASTnode* a);

#endif