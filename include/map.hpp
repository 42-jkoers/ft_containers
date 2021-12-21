#pragma once
#include <functional>
#include <memory>

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

	map(const key_compare& cmp = key_compare())
		: _tree(value_compare(cmp)) {}

	template <typename InputIt>
	map(InputIt			   first,
		InputIt			   last,
		const key_compare& cmp = key_compare(),
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
		: _tree(first, last, value_compare(cmp)) {}

	map(const _Self& o)
		: _tree(o._tree) {}

	~map() {}

	// getters and setters
	std::allocator<T> get_allocator() const { return _allocator; }
	// access
	T& at(const Key& key);

  private:
	std::allocator<T> _allocator;
};
} // namespace ft
