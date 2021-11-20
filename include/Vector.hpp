#pragma once
#include <iostream>
#include <limits>
#include <memory>
#include <sstream>
#include <stdexcept>
#define STARTSIZE 1

namespace ft {

template <typename T>
class vector {
  public:
	typedef T		  value_type;
	typedef T*		  pointer;
	typedef const T*  const_pointer;
	typedef T&		  reference;
	typedef const T&  const_reference;
	typedef size_t	  size_type;
	typedef ptrdiff_t difference_type;

	vector<T>() : _content(NULL), _capacity(0), _length(0){};
	~vector<T>(){};

	void push_back(const T& x) {
		if (!_capacity)
			reserve(STARTSIZE);
		else if (_length == _capacity)
			reserve(_capacity * 2);
		_content[_length++] = x;
	}

	void reserve(size_t new_cap) {
		if (new_cap <= _capacity)
			return;
		if (new_cap > max_size())
			throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");

		T* old = _content;
		_content = _allocator.allocate(new_cap);
		_capacity = new_cap;
		if (!old)
			return;
		std::memcpy(_content, old, _length * sizeof(T));
		_allocator.deallocate(old, _length);
	}

	void clear() {
		std::memset(_content, 0, _length);
		_length = 0;
	}

	size_type		  size() const { return _length; };
	size_type		  capacity() const { return _capacity; }
	size_type		  max_size() const { return (std::min((size_type)std::numeric_limits<ptrdiff_t>::max(), std::numeric_limits<size_type>::max() / sizeof(T))); }
	std::allocator<T> get_allocator() const { return _allocator; }
	T*				  data() const { return _content; }

  protected:
  private:
	T*				  _content;
	size_t			  _capacity;
	size_t			  _length;
	std::allocator<T> _allocator;
};

} // namespace ft
