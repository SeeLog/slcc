#include "slcc.h"

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "引数の個数が正しくありません\n");
    return 1;
  }

  // トークナイズする
  // 結果は code に保存される
  user_input = argv[1];
  token = tokenize(user_input);
  Program *prog = program();

  int offset = 0;
  for (LVar *lvar = prog->locals; lvar; lvar = lvar->next) {
    offset += 8;
    lvar->offset = offset;
  }

  for (Node *node = prog->node; node; node = node->next) {
    fprintf(stderr, "kind: %d\n", node->kind);
  }

  prog->stack_size = offset;

  codegen(prog);

  return 0;
}
