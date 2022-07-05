#include <vector>
#include <iostream>
#include <exception>
#include <memory>
#include "vector.hpp"
#include "print.hpp"
#include "iterator.hpp"
#include "containers_test/srcs/base.hpp"
#include "stack.hpp"
#include <stack>
#include <map>
#include "pair.hpp"
#include "tree.hpp"


#ifndef NAME_SPACE
	#define NAME_SPACE_STR "STD"
	using 	namespace std;
#else
	#define NAME_SPACE_STR "FT"
	using namespace ft;
#endif

#define TESTED_TYPE int
#define t_stack_ stack<TESTED_TYPE>
typedef ft::t_stack_::container_type container_type;

template <class T_STACK>
void	cmp(const T_STACK &lhs, const T_STACK &rhs)
{
	static int i = 0;

	std::cout << "############### [" << i++ << "] ###############"  << std::endl;
	std::cout << "eq: " << (lhs == rhs) << " | ne: " << (lhs != rhs) << std::endl;
	std::cout << "lt: " << (lhs <  rhs) << " | le: " << (lhs <= rhs) << std::endl;
	std::cout << "gt: " << (lhs >  rhs) << " | ge: " << (lhs >= rhs) << std::endl;
}


int		main(void)
{
	map<char, int>	test;
	ft::Rb_tree<char, ft::pair<char, int>, std::less<ft::pair<char, int> > > test2;

	// test['a'] = 2;


	test.insert(std::pair<char, int>('c', 6));
	test.insert(std::pair<char, int>('d', 2));
	test.insert(std::pair<char, int>('e', 3));
	test.insert(std::pair<char, int>('f', 4));
	test.insert(std::pair<char, int>('g', 5));


	test2.insert(ft::pair<char, int>('c', 1));
	test2.insert(ft::pair<char, int>('b', 2));
	test2.insert(ft::pair<char, int>('d', 3));
	test2.insert(ft::pair<char, int>('e', 4));
	test2.insert(ft::pair<char, int>('f', 5));
	// test2.insert(ft::pair<char, int>('g', 6));
	// test2.insert(ft::pair<char, int>('h', 7));
	// test2.insert(ft::pair<char, int>('i', 8));
	// test2.insert(ft::pair<char, int>('j', 9));


	test2.print2D();
	return (0);
}
