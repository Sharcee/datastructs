// Jorge Gonzalez
// Project 3
// 23 June 2016

#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <list>

namespace cop4530 {
template<typename T>
class Stack {
 public:
  // default constructor and destructor
  Stack();
  ~Stack();

  // copy constructors
  Stack(const Stack<T>&);
  Stack(Stack<T>&&);

  // assignment overloads
  Stack<T>& operator=(const Stack<T>&);
  Stack<T>& operator=(Stack<T>&&);

  // standard accessors
  int size() const;
  bool empty() const;
  void clear();

  T& top();
  const T& top() const;

  void print(std::ostream& os, char ofc = ' ') const;

  std::list<T> getList() const;   // returns a copy of lst

  // standard mutators
  void push(const T& x);
  void push(T&& x);
  void pop();

 private:
  std::list<T> lst;   // Stack will be implemented with a std::list
}; // class Stack

  // comparison overloads
  template<typename T>
  std::ostream& operator<<(std::ostream& os, const Stack<T>& a);

  template<typename T>
  bool operator==(const Stack<T>&, const Stack<T>&);

  template<typename T>
  bool operator!=(const Stack<T>&, const Stack<T>&);

  template<typename T>
  bool operator<=(const Stack<T>&, const Stack<T>&);

#include "stack.hpp"

} // namespace cop4530

#endif // STACK_H
