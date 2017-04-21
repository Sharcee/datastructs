template <typename T>
Stack<T>::Stack() { }

template <typename T>
Stack<T>::~Stack() { l.clear(); }

template <typename T>
Stack<T>::Stack( const Stack<T> & rhs) { l = rhs.l; }

template <typename T>
Stack<T>::Stack( Stack<T> && rhs) { l = std::move(rhs.l); }

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T> & rhs) {
  l = rhs.l;
  return *this;
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack<T> && rhs) {
  l = std::move(rhs.l);
  return *this;
}

template <typename T>
void Stack<T>::push(const T& x) { l.push_back(x); }

template <typename T>
void Stack<T>::push(T && x) { l.push_back(std::move(x)); }

template <typename T>
void Stack<T>::pop() { l.pop_back(); }

template <typename T>
void Stack<T>::clear() { l.clear(); }

template <typename T>
bool Stack<T>::empty() const {
  return l.empty();
}

template <typename T>
T& Stack<T>::top() { return l.back(); }

template <typename T>
const T& Stack<T>::top() const { return l.back(); }

template <typename T>
int Stack<T>::size() const { return int(l.size()); }

template <typename T>
void Stack<T>::print(std::ostream& os, char ofc) const {
  for (auto i = l.begin(); i != l.end(); ++i)
    os << *i << ofc;
}

template <typename T>
std::list<T> Stack<T>::getList() const {
  return l;
}

template <typename T>
std::ostream& operator<< (std::ostream& os, const Stack<T>& s) {
  s.print(os);
  return os;
}

template <typename T>
bool operator== (const Stack<T>& lhs, const Stack <T>& rhs) {
  return lhs.getList() == rhs.getList();
}

template <typename T>
bool operator!= (const Stack<T>& lhs, const Stack <T>& rhs) {
  return !(lhs == rhs );
}

template <typename T>
bool operator<= (const Stack<T>& lhs, const Stack <T>& rhs) {
 return lhs.getList() <= rhs.getList();
}
