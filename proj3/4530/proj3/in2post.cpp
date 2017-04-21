// Jorge Gonzalez
// Project 3
// 23 June 2016

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <sstream>
#include "stack.h"

using namespace std;
using namespace cop4530;

bool isOperator(string s) {
  if (s == "+" || s == "-" ||
      s == "*" || s == "/")
    return true;
  return false;
}

int precedence(string s) {
  if (s == "*" || s == "/")
    return 1;
  else if (s == "+" || s == "-")
    return 0;
  return -1;
}

vector<string> in2post(const vector<string> v) {
  // convert infix expression to postfix expression
  Stack<string> operators;
  vector<string> post;

  // convert to postfix
  for (uint i = 0; i < v.size(); i++) {

    // check for operands
    if (!isOperator(v[i]) &&
        // parentheses will be handled separately
        v[i] != "(" && v[i] != ")") {
      post.push_back(v[i]);

    } else if (isOperator(v[i])) {
      // push operators to the operator stack and check for precedence
      while (operators.top() != "(" &&
             precedence(operators.top()) >= precedence(v[i])) {
        post.push_back(operators.top());
        operators.pop();
      }

      operators.push(v[i]);

    } else if (v[i] == "(") {
      // always push
      operators.push(v[i]);

    } else if (v[i] == ")")
      // check for matching parentheses
      while (!operators.empty()) {
        if (operators.top() == "(") {
          operators.pop();
          break;
        }

        post.push_back(operators.top());
        operators.pop();

      } // if-else block
  } // for-loop

  while (!operators.empty()) {
    // push remaining operators to postfix vector
    post.push_back(operators.top());
    operators.pop();
  }

  return post;
} // in2post

double evalPost(vector<string> post) {
  // evaluate an infix expression that is stored in a vector of strings
  if (post.empty()) {
      return 0;
  }

  Stack<string> ops; // Stack will store operators

  for (const auto& s : post) {
    if (!isOperator(s)) {
      // push operators
      ops.push(s);

    } else {
      // stod is used to convert from strings to double
      int y = stod(ops.top());
      ops.pop();

      int x = stod(ops.top());
      ops.pop();

      // evaluate
      if (s[0] == '+')
        x += y;
      else if (s[0] == '-')
        x -= y;
      else if (s[0] == '*')
        x *= y;
      else
        x /= y;

      // push the value of the operation to the top of the stack
      ops.push(to_string(x));
    }
  }

  // the most recent value will be at the top
  return stod(ops.top());
} // evalPost

void printVector(vector<string> v) {
  // print contents of a vector of strings
  for (auto i : v)
    cout << i + " ";
} // printVector

int main() {
  // convert and evaluate a series of infix expressions from stdin
  string expression = "";
  vector<string> infix;

  do {

    if (cin.eof())
      break;

    cout << "Enter infix expression (\"exit\" to quit): ";

    getline(cin, expression);
    if (expression == "exit")
      break;

    // parse the string by whitespace
    stringstream ss(expression);
    while (ss >> expression)
      strVec.push_back(expression);

    strVec = in2post(strVec);

    if (!strVec.empty()) {
      cout << "\nPostfix expression: ";

      // print contents of strVec
      printVector(strVec);

      // check for chars in strVec
      bool chars = false;
      for (auto s : strVec) {
        for (uint i = 0; i < s.length(); i++) {
          if (isalpha(s[i])) {
            chars = true;
          }
        }
      }

      if (!chars) {
        // call evalPost if strVec has no chars
        cout << "\nPostfix evaluation: ";
        printVector(strVec);
        cout << " = " << evalPost(strVec) << endl;

      } else {
        cout << "\nPostfix evaluation: ";
        printVector(strVec);
        cout << " = ";
        printVector(strVec);
        cout << endl;
      }

     strVec.clear();   // empty the vector
    }
  } while (!cin.eof());

  return 0;
}
