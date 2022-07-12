#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include "pair.hpp"

namespace ft
{
	template <typename _Key, typename _Tp, typename _Compare = std::less<_Key>,
				typename _Alloc = std::allocator<ft::pair<const _Key, _Tp> > >
		class map
		{
			public:
				typedef _Key							key_type;
				typedef _Tp								mapped_type;
				typedef ft::pair<const _Key, _Tp>		value_type;
				typedef _Compare						key_compare;
				typedef _Alloc							allocator_type;
			
			private:
				typedef _Rb_tree<key_type, value_type, key_compare> Rep_type;
				
				Rep_type	m_tree;

			public:
				typedef typename allocator_type::pointer			pointer;
				typedef typename allocator_type::const_pointer		const_pointer;
				typedef typename allocator_type::reference			reference;
				typedef typename allocator_type::const_reference	const_reference;
				typedef typename Rep_type::iterator					iterator;
				typedef typename Rep_type::const_iterator			const_iterator;
				typedef typename Rep_type::size_type				size_type;
				typedef typename Rep_type::difference_type			difference_type;
				typedef typename Rep_type::reverse_iterator			reverse_iterator;
				typedef typename Rep_type::const_reverse_iterator	const_reverse_iterator;

				map()
				: m_tree() { }
			
				explicit
				map(const _Compare& comp,
				const allocator_type& a = allocator_type())
				: m_tree(comp, a) { }
			
				map(const map& x)
				: m_tree(x.m_tree) { }

				//...//

				map&
				operator=(const map& x)
				{
					m_tree = x.m_tree;
					return (*this);
				}

				allocator_type
				get_allocator() const
				{ return m_tree.get_allocator(); }

				// __iterators__
				iterator
				begin()
				{ return m_tree.begin(); }

				const_iterator
				begin() const
				{ return m_tree.begin(); }

				iterator
				end()
				{ return m_tree.end(); }

				const_iterator
				end() const
				{ return m_tree.end(); }

				reverse_iterator
				rbegin()
				{ return m_tree.rbegin(); }

				const_reverse_iterator
				rbegin() const
				{ return m_tree.rbegin(); }

				reverse_iterator
				rend()
				{ return m_tree.rend(); }

				const_reverse_iterator
				rend() const
				{ return m_tree.rend(); }

				// __capacity__
				bool
				empty() const
				{ return m_tree.empty(); }

				size_type
				size() const
				{ return m_tree.size(); }

				size_type
				max_size() const
				{ return m_tree.max_size(); }

		};
}

#endif