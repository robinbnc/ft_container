#ifndef TREE_HPP
# define TREE_HPP

# include <memory>
# include <iostream>
# include <stdio.h>
# include "pair.hpp"
#define COUNT 10

namespace ft
{
	enum rb_tree_color { _rb_red = false, _rb_black = true };

	template<typename Val>
		struct	s_tree_node
		{
			typedef	struct	s_tree_node	t_tree_node;
			typedef	t_tree_node*		m_ptr;
			typedef	const t_tree_node*	m_const_ptr;

			Val				*m_value;
			rb_tree_color	m_color;
			m_ptr			m_parent;
			m_ptr			m_left;
			m_ptr			m_right;


			s_tree_node()
			:  m_value(NULL), m_color(_rb_red), m_parent(NULL), m_left(NULL), m_right(NULL) 
			{}

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

		template<typename Key, typename Val/* Pair */,
				typename Compare, typename Alloc = std::allocator<Val> >
		class Rb_tree
		{
			public:
				typedef	struct	s_tree_node<Val>	tree_node;
				typedef std::allocator<tree_node>	Node_allocator;
				typedef std::size_t					size_type;

			protected:
				Node_allocator	m_node_allocator;
				Alloc			m_val_allocator;
				tree_node		m_header;
				size_type		m_node_count;

			private:

				bool
				_M_is_root(tree_node *node)
				{ return (node == m_header.m_parent); }

				tree_node*
				_M_get_root( void )
				{ return (m_header.m_parent); }
				
				tree_node*
				createNode(Val value)
				{
					tree_node	*ret;

					ret = m_node_allocator.allocate(1);
					m_node_allocator.construct(ret, tree_node());
					ret->m_value = m_val_allocator.allocate(1);
					m_val_allocator.construct(ret->m_value, value);
					return (ret);
				}

				tree_node*
				BSTInsert(tree_node* root, tree_node *pt)
				{
					// std::less<Val> _comp;
				    /* If the tree is empty, return a new node */
				    if (root == NULL)
				       return pt;

				    /* Otherwise, recur down the tree */
				    if (/* _comp.operator(pt->m_value, root->m_value)) */ pt->m_value < root->m_value)
				    {
				        root->m_left  = BSTInsert(root->m_left, pt);
				        root->m_left->m_parent = root;
				    }
				    else if (pt->m_value > root->m_value)
				    {
				        root->m_right = BSTInsert(root->m_right, pt);
				        root->m_right->m_parent = root;
				    }
				    return (root);
				}

				void
				rotateLeft(tree_node *x)//normalement ok tester
				{
					tree_node	*x_parent = x->m_parent;
					tree_node	*x_right_child = x->m_right;

					x->m_right = x_right_child->m_left;
					if (x_right_child->m_left)
						x_right_child->m_left->m_parent = x;

					x_right_child->m_parent = x_parent;
					if (this->_M_is_root(x))
						m_header.m_parent = x_right_child;
					else if (x_parent->m_left == x)
						x_parent->m_left = x_right_child;
					else
						x_parent->m_right = x_right_child;

					x_right_child->m_left = x;
					x->m_parent = x_right_child;
				}

				void rotateRight(tree_node *pt)
				{
				    tree_node *pt_left = pt->m_left;
				
				    pt->m_left = pt_left->m_right;
				    if (pt->m_left != NULL)
				        pt->m_left->m_parent = pt;

				    pt_left->m_parent = pt->m_parent;
				    if (this->_M_is_root(pt))
				    	m_header.m_parent = pt_left;
				    else if (pt == pt->m_parent->m_left)
				        pt->m_parent->m_left = pt_left;
				    else
				        pt->m_parent->m_right = pt_left;

				    pt_left->m_right = pt;
				    pt->m_parent = pt_left;
				}

				void fixViolation(tree_node *root, tree_node *pt)
				{
				    tree_node *parent_pt = NULL;
				    tree_node *grand_parent_pt = NULL;

				    while ((pt != root) && (pt->m_color != _rb_black) &&
				           (pt->m_parent->m_color == _rb_red))
				    {
					
				        parent_pt = pt->m_parent;
				        grand_parent_pt = pt->m_parent->m_parent;

				        /*  Case : A
				            Parent of pt is left child
				            of Grand-parent of pt */
				        if (parent_pt == grand_parent_pt->m_left)
				        {
						
				            tree_node *uncle_pt = grand_parent_pt->m_right;

							/* Case : 1
								The uncle of pt is also red
								Only Recoloring required */
				            if (uncle_pt != NULL && uncle_pt->m_color ==
																	_rb_red)
				            {
				                grand_parent_pt->m_color = _rb_red;
				                parent_pt->m_color = _rb_black;
				                uncle_pt->m_color = _rb_black;
				                pt = grand_parent_pt;
				            }

				            else
				            {
				                /* Case : 2
				                   pt is right child of its parent
				                   Left-rotation required */
				                if (pt == parent_pt->m_right)
				                {
				                    rotateLeft(parent_pt);
				                    pt = parent_pt;
				                    parent_pt = pt->m_parent;
				                }

				                /* Case : 3
				                   pt is left child of its parent
				                   Right-rotation required */
				                rotateRight(grand_parent_pt);
								rb_tree_color	tmp = parent_pt->m_color;
								parent_pt->m_color = grand_parent_pt->m_color;
								grand_parent_pt->m_color = tmp;
				                pt = parent_pt;
				            }
				        }

				        /* Case : B
				           Parent of pt is right child
				           of Grand-parent of pt */
				        else
				        {
				            tree_node *uncle_pt = grand_parent_pt->m_left;

				            /*  Case : 1
				                The uncle of pt is also red
				                Only Recoloring required */
				            if ((uncle_pt != NULL) && (uncle_pt->m_color ==
				                                                    _rb_red))
				            {
				                grand_parent_pt->m_color = _rb_red;
				                parent_pt->m_color = _rb_black;
				                uncle_pt->m_color = _rb_black;
				                pt = grand_parent_pt;
				            }
				            else
				            {
				                /* Case : 2
				                   pt is left child of its parent
				                   Right-rotation required */
				                if (pt == parent_pt->m_left)
				                {
				                    rotateRight(parent_pt);
				                    pt = parent_pt;
				                    parent_pt = pt->m_parent;
				                }

				                /* Case : 3
				                   pt is right child of its parent
				                   Left-rotation required */
				                rotateLeft(grand_parent_pt);
								rb_tree_color	tmp = parent_pt->m_color;
								parent_pt->m_color = grand_parent_pt->m_color;
								grand_parent_pt->m_color = tmp;
								pt = parent_pt;
				            }
				        }
				    }

				    root->m_color = _rb_black;
				}

			public:
				void print2DUtil(tree_node *root, int space)
				{
					if (root == NULL)
						return;

					space += COUNT;
					print2DUtil(root->m_right, space);
					std::cout<< std::endl;
					for (int i = COUNT; i < space; i++)
						std::cout<<" ";
					if (root->m_value != NULL)
						std::cout<< *root->m_value <<"\n";
					else
						std::cout<< "NODE" <<"\n";
					print2DUtil(root->m_left, space);
				}

				void print2D()
				{
					this->print2DUtil(_M_get_root(), 0);
				}

				Rb_tree()
				: m_node_count(0)
				{
					this->m_header.m_color = _rb_red;
					this->m_header.m_parent = 0;
					this->m_header.m_left = &this->m_header;
					this->m_header.m_right = &this->m_header;
				}

				~Rb_tree()
				{ }

				// _ITERATORS_

				// _CAPACITY_
				bool
				empty() const
				{ return (!m_node_count); }

				size_type
				size() const
				{ return (m_node_count); }

				size_type
				max_size() const
				{ return (m_node_allocator.max_size()); }

				void
				insert(Val value)
				{
					tree_node	*new_node = createNode(value);

					m_header.m_parent = BSTInsert(this->_M_get_root(), new_node);
					fixViolation(_M_get_root(), new_node);
				}
		};
}

#endif