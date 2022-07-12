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
#include <unistd.h>
#include "map.hpp"


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
	ft::Rb_tree<int, ft::pair<int, char>, std::less<ft::pair<char, int> > > test2;
	ft::map<int, char>	test;

	test.insert(ft::pair<int ,char >(6, 'c'));
	test.insert(ft::pair<int ,char >(2, 'd'));
	test.insert(ft::pair<int ,char >(3, 'e'));
	test.insert(ft::pair<int ,char >(4, 'f'));
	test.insert(ft::pair<int ,char >(5, 'g'));
	test.insert(ft::pair<int ,char >(11, 'h'));
	test.insert(ft::pair<int ,char >(8, 'i'));
	test.insert(ft::pair<int ,char >(15, 'j'));

	const int t(6);
	test.erase(t);

	// std::cout << (test.upper_bound(1) == test.begin()) << "\n";
	// std::cout << test.upper_bound(7)->first << "\n";
	// std::cout << test.upper_bound(3)->first << "\n";
	// std::cout << test.upper_bound(12)->first << "\n";
	std::cout << test[2] << "\n";
	test[20] = 'c';
	std::cout << test[20] << "\n";
	// std::cout << (test.upper_bound(18) == test.end() ? "true" : "false") << "\n";
	// std::cout << ((*test.equal_range(3).second).first/*  == test.end() ? "true" : "false" */) << "\n";
	// std::cout << (test.find(1) == test.end() ? "true" : "false") << "\n";



	test.print();
	test.clear();
	// for (std::map<int, char>::iterator it = test.begin(); it != test.end(); it++)
	// 	std::cout << it->first << std::endl;
	// std::cout << "===================================" << std::endl;
	// for (std::map<int, char>::iterator it = ++test.end(); it != test.begin(); it--)
	// 	std::cout << it->first << std::endl;

	// std::cout << (test.find(1) == test.begin() ? "found" : "not found") << std::endl;

	// test2.insert(ft::pair<int, char>(6, 'c'));
	// test2.insert(ft::pair<int, char>(2, 'd'));
	// test2.insert(ft::pair<int, char>(2, 'd'));
	// test2.insert(ft::pair<int, char>(3, 'e'));
	// test2.insert(ft::pair<int, char>(4, 'f'));
	// test2.insert(ft::pair<int, char>(5, 'g'));
	// test2.insert(ft::pair<int, char>(11, 'h'));
	// test2.insert(ft::pair<int, char>(8, 'i'));
	// test2.insert(ft::pair<int, char>(15, 'j'));
	// test2.insert(ft::pair<int, char>(16, 'j'));
	// test2.insert(ft::pair<int, char>(17, 'j'));
	// test2.insert(ft::pair<int, char>(18, 'j'));
	// test2.insert(ft::pair<int, char>(19, 'j'));
	// test2.insert(ft::pair<int, char>(20, 'j'));
	// test2.insert(ft::pair<int, char>(21, 'j'));
	// test2.insert(ft::pair<int, char>(22, 'j'));
	// test2.insert(ft::pair<int, char>(23, 'j'));
	// test2.insert(ft::pair<int, char>(24, 'j'));


	// test2.print2D();


	// for (ft::Rb_tree<int, ft::pair<int, char>, std::less<ft::pair<char, int> > >::iterator it = test2.begin(); it != test2.end(); it++)
	// {
	// 	// sleep(1);
	// 	std::cout << it->first << std::endl;
	// }
	// std::cout << "===================================" << std::endl;
	// for (ft::Rb_tree<int, ft::pair<int, char>, std::less<ft::pair<char, int> > >::iterator it = --test2.end(); it != test2.begin(); it--)
	// {
	// 	// sleep(1);
	// 	std::cout << it->first << std::endl;
	// }
	// test2.insert(ft::pair<int, char>(25, 'j'));
	// test2.erase(ft::pair<int, char>(21, 'j'));
	// test2.insert(ft::pair<int, char>(26, 'j'));
	// test2.insert(ft::pair<int, char>(27, 'j'));
	// test2.insert(ft::pair<int, char>(28, 'j'));
	// test2.insert(ft::pair<int, char>(29, 'j'));
	// test2.insert(ft::pair<int, char>(29, 'j'));
	// test2.insert(ft::pair<int, char>(30, 'j'));
	// for (ft::Rb_tree<int, ft::pair<int, char>, std::less<ft::pair<char, int> > >::iterator it = test2.begin(); it != test2.end(); it++)
	// {
	// 	// sleep(1);
	// 	std::cout << it->first << std::endl;
	// }
	// std::cout << "===================================" << std::endl;
	// for (ft::Rb_tree<int, ft::pair<int, char>, std::less<ft::pair<char, int> > >::iterator it = --test2.end(); it != test2.begin(); it--)
	// {
	// 	// sleep(1);
	// 	std::cout << it->first << std::endl;
	// }
	// std::cout << test2.size() << "\n";

	// test2.clear();
	// std::cout << test2.size() << "\n";
	// test2.print2D();
	return (0);
}
