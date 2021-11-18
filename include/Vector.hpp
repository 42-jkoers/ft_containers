#pragma once
#include <iostream>
#include <limits>
#include <memory>
#define STARTSIZE 1

namespace ft {

template <typename T>
class vector {
  public:
	typedef typename std::size_t size_type;

	vector<T>() : _content(NULL), _capacity(0), _length(0){};
	~vector<T>(){};

	void push_back(const T& x) {
		if (!_capacity)
			_grow(STARTSIZE);
		else if (_length == _capacity)
			_grow(_capacity * 2);
		_content[_length++] = x;
	}

	void reserve(size_type new_cap) {
		// TODO: allocator exception
		// TODO: If an exception is thrown, this function has no effect
		if (new_cap > max_size())
			throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
		if (new_cap <= _capacity)
			return;
		_grow(new_cap);
	}

	void clear() {
		std::memset(_content, 0, _length);
		_length = 0;
		size_type		  size() const { return _size; };
		size_type		  capacity() const { return _capacity; }
		size_type		  max_size() const { return (std::min((size_type)std::numeric_limits<ptrdiff_t>::max(), std::numeric_limits<size_type>::max() / sizeof(T))); }
		std::allocator<T> get_allocator() const { return _allocator; }
		T*				  data() const { return _content; }

	  protected:
	  private:
		void _grow(size_t newCapacity) {
			T* old = _content;
			_content = _allocator.allocate(newCapacity);
			_capacity = newCapacity;
			if (!old)
				return;
			std::memcpy(_content, old, _length * sizeof(T));
			_allocator.deallocate(old, _length);
		}
		T*				  _content;
		size_t			  _capacity;
		size_t			  _length;
		std::allocator<T> _allocator;
	};

} // namespace ft
