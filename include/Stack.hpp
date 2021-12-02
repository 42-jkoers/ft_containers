#pragma once

#include "Vector.hpp"

namespace ft {

template <class T, class Container = ft::vector<T> /**/>
class stack {
  public:
	typedef T		  value_type;
	typedef Container container_type;
	typedef size_t	  size_type;
	typedef T&		  reference;
	typedef const T&  const_reference;

	explicit stack(const Container& cont = Container()) : c(cont) {}
	stack<T, Container>& operator=(const stack<T, Container>& o) {
		c = o.c;
		return *this;
	}
	~Stack() {}

	reference		top() { return c.back(); }
	const_reference top() const { return c.back(); }
	bool			empty() const { return c.empty(); }
	size_type		size() const { return c.size(); }
	void			push(const value_type& val) { c.push_back(val); }
	void			pop() { c.pop_back(); }

	//
	friend bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs);
	friend bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs);
	friend bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs);
	friend bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs);
	friend bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs);
	friend bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs);

  protected:
	container_type c;
};

template <class T, typename Container /**/>
bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return lhs.c == rhs.c; }
template <class T, typename Container /**/>
bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return lhs.c != rhs.c; }
template <class T, typename Container /**/>
bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return lhs.c < rhs.c; }
template <class T, typename Container /**/>
bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return lhs.c <= rhs.c; }
template <class T, typename Container /**/>
bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return lhs.c > rhs.c; }
template <class T, typename Container /**/>
bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return lhs.c >= rhs.c; }

} // namespace ft
