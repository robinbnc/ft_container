#include <vector>
#include <iostream>
#include <exception>
#include <memory>
#include "vector.hpp"
#include "print.hpp"
#include "iterator.hpp"
// #include "containers_test/srcs/base.hpp"
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
	map<int, char>	test;
	ft::Rb_tree<int, ft::pair<int, char>, std::less<ft::pair<char, int> > > test2;

	// test['a'] = 2;


	test.insert(std::pair<int ,char >(6, 'c'));
	test.insert(std::pair<int ,char >(2, 'd'));
	test.insert(std::pair<int ,char >(3, 'e'));
	test.insert(std::pair<int ,char >(4, 'f'));
	test.insert(std::pair<int ,char >(5, 'g'));
	test.insert(std::pair<int ,char >(11, 'h'));
	test.insert(std::pair<int ,char >(8, 'i'));
	test.insert(std::pair<int ,char >(15, 'j'));

	for (std::map<int, char>::iterator it = test.begin(); it != test.end(); it++)
		std::cout << it->first << std::endl;

	test2.insert(ft::pair<int, char>(6, 'c'));
	test2.insert(ft::pair<int, char>(2, 'd'));
	test2.insert(ft::pair<int, char>(3, 'e'));
	test2.insert(ft::pair<int, char>(4, 'f'));
	test2.insert(ft::pair<int, char>(5, 'g'));
	test2.insert(ft::pair<int, char>(11, 'h'));
	test2.insert(ft::pair<int, char>(8, 'i'));
	test2.insert(ft::pair<int, char>(15, 'j'));
	test2.insert(ft::pair<int, char>(16, 'j'));
	test2.insert(ft::pair<int, char>(17, 'j'));
	test2.insert(ft::pair<int, char>(18, 'j'));
	test2.insert(ft::pair<int, char>(19, 'j'));
	test2.insert(ft::pair<int, char>(20, 'j'));
	test2.insert(ft::pair<int, char>(21, 'j'));
	test2.insert(ft::pair<int, char>(22, 'j'));
	test2.insert(ft::pair<int, char>(23, 'j'));
	test2.insert(ft::pair<int, char>(24, 'j'));


	// test2.print2D();

	// test2.erase(ft::pair<int, char>(15, 'j'));
	test2.print2D();
	return (0);
}
