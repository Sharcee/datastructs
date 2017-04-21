#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <sstream>
#include "stack.h"

using namespace std;
using namespace cop4530;

bool isOperator(string s) {
  if ( s == "+" || s == "-" || s == "*" || s == "/")
    return true;
 return false;
}

int findPrecedence (string s) {
  if (s == "*" || s == "/") return 1;
  else if (s == "+" || s == "-") return 0;

  return -1;
}
void print(vector<string> v) {
  for (auto it: v)
    cout << it + " ";
}

double evaluate(vector<string> v) {
  if (v.empty())
    return 0;

  Stack<string> oper_stack;
  for (const auto& it: v) {
    if (!isOperator(it)) oper_stack.push(it);
    else {

      double first = stod(oper_stack.top());
      oper_stack.pop();
      double second = stod(oper_stack.top());
      oper_stack.pop();

      if      (it[0] == '+') second = second + first;
      else if (it[0] == '-') second = second - first;
      else if (it[0] == '*') second = second * first;
      else                second = second / first;

      oper_stack.push(to_string(second));
    }
  }

  return stod(oper_stack.top());
}

vector<string> in2post(const vector<string>& v) {
  Stack<string> operator_stack;
  vector<string> postfix;

  //int errflag = 0;

  for (unsigned i = 0; i < v.size(); i++) {
    if(!isOperator(v[i]) && v[i] != "(" && v[i] != ")")
      postfix.push_back(v[i]);

    else if (isOperator(v[i])) {
      while(operator_stack.top() != "(" &&
            findPrecedence(operator_stack.top()) >=
              findPrecedence(v[i]))
      {
        postfix.push_back(operator_stack.top());
        operator_stack.pop();
      }

      operator_stack.push(v[i]);

    }
    else if ( v[i] == "(" ) operator_stack.push(v[i]);
    else if ( v[i] == ")" ) {
      while (!operator_stack.empty()) {

        if (operator_stack.top() == "(") {
          operator_stack.pop();
          break;
        }
        postfix.push_back(operator_stack.top());
        operator_stack.pop();

      } // end while
    } // else if
  } // for loop

  while(!operator_stack.empty()) {
    postfix.push_back(operator_stack.top());
    operator_stack.pop();
  }

  return postfix;
} // end function

int main() {
  string topostFix = "";
  vector<string> infix;

  do {
    if ( cin.eof() )
      break;

    printf("Enter infix expression (\"exit\" to quit): ");
    getline(cin, topostFix);
    if (topostFix == "exit")
      break;

    stringstream oss{topostFix};
    while (oss >> topostFix) {
      infix.push_back(topostFix);
    }

    infix = in2post(infix);
    if(!infix.empty()) {
      printf("\nPostfix expression: ");
      print(infix);
      bool variableflag = false;
      for (auto it: infix)
        for (unsigned i = 0; i < it.length(); i++)
          if (isalpha(it[i])) variableflag = true;

      if(!variableflag) {
        printf("\nPostfix evaluation: ");
        print(infix);
        cout << " = " << evaluate(infix) << endl;
      } else {
        printf("\nPostfix evaluation: ");
        print(infix);
        printf(" = ");
        print(infix);
        printf("\n");
      }

      infix.clear();
    }
  } while( !cin.eof() );

  return 0;
}
