#include "slcc.h"

Node *new_node(NodeKind kind);
Node *new_binary(NodeKind kind, Node *lhs, Node *rhs);
Node *new_num(int val);

Node *equality();
Node *relational();
Node *add();
Node *mul();
Node *unary();
Node *primary();


Node *new_node(NodeKind kind) {
  Node *node = calloc(1, sizeof(Node));
  node->kind = kind;

  return node;
}

Node *new_binary(NodeKind kind, Node *lhs, Node *rhs) {
  Node *node = new_node(kind);
  node->lhs = lhs;
  node->rhs = rhs;

  return node;
}

Node *new_num(int val) {
  Node *node = calloc(1, sizeof(Node));
  node->kind = ND_NUM;
  node->val = val;

  return node;
}

// expr = equality
Node *expr() {
  return equality();
}

// equality = relational ("==" relational | "!=" relational)*
Node *equality() {
  Node *node = relational();

  for (;;) {
    if (consume("==")) {
      node = new_binary(ND_EQ, node, relational());
    }
    else if (consume("!=")) {
      node = new_binary(ND_NE, node, relational());
    }
    else {
      return node;
    }
  }
}

// relational = add ("<" add | "<=" add | ">" add | ">=" add)*
Node *relational() {
  Node *node = add();

  for (;;) {
    if (consume("<")) {
      node = new_binary(ND_LT, node, add());
    }
    else if (consume("<=")) {
      node = new_binary(ND_LE, node, add());
    }
    else if (consume(">")) {
      node = new_binary(ND_LT, add(), node);
    }
    else if (consume(">=")) {
      node = new_binary(ND_LE, add(), node);
    }
    else {
      return node;
    }
  }
}

// add = mul ("+" mul | "-" mul)*
Node *add() {
  Node *node = mul();

  for (;;) {
    if (consume("+")) {
      node = new_binary(ND_ADD, node, mul());
    }
    else if (consume("-")) {
      node = new_binary(ND_SUB, node, mul());
    }
    else {
      return node;
    }
  }
}

// mul = unary ( "*" primary | "/" primary )*
Node *mul() {
  Node *node = unary();

  for (;;) {
    if (consume("*")) {
      node = new_binary(ND_MUL, node, primary());
    }
    else if (consume("/")) {
      node = new_binary(ND_DIV, node, primary());
    }
    else {
      return node;
    }
  }
}

// unary = ("+" | "-")? primary
Node *unary() {
  if (consume("+")) {
    // +x -> x
    return primary();
  }
  if (consume("-")) {
    // -x -> 0 - x
    return new_binary(ND_SUB, new_num(0), primary());
  }
  return primary();
}

// primary = num | "(" expr ")"
Node *primary() {
  // ( が来たら "(" expr ")" が来るはず、来なければ受理できない
  if (consume("(")) {
    Node *node = expr();
    expect(")");
    return node;
  }

  // そうでなければ数値を受理
  return new_num(expect_number());
}