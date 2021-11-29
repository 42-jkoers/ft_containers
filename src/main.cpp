#include "Vector.hpp"
#include <cassert>
#include <iostream>
#include <limits>
#include <memory>
#include <vector>

#define T int

void print_vector(ft::vector<int>& v) {
	for (ft::vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

int main() {
	{ // ::capacity()
		std::vector<int> v;
		ft::vector<int>	 j;
		for (size_t i = 0; i < 1000000; i++) {
			assert(v.capacity() == j.capacity());
			v.push_back(3);
			j.push_back(3);
		}
	}
	{ // ::reserve()
		std::vector<int> v;
		ft::vector<int>	 j;
		v.reserve(42);
		j.reserve(42);
		assert(v.capacity() == j.capacity());
		v.reserve(1);
		j.reserve(1);
		assert(v.capacity() == j.capacity());

		try {
			v.reserve(SIZE_T_MAX);
		} catch (const std::exception& v) {
			try {
				j.reserve(SIZE_T_MAX);
			} catch (const std::exception& j) {
				assert(!strcmp(v.what(), j.what()));
			}
		}
	}
	{ // ::max_size()
		{
			std::vector<int> v;
			ft::vector<int>	 j;
			assert(v.max_size() == j.max_size());
		}
		{
			std::vector<char> v;
			ft::vector<char>  j;
			assert(v.max_size() == j.max_size());
		}
		{
			std::vector<std::string> v;
			ft::vector<std::string>	 j;
			assert(v.max_size() == j.max_size());
		}
	}
	{ // ::size
		std::vector<int> v;
		ft::vector<int>	 j;
		for (size_t i = 0; i < 10; i++) {
			assert(v.size() == j.size());
			v.push_back(3);
			j.push_back(3);
		}
	}

	{ // ::get_allocator
	}

	{ // ::clear()
		std::vector<int> v;
		ft::vector<int>	 j;
		for (size_t i = 0; i < 10; i++) {
			v.push_back(3);
			j.push_back(3);
		}
		v.clear();
		j.clear();
		assert(v.size() == j.size());
		assert(v.capacity() == j.capacity());
	}

	{ // ::data
		std::vector<int> v;
		ft::vector<int>	 j;
		assert(v.data() == j.data());
		// TODO: more tests
	}
	{ // ::at(size_type pos)
		std::vector<int> v;
		ft::vector<int>	 j;
		for (size_t i = 0; i < 10; i++) {
			v.push_back(3);
			j.push_back(3);
		}
		assert(v.at(4) == j.at(4));
		try {
			int a = v.at(SIZE_T_MAX);
			(void)a;
		} catch (const std::exception& v) {
			try {
				int a = j.at(SIZE_T_MAX);
				(void)a;
			} catch (const std::exception& j) {
				assert(!strcmp(v.what(), j.what()));
			}
		}
	}
	{ // ::pop_back()
		std::vector<int> v;
		ft::vector<int>	 j;
		for (size_t i = 0; i < 10; i++) {
			v.push_back(3);
			j.push_back(3);
			assert(v.size() == j.size());
			v.pop_back();
			j.pop_back();
		}
	}
	{ // iterator
		std::vector<int> v;
		ft::vector<int>	 j;
		for (size_t i = 0; i < 10; i++) {
			v.push_back(i);
			j.push_back(i);
		}
		std::vector<int>::iterator it_v = v.begin();
		ft::vector<int>::iterator  it_j = j.begin();
		while (it_v != v.end() && it_j != j.end()) {
			assert(*it_v == *it_j);
			it_v++;
			it_j++;
		}
	}
	{ // ::erase()
		std::vector<int> v;
		ft::vector<int>	 j;

		for (size_t i = 0; i < 1000; i++) {
			v.push_back(i);
			j.push_back(i);
		}

		v.erase(v.begin());
		j.erase(j.begin());
		v.erase(2 + v.begin() - 1, v.begin() + 5);
		j.erase(2 + j.begin() - 1, j.begin() + 5);

		for (std::vector<int>::iterator it = v.begin(); it != v.end();) {
			if (*it % 2 == 0) {
				it = v.erase(it);
			} else {
				++it;
			}
		}
		for (ft::vector<int>::iterator it = j.begin(); it != j.end();) {
			if (*it % 2 == 0) {
				it = j.erase(it);
			} else {
				++it;
			}
		}
		for (size_t i = 0; i < 10; i++)
			assert(v[i] == j[i]);
	}
	{ // ::insert()
		std::vector<int> v;
		ft::vector<int>	 j;
		for (size_t i = 0; i < 10; i++) {
			v.push_back(i);
			j.push_back(i);
		}
		v.insert(v.begin() + 2, 4, 42);
		j.insert(j.begin() + 2, 4, 42);
		for (size_t i = 0; i < 14; i++)
			assert(v[i] == j[i]);
	}
	{ // operator==
		std::vector<int> v;
		std::vector<int> v1;
		ft::vector<int>	 j;
		ft::vector<int>	 j1;
		assert((v == v1) == (j == j1));
		for (size_t i = 0; i < 10; i++) {
			v.push_back(i);
			v1.push_back(i);
			j.push_back(i);
			j1.push_back(i);
		}
		assert((v == v1) == (j == j1));
		v[v.size() - 1] = 500;
		j[j.size() - 1] = 500;
		assert((v == v1) == (j == j1));
		j.pop_back();
		v.pop_back();
		assert((v == v1) == (j == j1));
	}
	{ // copy constructor
		std::vector<int> v;
		std::vector<int> v1;
		ft::vector<int>	 j;
		ft::vector<int>	 j1;
		for (size_t i = 0; i < 10; i++) {
			v.push_back(i);
			j.push_back(i);
		}
		v = v1;
		j = j1;
		assert((v == v1) == (j == j1));
	}
	// std::allocator<std::string> alloc;
	// std::string*				p = alloc.allocate(100);
	// p[0] = "aaaa";
	// std::cout << p[0] << std::endl;

	return 0;
}
