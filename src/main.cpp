#include "Vector.hpp"
#include <cassert>
#include <iostream>
#include <limits>
#include <memory>
#include <vector>

#define T int
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
		v.push_back(3);
		j.push_back(3);
		for (size_t i = 0; i < 10; i++) {
			assert(v.size() == j.size());
			v.pop_back();
			j.pop_back();
		}
	}
	// std::allocator<std::string> alloc;
	// std::string*				p = alloc.allocate(100);
	// p[0] = "aaaa";
	// std::cout << p[0] << std::endl;

	return 0;
}
