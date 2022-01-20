#pragma once
#include <limits>
#include <stddef.h>
#include <stdint.h>

namespace ft {

// enable_if
template <bool b, class T = void>
struct enable_if {};
template <class T>
struct enable_if<true, T> { typedef T type; };

// iterator tags
template <class>
struct has_type { typedef void type; };
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

// SFINAE iterator validation
template <class T>
struct has_iterator_tags {
	typedef char valid[1];
	typedef char invalid[2];

	template <class U>
	static invalid& test(...);

	template <class U> // I don't know why it needs this extra wrapper but oh well
	static valid&	  test(typename ft::has_type<typename U::iterator_category>::type* = 0,
						   typename ft::has_type<typename U::value_type>::type* = 0,
						   typename ft::has_type<typename U::pointer>::type* = 0,
						   typename ft::has_type<typename U::reference>::type* = 0,
						   typename ft::has_type<typename U::difference_type>::type* = 0);

	static const bool value = sizeof(test<T>(0, 0, 0, 0, 0)) == sizeof(valid);
};

template <typename T>
struct is_pointer {
	static const bool value = false;
};

template <typename T>
struct is_pointer<T*> {
	static const bool value = true;
};

template <typename T>
struct is_pointer<const T*> {
	static const bool value = true;
};

template <class Iterator> // ?
struct iterator_traits {
	typedef typename Iterator::difference_type	 difference_type;
	typedef typename Iterator::value_type		 value_type;
	typedef typename Iterator::pointer			 pointer;
	typedef typename Iterator::reference		 reference;
	typedef typename Iterator::iterator_category iterator_category;
};

template <class T>
struct iterator_traits<T*> {
	typedef ptrdiff_t					   difference_type;
	typedef T							   value_type;
	typedef T*							   pointer;
	typedef T&							   reference;
	typedef ft::random_access_iterator_tag iterator_category;
};

template <class T>
class iterator_traits<const T*> {
	typedef ptrdiff_t					   difference_type;
	typedef T							   value_type;
	typedef const T*					   pointer;
	typedef const T&					   reference;
	typedef ft::random_access_iterator_tag iterator_category;
};

template <class T1, class T2>
struct pair {
	typedef T1	first_type;
	typedef T2	second_type;

	first_type	first;
	second_type second;

	pair() : first(), second() {}

	template <class U1, class U2>
	pair(const pair<U1, U2>& p) : first(p.first), second(p.second) {}

	pair(const T1& x, const T2& y) : first(x), second(y) {}

	pair& operator=(const pair& x) {
		first = x.first;
		second = x.second;
		return *this;
	}
};

template <class T1, class T2>
bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) { return lhs.first == rhs.first && lhs.second == rhs.second; }

template <class T1, class T2>
bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) { return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second); }

template <class T1, class T2>
bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) { return !(lhs == rhs); }

template <class T1, class T2>
bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) { return (rhs < lhs); }

template <class T1, class T2>
bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) { return !(rhs < lhs); }

template <class T1, class T2>
bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) { return !(lhs < rhs); }

template <class T1, class T2>
pair<T1, T2> make_pair(T1 x, T2 y) { return pair<T1, T2>(x, y); }

// integral types:
// bool
// char
// char16_t
// char32_t
// wchar_t
// short
// int
// long
// long long int	// C++11

template <bool is_integral, typename T>
struct integral_constant {
	typedef T		  type;
	static const bool value = is_integral;
};

template <typename INVALID>
struct is_integral_type : public integral_constant<false, int> {};

template <>
struct is_integral_type<bool> : public integral_constant<true, bool> {};

template <>
struct is_integral_type<char> : public integral_constant<true, char> {};

template <>
struct is_integral_type<short> : public integral_constant<true, short> {};

template <>
struct is_integral_type<int> : public integral_constant<true, int> {};

template <>
struct is_integral_type<long> : public integral_constant<true, long> {};

// template <> // C++11
// struct is_integral_type<long long> : public integral_constant<true, long long> {};

template <>
struct is_integral_type<unsigned char> : public integral_constant<true, unsigned char> {};

template <>
struct is_integral_type<unsigned short> : public integral_constant<true, unsigned short> {};

template <>
struct is_integral_type<unsigned int> : public integral_constant<true, unsigned int> {};

template <>
struct is_integral_type<unsigned long> : public integral_constant<true, unsigned long> {};

// template <> // C++11
// struct is_integral_type<unsigned long long> : public integral_constant<true, unsigned long long> {};

template <typename T>
struct is_integral : public is_integral_type<T> {};

} // namespace ft
