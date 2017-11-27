#ifndef PARSER_INFO_H
#define PARSER_INFO_H

#include <string>
#include <stack>
#include <queue>
#include "node.h"
#include "term.h"

using std::queue;
using std::stack;
using std::string;

class ParserInfo
{
private:
  stack<Node *> nodes;
  stack<string> ops;
  
public:
  void clearAll();
  void pushNode(Node *node);
  void pushOp(string op);
  Node *popNode();
  Node *peekNode();
  string popOp();
  string peekOp();
  int getPriority(string op);
  Operators getOperators(string op);

};

#endif
