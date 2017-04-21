//////////////////////////////////////////////////
/////                                        /////
/////   class const_iterator                 /////
//////////////////////////////////////////////////

//  Zero parameter constructor
//     note: set current to nullptr
template <typename T>
List<T>::const_iterator::const_iterator() : current{ nullptr } {}

// Protected - One parameter constructor
//    note: set current to node pointer passed
template <typename T>
List<T>::const_iterator::const_iterator(Node *p) : current{p} {}

//  Retrieve element
template<typename T>
const T & List<T>::const_iterator::operator*() const { return this->retrieve(); }

// Post-fix
template<typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator++() {
  current = current->next;
  return *this;
}

// Pre-fix
template<typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++( int ) {
  const_iterator old = *this;
  ++(*this);
  return old;
}

// Post-fix
template<typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator--() {
  current = current->prev;
  return *this;
}

// Pre-fix
template<typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator--( int ) {
  const_iterator old = *this;
  --(*this);
  return old;
}

// Equality
template <typename T>
bool List<T>::const_iterator::operator==( const const_iterator &rhs ) const {
  return current == rhs.current;
}

// Inequality
template <typename T>
bool List<T>::const_iterator::operator!=( const const_iterator &rhs ) const {
  return !(*this == rhs);
}

// Fetch corresponding element
template <typename T>
T& List<T>::const_iterator::retrieve() const { return current->data; }

//////////////////////////////////////////////////
/////                                        /////
/////   class iterator                       /////
//////////////////////////////////////////////////

template<typename T>
List<T>::iterator::iterator() {}

template<typename T>
List<T>::iterator::iterator(Node *p) : const_iterator{p} {}

template<typename T>
T & List<T>::iterator::operator*() { return this->retrieve(); }

template<typename T>
const T& List<T>::iterator::operator*() const {
  return this->retrieve();
}

//  pre-fix
template<typename T>
typename List<T>::iterator & List<T>::iterator::operator++() {
  this->current = this->current->next;
  return *this;
}

//  post-fix
template<typename T>
typename List<T>::iterator List<T>::iterator::operator++(int) {
  iterator old = *this;
  ++( *this );
  return old;
}

//  pre-fix
template<typename T>
typename List<T>::iterator & List<T>::iterator::operator--() {
  this->current = this->current->prev;
  return *this;
}

//  post-fix
template<typename T>
typename List<T>::iterator List<T>::iterator::operator--(int) {
  iterator old = *this;
  --( *this );
  return old;
}

//////////////////////////////////////////////////
/////                                        /////
/////   class List                           /////
//////////////////////////////////////////////////
template<typename T>
List<T>::List() { init(); }

template<typename T>
List<T>::List ( const List & rhs) {
  init();
  for ( auto & x : rhs )
    push_back( x );
}

template<typename T>
List<T>::List( List && rhs)
  : theSize{ rhs.theSize }, head{ rhs.head }, tail{ rhs.tail } {
    rhs.theSize = 0;
    rhs.head = nullptr;
    rhs.tail = nullptr;
}

template<typename T>
List<T>::List(int num, const T& val) {
  init();
  for (auto i = 0; i < num; ++i)
    push_back(val);
}

template<typename T>
List<T>::List(List<T>::const_iterator start, List<T>::const_iterator end) {
  init();
  for (auto i = start; i != end; ++i) { push_back(*i); }
}

template<typename T>
List<T>::List(std::initializer_list<T> iList) {
  init();
  for (auto i = iList.begin(); i != iList.end(); ++i)
    push_back(*i);
}

template<typename T>
List<T>::~List() {
  clear();
  delete head;
  delete tail;
}

// Copy Constructor
template<typename T>
const List<T> & List<T>::operator=( const List & rhs ) {
  List<T> copy = rhs;
    return *this;
}

// Move constructor
template<typename T>
List<T> & List<T>::operator= ( List && rhs ) {
  std::swap( theSize, rhs.theSize );
  std::swap( head, rhs.head );
  std::swap( tail, rhs.tail );

  return *this;
}

template<typename T>
List<T> & List<T>::operator=( std::initializer_list<T> iList ) {
  List<T> copy = iList;
  std::swap( *this, copy );
  return *this;
}

template<typename T>
int List<T>::size() const { return theSize; }

template<typename T>
bool List<T>::empty() const { return size() == 0; }

template<typename T>
void List<T>::clear() {
  while(!empty()) { pop_front(); }
}

template<typename T>
void List<T>::reverse() {
  if(!this->empty()) {
    auto current = head;
    while( current != nullptr ) {
      std::swap(current->next, current->prev);
      current = current->prev;
    }
    std::swap(head, tail);
  }
}

template<typename T>
T& List<T>::front() { return *begin(); }

template<typename T>
const T& List<T>::front() const { return *begin(); }

template<typename T>
T& List<T>::back() { return *--end(); }

template<typename T>
const T& List<T>::back() const { return *--end(); }

template<typename T>
void List<T>::push_front(const T & val) {  insert( begin(), val ); }

template<typename T>
void List<T>::push_front(T && val) {  insert( begin(), std::move(val) ); }

template<typename T>
void List<T>::push_back(const T & val) {  insert( end(), val ); }

template<typename T>
void List<T>::push_back( T && val) {  insert( end(), std::move(val) ); }

template<typename T>
void List<T>::pop_front() { erase( begin() ); }

template<typename T>
void List<T>::pop_back() {  erase( --end() ); }

template<typename T>
void List<T>::remove(const T &val) {
  if(!this->empty()) {
    for ( auto i = begin(); i != end(); ++i)
      if(*i == val ) erase (i);
  }
}

template<typename T>
template<typename PREDICATE>
void List<T>::remove_if(PREDICATE pred) {
  for(auto i = begin(); i != end(); ++i)
    if(pred(*i))
      erase(i);
}

template<typename T>
void List<T>::print(std::ostream& os, char ofc) const {
  for (auto i = begin(); i != end(); ++i)
    os << *i << ofc;
}

template<typename T>
typename List<T>::iterator List<T>::begin() { return { head-> next }; }

template<typename T>
typename List<T>::const_iterator List<T>::begin() const { return { head-> next }; }

template<typename T>
typename List<T>::iterator List<T>::end() { return { tail }; }

template<typename T>
typename List<T>::const_iterator List<T>::end() const { return { tail }; }

template<typename T>
typename List<T>::iterator List<T>::insert( iterator itr, const T& val) {
  Node *p = itr.current;
  theSize++;
  return { p->prev = p->prev->next = new Node{ val, p->prev, p} };
}

template<typename T>
typename List<T>::iterator List<T>::insert( iterator itr, T&& val) {
  Node *p = itr.current;
  theSize++;
  return { p->prev = p->prev->next
            = new Node{ std::move(val), p->prev, p} };
}

template<typename T>
typename List<T>::iterator List<T>::erase( iterator i ) {
  Node *p = i.current;
  iterator retVal{ p-> next };
  p->prev->next = p->next;
  p->next->prev = p->prev;
  delete p;
  theSize--;

  return retVal;
}

template<typename T>
typename List<T>::iterator List<T>::erase ( iterator from, iterator to ) {
  for( iterator itr = from; itr != to; )
    itr = erase( itr );
    return to;
}

template<typename T>
void List<T>::init() {
  theSize = 0;
  head = new Node;
  tail = new Node;
  head->next = tail;
  tail->prev = head;
}

template <typename T>
bool operator==(const List<T> & lhs, const List<T> &rhs) {
  if (lhs.size() != rhs.size()) return false;
  for (auto itr_lhs = lhs.begin(), itr_rhs = rhs.begin(); itr_lhs != lhs.end(); ++itr_lhs, ++itr_rhs) {
    if (*itr_lhs != *itr_rhs) return false;
  }

  return true;
}

template <typename T>
bool operator!=(const List<T> & lhs, const List<T> &rhs) {
  return !( lhs == rhs );
}

// overloading output operator
template <typename T>
std::ostream & operator<<(std::ostream &os, const List<T> &l) {
  l.print(os);
  return os;
}
