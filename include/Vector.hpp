#pragma once
#include "iterator_traits.hpp"
#include "other.hpp"
#include <cmath>
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
	typedef T*		  iterator;
	typedef const T*  const_iterator;

	vector() : _content(NULL), _capacity(0), _length(0){};

	vector(size_type count, const value_type& value = value_type()) : _content(NULL), _length(0), _capacity(0) {
		insert(begin(), count, value);
	}

	template <typename InputIt>
	vector(InputIt first, InputIt last, typename ft::enable_if<ft::has_iterator_tags<InputIt>::value>::type* = 0) : _content(NULL), _length(0), _capacity(0) {
		insert(begin(), first, last);
	}

	vector(const vector<T>& other) : _content(NULL), _length(0), _capacity(0) {
		insert(begin(), other.begin(), other.end());
	}

	~vector() {
		if (!_content)
			return;
		for (size_type i = 0; i < _length; i++)
			_allocator.destroy(&_content[i]);
		_allocator.deallocate(_content, _capacity);
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
		for (size_type i = 0; i < _length; i++) {
			_allocator.construct(&_content[i], old[i]);
			_allocator.destroy(&old[i]);
		}
		_allocator.deallocate(old, _length);
	}

	void push_back(const T& x) {
		if (!_capacity)
			reserve(STARTSIZE);
		else if (_length == _capacity)
			reserve(_capacity * 2);
		_content[_length++] = x;
	}
	void	 pop_back() { _length--; }
	void	 clear() { _length = 0; }

	iterator erase(iterator pos) { return erase(pos, pos + 1); }
	iterator erase(iterator first, iterator last) { // TODO: if first > last?
		iterator lastCopy(last);
		while (last != end()) {
			*first = *last;
			++first;
			++last;
		}
		_length -= std::abs(last - first);
		return lastCopy;
	}

	void swap(vector<T>& other) {
		std::swap(_content, other._content);
		std::swap(_length, other._length);
		std::swap(_capacity, other._capacity);
	}

	iterator insert(iterator pos, const value_type& value) {
		insert(pos, 1, value);
		return pos;
	}

	void insert(iterator pos, size_type count, const value_type& value) {
		if (!count)
			return;
		reserve(_length + count);

		size_t insertAtI = pos - _content;
		if (_length) {
			for (size_t i = _length - 1; i >= insertAtI; i--) { // move elements to the right
				_allocator.construct(&_content[i + count], _content[i]);
				_allocator.destroy(&_content[i]);
			}
		}
		for (size_t i = insertAtI; i < count + insertAtI; i++)
			_allocator.construct(&_content[i], value);
		_length += count;
	}

	// getters
	size_type		  size() const { return _length; };
	size_type		  capacity() const { return _capacity; }
	size_type		  max_size() const { return std::min((size_type)std::numeric_limits<ptrdiff_t>::max(), std::numeric_limits<size_type>::max() / sizeof(T)); }
	std::allocator<T> get_allocator() const { return _allocator; }
	T*				  data() const { return _content; }
	bool			  empty() const { return _length == 0; }

	// access
	reference		operator[](size_type pos) { return _content[pos]; }
	const_reference operator[](size_type pos) const { return _content[pos]; }
	//
	reference at(size_type pos) {
		if (pos >= _length)
			throw std::out_of_range("vector");
		return _content[pos];
	}
	const_reference at(size_type pos) const {
		if (pos >= _length)
			throw std::out_of_range("vector");
		return _content[pos];
	}
	reference		front() { return _content[0]; }
	const_reference front() const { return _content[0]; }
	reference		back() { return _content[_length - 1]; }
	const_reference back() const { return _content[_length - 1]; }

	iterator		begin() { return iterator(_content); }
	const_iterator	begin() const { return const_iterator(_content); }
	iterator		end() { return iterator(&_content[_length]); }
	const_iterator	end() const { return const_iterator(&_content[_length]); }

  private:
	T*				  _content;
	size_t			  _capacity;
	size_t			  _length;
	std::allocator<T> _allocator;
};

template <typename T>
bool operator==(const vector<T>& lhs, const vector<T>& rhs) {
	return lhs.size() == rhs.size() && equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename T>
bool operator!=(const vector<T>& lhs, const vector<T>& rhs) { return !(lhs == rhs); }

template <typename T>
bool operator<(const vector<T>& lhs, const vector<T>& rhs) {
	return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename T>
bool operator<=(const vector<T>& lhs, const vector<T>& rhs) { return !(lhs > rhs); }

template <typename T>
bool operator>(const vector<T>& lhs, const vector<T>& rhs) { return rhs < lhs; }

template <typename T>
bool operator>=(const vector<T>& lhs, const vector<T>& rhs) { return !(lhs < rhs); }

template <typename T>
void swap(vector<T>& lhs, vector<T>& rhs) { rhs.swap(lhs); }
} // namespace ft
