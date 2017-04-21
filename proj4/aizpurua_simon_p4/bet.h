#ifndef BET_H_
#define BET_H_

#include <iostream>
#include <cctype>
#include <stack>
#include <utility>
#include <sstream>
#include <algorithm>

using namespace std;

class BET {

public:
  BET();
  BET(const string& postfix);
  BET(const BET& );
  const BET& operator=(const BET& );
  ~BET();

  bool buildFromPostfix(const string& postfix);
  void printInfixExpression();
  void printPostfixExpression();
  bool empty();

  size_t size();
  size_t leaf_nodes();

  struct BinaryNode {
    string element;
    BinaryNode *left;
    BinaryNode *right;

    BinaryNode( string& theElement, BinaryNode *lt = nullptr, BinaryNode *rt = nullptr )
      : element{theElement}, left{lt}, right{rt} { }

    BinaryNode( const string& theElement, BinaryNode *lt = nullptr, BinaryNode *rt = nullptr )
      : element{theElement}, left{lt}, right{rt} { }

    BinaryNode( const string && theElement, BinaryNode *lt = nullptr, BinaryNode *rt = nullptr )
      : element{ std::move(theElement) }, left{lt}, right{rt} { }
  };

private:


  BinaryNode *root;

  void printInfixExpression(BinaryNode *n);
  void makeEmpty(BinaryNode* &t);
  BinaryNode* clone(BinaryNode *t);
  void printPostfixExpression(BinaryNode *n);
  size_t size(BinaryNode *t);
  size_t leaf_nodes(BinaryNode *t);

};

#include "bet.hpp"
#endif
