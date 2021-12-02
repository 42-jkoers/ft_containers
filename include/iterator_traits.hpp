#pragma once
#include <limits>

namespace ft {

template <class>
struct validate_type { typedef void type; };
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <class T>
struct has_iterator_typedefs {
	typedef char valid[1];
	typedef char invalid[2];

	template <class U>
	static invalid& test(...);

	template <class U> // I don't know why it needs this extra wrapper but oh well
	static valid& test(typename ft::validate_type<typename U::iterator_category>::type* = 0,
					   typename ft::validate_type<typename U::value_type>::type* = 0,
					   typename ft::validate_type<typename U::pointer>::type* = 0,
					   typename ft::validate_type<typename U::reference>::type* = 0,
					   typename ft::validate_type<typename U::difference_type>::type* = 0);
	// template <class U>
	// static valid&	  test(typename U::iterator_category*,
	// 					   typename U::value_type*,
	// 					   typename U::pointer*,
	// 					   typename U::reference*,
	// 					   typename U::difference_type*);

	static const bool value = sizeof(test<T>(0, 0, 0, 0, 0)) == sizeof(valid);
};

template <class Iter, bool>
struct _iterator_traits {};

template <class Iter>
struct _iterator_traits<Iter, true> {
	typedef typename Iter::iterator_category iterator_category;
	typedef typename Iter::value_type		 value_type;
	typedef typename Iter::pointer			 pointer;
	typedef typename Iter::reference		 reference;
	typedef typename Iter::difference_type	 difference_type;
};

template <class Iter>
struct iterator_traits : public _iterator_traits<Iter, has_iterator_typedefs<Iter>::value> {};
template <class T>
struct iterator_traits<T*> {
	typedef ft::random_access_iterator_tag iterator_category;
	typedef T							   value_type;
	typedef T*							   pointer;
	typedef T&							   reference;
	typedef ptrdiff_t					   difference_type;
};

template <class T>
struct iterator_traits<const T*> {
	typedef ft::random_access_iterator_tag iterator_category;
	typedef T							   value_type;
	typedef const T*					   pointer;
	typedef const T&					   reference;
	typedef ptrdiff_t					   difference_type;
};
} // namespace ft
