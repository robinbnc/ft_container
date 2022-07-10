#ifndef ITERATOR_BASE
# define ITERATOR_BASE

namespace ft
{
	template <class Iterator>
		struct iterator_traits
		{
			typedef typename Iterator::iterator_category iterator_category;
			typedef typename Iterator::value_type        value_type;
			typedef typename Iterator::difference_type   difference_type;
			typedef typename Iterator::pointer           pointer;
			typedef typename Iterator::reference         reference;
		};

	template <class T>
		struct iterator_traits<T*>
		{
			typedef std::random_access_iterator_tag		iterator_category;
			typedef T									value_type;
			typedef ptrdiff_t							difference_type;
			typedef T*									pointer;
			typedef T&									reference;
		};

	template <class T>
		class iterator_traits<const T*>
		{
			typedef std::random_access_iterator_tag		iterator_category;
			typedef T									value_type;
			typedef ptrdiff_t							difference_type;
			typedef const T*							pointer;
			typedef const T&							reference;
		};

	template <class Category, class T, class Distance = std::ptrdiff_t,
				class Pointer = T*, class Reference = T&>
		class iterator
		{
			public:
				typedef T         						value_type;
				typedef Distance  						difference_type;
				typedef Pointer   						pointer;
				typedef Reference 						reference;
				typedef Category  						iterator_category;
		};
}

#endif