#pragma once
#include <limits>

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

} // namespace ft
