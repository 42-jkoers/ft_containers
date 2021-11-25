#pragma once
#include <iostream>
#include <limits>
#include <memory>
#include <sstream>
#include <stdexcept>
#define STARTSIZE 1

namespace ft {

template <typename T>
class vector;

template <typename T>
class RandomAccessIterator {
  public:
	typedef RandomAccessIterator<T>			self;
	typedef size_t							size_type;
	typedef ptrdiff_t						difference_type;
	typedef T								value_type;
	typedef T*								pointer;
	typedef T&								reference;
	typedef std::random_access_iterator_tag iterator_category;

  public:
	RandomAccessIterator() : _p(NULL) {}
	RandomAccessIterator(const self& other) : _p(other._p) {}
	~RandomAccessIterator() {}

	self& operator=(const self& other) {
		_p = other._p;
		return *this;
	}
	self& operator++() {
		++_p;
		return *this;
	}
	self operator++(int) {
		self ite = *this;
		_p++;
		return ite;
	}
	self& operator--() {
		--_p;
		return *this;
	}
	self operator--(int) {
		self ite = *this;
		_p--;
		return ite;
	}
	self& operator+=(size_type offset) {
		_p += offset;
		return *this;
	}
	self& operator-=(size_type offset) {
		_p -= offset;
		return *this;
	}
	reference operator*() const { return *_p; }
	pointer	  operator->() const { return _p; }
	reference operator[](difference_type n) const { return *(*this + n); }

	template <typename T2>
	friend bool operator==(const RandomAccessIterator<T2>& lhs, const RandomAccessIterator<T2>& rhs);
	template <typename T2>
	friend bool operator!=(const RandomAccessIterator<T2>& lhs, const RandomAccessIterator<T2>& rhs);
	template <typename T2>
	friend bool operator<(const RandomAccessIterator<T2>& lhs, const RandomAccessIterator<T2>& rhs);
	template <typename T2>
	friend bool operator>(const RandomAccessIterator<T2>& lhs, const RandomAccessIterator<T2>& rhs);
	template <typename T2>
	friend bool operator<=(const self& lhs, const self& rhs);
	template <typename T2>
	friend bool operator>=(const self& lhs, const self& rhs);

	template <typename T2>
	friend RandomAccessIterator<T2> operator+(const RandomAccessIterator<T2>& ite, size_t offset);
	template <typename T2>
	friend RandomAccessIterator<T2> operator+(size_t offset, const RandomAccessIterator<T2>& ite);

	template <typename T2>
	friend RandomAccessIterator<T2> operator-(const RandomAccessIterator<T2>& ite, size_t offset);
	template <typename T2>
	friend RandomAccessIterator<T2> operator-(size_t offset, const RandomAccessIterator<T2>& ite);

	template <typename T2>
	friend ptrdiff_t operator-(const RandomAccessIterator<T2>& lhs, const RandomAccessIterator<T2>& rhs);
	template <typename T2>
	friend ptrdiff_t operator+(const RandomAccessIterator<T2>& lhs, const RandomAccessIterator<T2>& rhs);

	template <typename T2>
	friend class vector;

  private:
	pointer _p;
	RandomAccessIterator(pointer elem) : _p(elem) {}
};

template <typename T>
bool operator==(const RandomAccessIterator<T>& lhs, const RandomAccessIterator<T>& rhs) { return lhs._p == rhs._p; }

template <typename T>
bool operator!=(const RandomAccessIterator<T>& lhs, const RandomAccessIterator<T>& rhs) { return lhs._p != rhs._p; }

template <typename T>
bool operator<(const RandomAccessIterator<T>& lhs, const RandomAccessIterator<T>& rhs) { return lhs._p < rhs._p; }

template <typename T>
bool operator>(const RandomAccessIterator<T>& lhs, const RandomAccessIterator<T>& rhs) { return lhs._p > rhs._p; }

template <typename T>
bool operator<=(const RandomAccessIterator<T>& lhs, const RandomAccessIterator<T>& rhs) { return lhs._p <= rhs._p; }

template <typename T>
bool operator>=(const RandomAccessIterator<T>& lhs, const RandomAccessIterator<T>& rhs) { return lhs._p >= rhs._p; }

template <typename T>
RandomAccessIterator<T> operator+(const RandomAccessIterator<T>& ite, size_t offset) {
	RandomAccessIterator<T> res = ite;
	return res += offset;
}
template <typename T>
RandomAccessIterator<T> operator+(size_t offset, const RandomAccessIterator<T>& ite) { return ite + offset; }

template <typename T>
RandomAccessIterator<T> operator-(const RandomAccessIterator<T>& ite, size_t offset) {
	RandomAccessIterator<T> res = ite;
	return res -= offset;
}
template <typename T>
RandomAccessIterator<T> operator-(size_t offset, const RandomAccessIterator<T>& ite) { return ite - offset; }

template <typename T>
ptrdiff_t operator+(const RandomAccessIterator<T>& lhs, const RandomAccessIterator<T>& rhs) { return lhs._p + rhs._p; }
template <typename T>
ptrdiff_t operator-(const RandomAccessIterator<T>& lhs, const RandomAccessIterator<T>& rhs) { return lhs._p - rhs._p; }

template <typename T>
class vector {
  public:
	typedef T						value_type;
	typedef T*						pointer;
	typedef const T*				const_pointer;
	typedef T&						reference;
	typedef const T&				const_reference;
	typedef size_t					size_type;
	typedef ptrdiff_t				difference_type;
	typedef RandomAccessIterator<T> iterator;
	typedef RandomAccessIterator<T> const_iterator;

	vector() : _content(NULL), _capacity(0), _length(0){};
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

	iterator erase(iterator position) {
		iterator erased(position);
		while (position != end() - 1) {
			position[0] = position[1];
			position++;
		}
		_length--;
		return erased;
	}
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

		size_t insertAtI = pos._p - _content;
		for (size_t i = _length - 1; i >= insertAtI; i--) { // move elements to the right
			_allocator.construct(&_content[i + count], _content[i]);
			_allocator.destroy(&_content[i]);
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

} // namespace ft
