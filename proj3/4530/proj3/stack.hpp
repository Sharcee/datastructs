// Jorge Gonzalez
// Project 3
// 23 June 2016

template<typename T>
Stack<T>::Stack() {
  /* list is already initialized and empty */
}

template<typename T>
Stack<T>::~Stack() {
  /* lst's destructor will be called so this is unnecessary */
}

// member functions are easily implemented
// by calling std::list's corresponding member functions

template<typename T>
Stack<T>::Stack(const Stack<T>& s) {
  // copy constructor
  lst = s.lst;
}

template<typename T>
Stack<T>::Stack(Stack<T>&& s) {
  // move constructor
  lst = move(s.lst);
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& s) {
  // copy assignment
  lst = s.lst;
  return *this;
}

template<typename T>
Stack<T>& Stack<T>::operator=(Stack<T>&& s) {
  // move assignment
  lst = move(s.lst);
  return *this;
}

template<typename T>
bool Stack<T>::empty() const {
  return lst.empty();
}

template<typename T>
void Stack<T>::clear() {
  lst.clear();
}

template<typename T>
void Stack<T>::push(const T& x) {
  lst.push_back(x);
}

template<typename T>
void Stack<T>::push(T&& x) {
  // move version of push(const T&)
  lst.push_back(move(x));
}

template<typename T>
void Stack<T>::pop() {
  lst.pop_back();
}

template<typename T>
T& Stack<T>::top() {
  return lst.back();
}

template<typename T>
const T& Stack<T>::top() const {
  return lst.back();
}

template<typename T>
int Stack<T>::size() const {
  return int(lst.size());
}

template<typename T>
void Stack<T>::print(std::ostream& os, char ofc) const {
  // iterate through lst to print all elements in the Stack
  for (auto i = lst.begin(); i != lst.end(); i++) {
    os << *i << ofc;
  }
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Stack<T>& a) {
   //invokes the print() method to print the Stack<T> a in the specified ostreas
  a.print(os);
  return os;
}

template<typename T>
std::list<T> Stack<T>::getList() const {
  // for use with comparison overloads
  return lst;
}

template<typename T>
bool operator==(const Stack<T>& s1, const Stack<T>& s2) {
    // returns true if the two compared Stacks have the same elements, in the same order, and false otherwise
  return s1.getList() == s2.getList();
}

template<typename T>
bool operator!=(const Stack<T>& s1, const Stack<T>& s2) {
  // opposite of operator==().
  return s1.getList() != s2.getList();
}

template<typename T>
bool operator<=(const Stack<T>& s1, const Stack<T>& s2) {
  // returns true if every element in Stack a is smaller than or equal to the corresponding
  // element of Stack b, i.e., if repeatedly invoking top() and pop() on both a and b,
  // we will generate a sequence of elements ai from a and bi from b, and for every i,  ai ≤ bi, until a is empty.
  return s1.getList() <= s2.getList();
}
