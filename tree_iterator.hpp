#ifndef TREE_ITERATOR
# define TREE_ITERATOR

# include "tree.hpp"

namespace ft
{
	template<typename T>
		struct Rb_tree_iterator
		{
			typedef T  value_type;
			typedef T& reference;
			typedef T* pointer;

			typedef std::bidirectional_iterator_tag	iterator_category;
			typedef ptrdiff_t						difference_type;

			typedef Rb_tree_iterator<T>				_Self;
			typedef struct s_tree_node<T>::m_ptr	_Base_ptr;
			typedef struct s_tree_node<T>*			_Link_type;

			Rb_tree_iterator()
			: m_node() { }
		
			explicit
			Rb_tree_iterator(_Link_type __x)
			: m_node(__x) { }
		
			reference
			operator*() const
			{ return (*m_node->m_value); }
		
			pointer
			operator->() const // pas sur du tout recheck
			{ return ((m_node)->m_value); }
		
			_Self&
			operator++()
			{
				m_node = Rb_tree_increment(m_node);
				return (*this);
			}
		
			_Self
			operator++(int)
			{
				_Self tmp = *this;
				m_node = Rb_tree_increment(m_node);
				return (tmp);
			}
		
			_Self&
			operator--()
			{
				m_node = Rb_tree_decrement(m_node);
				return (*this);
			}
		
			_Self
			operator--(int)
			{
				_Self tmp = *this;
				m_node = Rb_tree_decrement(m_node);
				return (tmp);
			}
		
			bool
			operator==(const _Self& x) const
			{ return (m_node == x.m_node); }
		
			bool
			operator!=(const _Self& x) const
			{ return (m_node != x.m_node); }

			_Base_ptr m_node;

			private:
				_Base_ptr
				Rb_tree_increment(_Base_ptr node)
				{
					if (node->m_right != NULL)
						return (node->m_right->minimum(node->m_right));
					if (node->isOnLeft() && node->m_parent != NULL)
							return (node->m_parent);
					else if (node->m_parent != NULL ) // possible segfault check grand parent
						return (node->m_parent->m_parent);
				}

				_Base_ptr
				Rb_tree_decrement(_Base_ptr node)
				{
					if (node->m_left != NULL)
						return (node->m_left->maximum(node->m_left));
					if (!node->isOnLeft() && node->m_parent != NULL)
							return (node->m_parent);
					else if (node->m_parent != NULL ) // possible segfault check grand parent
						return (node->m_parent->m_parent);
				}
	};
}

#endif