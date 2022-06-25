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
#include "pair.hpp"

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
	ft::pair<std::string, int>	test("hello", 1);

	std::cout << test.second << std::endl;
	// ctnr.push_back(21);
	// ctnr.push_back(42);
	// ctnr.push_back(1337);
	// ctnr.push_back(19);
	// ctnr.push_back(19);
	// ctnr.push_back(0);
	// ctnr.push_back(183792);
	stack<int>	 stck;
	// t_stack_	stck2(ctnr);

	// cmp(stck, stck);  // 0
	// cmp(stck, stck2); // 1
	// stck2.push(61);
	// stck2.push(62);

	// cmp(stck, stck2); // 2
	// cmp(stck2, stck); // 3

	// stck.push(42);

	// cmp(stck, stck2); // 4
	// cmp(stck2, stck); // 5

	// stck.push(100);

	// cmp(stck, stck2); // 6
	// cmp(stck2, stck); // 7
	return (0);
}
