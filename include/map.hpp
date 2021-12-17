#pragma once
#include <functional>

namespace ft {
template <
	class Key,
	class T,
	class Compare = std::less<Key>,
	class Allocator = std::allocator<std::pair<const Key, T> /**/> /**/>
class map {
  public:
	typedef Key									   key_type;
	typedef T									   mapped_type;
	typedef std::pair<key_type, mapped_type>	   value_type;
	typedef size_t								   size_type;
	typedef ptrdiff_t							   difference_type;
	typedef Compare								   key_compare;
	typedef Allocator							   allocator_type;
	typedef value_type&							   reference;
	typedef const value_type&					   const_reference;
	typedef typename allocator_type::pointer	   pointer;
	typedef typename allocator_type::const_pointer const_pointer;
};
} // namespace ft
