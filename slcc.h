#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * tokenize.c
*/

// ローカル変数の型
typedef struct LVar LVar;
struct LVar {
  LVar *next; // 次の変数かNULL
  char *name; // 変数の名前
  int len;    // 名前の長さ
  int offset; // RBPからのオフセット
};

// トークンの種類
typedef enum {
  TK_RESERVED, // 記号
  TK_IDENT,   // 識別子
  TK_NUM,      // 整数トークン
  TK_EOF,      // 入力の終わりを表すトークン
} TokenKind;

typedef struct Token Token;
struct Token {
  TokenKind kind; // トークンの型
  Token *next;    // 次の入力トークン
  int val;        // kind が TK_NUM の場合、その数値
  char *str;      // トークン文字列
  int len;        // トークンの長さ
};

void error(char *fmt, ...);
void error_at(char *loc, char *fmt, ...);
bool consume(char *op);
char *strndup(char *p, int len);
Token *consume_ident();
void expect(char *op);
int expect_number();
bool at_eof();
Token *new_token(TokenKind kind, Token *cur, char *str, int len);
Token *tokenize();

extern char *user_input;
extern Token *token;


/**
 * parse.c
*/

// 抽象構文木のノードの種類
typedef enum {
  ND_ADD,     // +
  ND_SUB,     // -
  ND_MUL,     // *
  ND_DIV,     // /
  ND_ASSIGN,  // =
  ND_RETURN,  // return
  ND_EXPR_STMT, // 式文
  ND_LVAR,    // ローカル変数
  ND_EQ,      // ==
  ND_NE,      // !=
  ND_LT,      // <
  ND_LE,      // <=
  ND_NUM,     // integer
} NodeKind;

// 抽象構文木のノードの型
typedef struct Node Node;
struct Node {
  NodeKind kind;  // ノードの型
  Node *next;     // 次のノード
  Node *lhs;      // 左辺
  Node *rhs;      // 右辺
  LVar *lvar;     // ND_LVAR のときに使われる
  int val;        // ND_NUM のときに使われる
  int offset;     // ND_LVAR のときに使われる
};

typedef struct {
  Node *node;
  LVar *locals;
  int stack_size;
} Program;
Program *program();
Node *expr();

/**
 * codegen.c
*/
void codegen(Program *prog);
