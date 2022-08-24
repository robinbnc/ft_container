#include "print_vector.hpp"

#ifndef NAME_SPACE
# define NAME_SPACE std
#endif

using namespace NAME_SPACE;

#define TESTED_TYPE foo<int>

template <typename Ite_1, typename Ite_2>
void ft_eq_ope(const Ite_1 &first, const Ite_2 &second, const bool redo = 1)
{
	std::cout << (first < second) << std::endl;
	std::cout << (first <= second) << std::endl;
	std::cout << (first > second) << std::endl;
	std::cout << (first >= second) << std::endl;
	if (redo)
		ft_eq_ope(second, first, 0);
}

int		main(void)
{
	{
		const int size = 5;
		NAME_SPACE::vector<TESTED_TYPE> vct(size);
		NAME_SPACE::vector<TESTED_TYPE>::reverse_iterator it(vct.rbegin());
		NAME_SPACE::vector<TESTED_TYPE>::const_reverse_iterator ite(vct.rend());

		for (int i = 1; it != ite; ++i)
			*it++ = (i * 7);
		printSize(vct, 1);

		it = vct.rbegin();
		ite = vct.rbegin();

		std::cout << *(++ite) << std::endl;
		std::cout << *(ite++) << std::endl;
		std::cout << *ite++ << std::endl;
		std::cout << *++ite << std::endl;

		it->m();
		ite->m();

		std::cout << *(++it) << std::endl;
		std::cout << *(it++) << std::endl;
		std::cout << *it++ << std::endl;
		std::cout << *++it << std::endl;

		std::cout << *(--ite) << std::endl;
		std::cout << *(ite--) << std::endl;
		std::cout << *--ite << std::endl;
		std::cout << *ite-- << std::endl;

		(*it).m();
		(*ite).m();

		std::cout << *(--it) << std::endl;
		std::cout << *(it--) << std::endl;
		std::cout << *it-- << std::endl;
		std::cout << *--it << std::endl;
	}
	{
		const int size = 5;
		NAME_SPACE::vector<TESTED_TYPE> vct(size);
		NAME_SPACE::vector<TESTED_TYPE>::reverse_iterator it(vct.rbegin());
		NAME_SPACE::vector<TESTED_TYPE>::const_reverse_iterator ite(vct.rend());

		for (int i = 1; it != ite; ++i)
			*it++ = (i * 7);
		printSize(vct, 1);

		it = vct.rbegin();
		ite = vct.rbegin();

		std::cout << *(++ite) << std::endl;
		std::cout << *(ite++) << std::endl;
		std::cout << *ite++ << std::endl;
		std::cout << *++ite << std::endl;

		it->m();
		ite->m();

		std::cout << *(++it) << std::endl;
		std::cout << *(it++) << std::endl;
		std::cout << *it++ << std::endl;
		std::cout << *++it << std::endl;

		std::cout << *(--ite) << std::endl;
		std::cout << *(ite--) << std::endl;
		std::cout << *--ite << std::endl;
		std::cout << *ite-- << std::endl;

		(*it).m();
		(*ite).m();

		std::cout << *(--it) << std::endl;
		std::cout << *(it--) << std::endl;
		std::cout << *it-- << std::endl;
		std::cout << *--it << std::endl;
	}
	{
		const int size = 5;
		NAME_SPACE::vector<TESTED_TYPE> vct(size);
		NAME_SPACE::vector<TESTED_TYPE>::reverse_iterator it_0(vct.rbegin());
		NAME_SPACE::vector<TESTED_TYPE>::reverse_iterator it_1(vct.rend());
		NAME_SPACE::vector<TESTED_TYPE>::reverse_iterator it_mid;

		NAME_SPACE::vector<TESTED_TYPE>::const_reverse_iterator cit_0 = vct.rbegin();
		NAME_SPACE::vector<TESTED_TYPE>::const_reverse_iterator cit_1;
		NAME_SPACE::vector<TESTED_TYPE>::const_reverse_iterator cit_mid;

		for (int i = size; it_0 != it_1; --i)
			*it_0++ = i;
		printSize(vct, 1);
		it_0 = vct.rbegin();
		cit_1 = vct.rend();
		it_mid = it_0 + 3;
		cit_mid = it_0 + 3; cit_mid = cit_0 + 3; cit_mid = it_mid;

		std::cout << std::boolalpha;
		std::cout << ((it_0 + 3 == cit_0 + 3) && (cit_0 + 3 == it_mid)) << std::endl;

		std::cout << "\t\tft_eq_ope:" << std::endl;
		// regular it
		ft_eq_ope(it_0 + 3, it_mid);
		ft_eq_ope(it_0, it_1);
		ft_eq_ope(it_1 - 3, it_mid);
		// const it
		ft_eq_ope(cit_0 + 3, cit_mid);
		ft_eq_ope(cit_0, cit_1);
		ft_eq_ope(cit_1 - 3, cit_mid);
		// both it
		ft_eq_ope(it_0 + 3, cit_mid);
		ft_eq_ope(it_mid, cit_0 + 3);
		ft_eq_ope(it_0, cit_1);
		ft_eq_ope(it_1, cit_0);
		ft_eq_ope(it_1 - 3, cit_mid);
		ft_eq_ope(it_mid, cit_1 - 3);
	}
	return (0);
}
