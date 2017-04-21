#ifndef STACK_H_
#define STACK_H_

#include <list>
#include <iostream>

namespace cop4530 {

template <typename T>
class Stack {
public:
  Stack();
  ~Stack();
  Stack( const Stack<T> & );
  Stack( Stack<T> && );
  Stack<T>& operator=(const Stack<T> & );
  Stack<T>& operator=(Stack<T> &&);

  int size() const;
  bool empty() const; //done
  void clear();       //done

  void push(const T& x);
  void push(T && x);
  void pop();

  std::list<T> getList() const;

  T& top();
  const T& top() const;

  void print(std::ostream& os, char ofc = ' ') const;

private:
  std::list<T> l;
}; //end class Stack

template<typename T>
std::ostream& operator<< (std::ostream& os, const Stack<T>& s);

template<typename T>
bool operator== (const Stack<T>& lhs, const Stack <T>& rhs);

template<typename T>
bool operator!= (const Stack<T>& lhs, const Stack <T>& rhs);

template<typename T>
bool operator<= (const Stack<T>& lhs, const Stack <T>& rhs);

#include "stack.hpp"

} // end cop4530 namespace
#endif
