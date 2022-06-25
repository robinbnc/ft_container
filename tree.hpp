#ifndef TREE_HPP
# define TREE_HPP

namespace ft
{
	enum rb_tree_color { _rb_red = false, _rb_black = true };

	template<typename Val>
		struct	s_tree_node
		{
			typedef	t_tree_node*		m_ptr;
			typedef	const t_tree_node*	m_const_ptr;

			Val				m_value;
			rb_tree_color	m_color;
			m_ptr			m_parent;
			m_ptr			m_left;
			m_ptr			m_right;

			static m_ptr
			minimum(m_ptr x)
			{
				while (x->m_left != 0)
					x = x->m_left;
				return (x);
			}

			static m_const_ptr
			minimum(m_const_ptr x)
			{
				while (x->m_left != 0)
					x = x->m_left;
				return (x);
			}

			static m_ptr
			maximum(m_ptr x)
			{
				while (x->m_right != 0)
					x = x->m_right;
				return (x);
			}

			static m_const_ptr
			maximum(m_const_ptr x)
			{
				while (x->m_right != 0)
					x = x->m_right;
				return (x);
			}
		};
}

#endif