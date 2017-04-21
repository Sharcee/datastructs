bool isOperator(string s) {
  if ( s == "+" || s == "-" || s == "*" || s == "/")
    return true;
 return false;
}

bool isOperand(string s) {
    if (!isOperator(s) && s != "(" && s != ")")
        return true;
    return false;
}

int findPrecedence (string s) {
  if (s == "*" || s == "/") return 2;
  else if (s == "+" || s == "-") return 1;
  else return 0;
}

BET::BET() : root {nullptr} { }
BET::BET(const string& postfix) : root {nullptr} {
  buildFromPostfix(postfix);
}
BET::BET(const BET& t) : root{ nullptr } {
  root = clone(t.root);
}
const BET& BET::operator=(const BET& t) {
  makeEmpty(root);
  root = clone(t.root);
  return *this;
}
BET::~BET() {
  makeEmpty(root);
}
bool BET::buildFromPostfix(const string& postfix) {
  if(postfix.empty()) {
    printf("Wrong postfix expression\n");
    return false;
  }

  stack<BinaryNode*> poststack;
  stringstream s(postfix);
  string temp = "";

  makeEmpty(root);

  while(s >> temp) {
    if (isOperand(temp)) {
      BinaryNode *node = new BinaryNode(temp);
      poststack.push(node);
    }else if(isOperator(temp)) {
      BinaryNode *node = new BinaryNode(temp);

      node->right = poststack.top();
      poststack.pop();

      node->left = poststack.top();
      poststack.pop();

      poststack.push(node);
    }
  }

  root = poststack.top();

  if(poststack.empty()) {
    printf("Wrong postfix expression\n");
    return false;
  }

  poststack.pop();
  if (!poststack.empty()) {
    makeEmpty(root);
    return false;
  }

  return true;
}

void BET::printInfixExpression() {
  if(empty()) printf("Error: Wrong postfix expression\n");
  else {
    printInfixExpression(root);
    cout << endl;
  }
}
void BET::printPostfixExpression() {
  if(empty()) printf("Error: Wrong postfix expression\n");
  else {
    printPostfixExpression(root);
    cout << endl;
  }
}
bool BET::empty() {
  if(root == nullptr) return true;
  return false;
}
size_t BET::size() {
  return size(root);
}
size_t BET::leaf_nodes() {
  return leaf_nodes(root);
}
void BET::printInfixExpression(BinaryNode *n) {
  if (n != nullptr) {
    if(!isOperator(n->element))
      cout << n->element;
    else {
      if (n != root)
        cout << "(";

      printInfixExpression(n->left);
      cout << " " << n->element << " ";
      printInfixExpression(n->right);

      if (n != root)
        cout << ")";
    }
  }
} //end func

void BET::makeEmpty(BinaryNode* &t) {
  if ( t != nullptr) {
    makeEmpty( t-> left);
    makeEmpty( t-> right);
    delete t;
  }
  t = nullptr;
}
BET::BinaryNode* BET::clone(BinaryNode *t) {
  if( t == nullptr )
    return nullptr;
  else
    return new BinaryNode{ t-> element, clone( t-> left), clone( t->right ) };
}

void BET::printPostfixExpression(BinaryNode *n) {
  if (n != nullptr) {
    printPostfixExpression(n->left);
    printPostfixExpression(n->right);
    cout << n->element << " ";
  }
}
size_t BET::size(BinaryNode *t) {
  if (t == nullptr)
    return 0;
  else {
    int cntr = 1;
    cntr += size(t->left);
    cntr += size(t->right);
    return cntr;
  }
}
size_t BET::leaf_nodes(BinaryNode *t) {
  if (t == nullptr) return 0;
  if (t->left == nullptr && t->right == nullptr) return 1;
  else return leaf_nodes(t->left) + leaf_nodes(t->right);
}
