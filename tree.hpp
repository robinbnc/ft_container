#ifndef TREE_HPP
# define TREE_HPP

# include <memory>
# include <iostream>
# include <stdio.h>
# include "pair.hpp"
# include "reverse_iterator.hpp"

# define COUNT 10
# define RED "\x1b[31;1m"
# define RESET "\x1b[0m"


namespace ft
{

	enum rb_tree_color { _rb_red = false, _rb_black = true };

	template<typename Val>
		struct	s_tree_node
		{
			typedef	struct	s_tree_node			t_tree_node;
			typedef	t_tree_node*				m_ptr;
			typedef	const t_tree_node*			m_const_ptr;

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

			m_ptr sibling()
			{
				// sibling null if no parent
				if (this->m_parent == NULL)
					return (NULL);
				if (this->isOnLeft())
					return (this->m_parent->m_right);
				return (this->m_parent->m_left);
			}

			bool
			isOnLeft()
			{ return (this == this->m_parent->m_left); }

			bool
			hasRedChild()
			{
				return ((this->m_left && this->m_left->m_color == _rb_red) ||
					(this->m_right && this->m_right->m_color == _rb_red));
			}

			static void
			swapColors(m_ptr x1, m_ptr x2)
			{
				rb_tree_color temp;

				temp = x1->m_color;
				x1->m_color = x2->m_color;
				x2->m_color = temp;
			}
			
			static void
			swapValues(m_ptr u, m_ptr v)
			{
				Val *temp;

				temp = u->m_value;
				u->m_value = v->m_value;
				v->m_value = temp;
			}

			void
			moveDown(m_ptr nParent)
			{
				if (this->m_parent != NULL)
				{
					if (isOnLeft())
						m_parent->m_left = nParent;
					else
						m_parent->m_right = nParent;
				}
				nParent->m_parent = this->m_parent;
				this->m_parent = nParent;
			}

			m_ptr
			uncle()
			{
				if (m_parent == NULL || m_parent->m_parent == NULL)
					return (NULL);
			
				if (m_parent->isOnLeft())
					return (m_parent->m_parent->m_right);
				else
					return (m_parent->m_parent->m_left);
			}
		};

		template<typename T>
			struct Rb_tree_iterator
			{
				typedef T  								value_type;
				typedef T& 								reference;
				typedef T* 								pointer;

				typedef std::bidirectional_iterator_tag	iterator_category;
				typedef std::ptrdiff_t					difference_type;

				typedef Rb_tree_iterator<T>				_Self;
				typedef typename s_tree_node<T>::m_ptr	_Base_ptr;
				typedef s_tree_node<T>*					_Link_type;

				Rb_tree_iterator()
				: m_node() { }
			
				explicit
				Rb_tree_iterator(_Link_type x)
				: m_node(x) { }
			
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
						else if (node->isOnLeft() && node->m_parent != NULL)
								return (node->m_parent);
						else
						{
							while (!node->isOnLeft())
								node = node->m_parent;
							return (node->m_parent);
						}
					}

					_Base_ptr
					Rb_tree_decrement(_Base_ptr node)
					{
						if (node->m_left != NULL)
							return (node->m_left->maximum(node->m_left));
						else if (!node->isOnLeft()
								&& node->m_parent != NULL)
								return (node->m_parent);
						else
						{
							while (node->isOnLeft())
								node = node->m_parent;
							return (node->m_parent);
						}
					}
				};

			template<typename T>
				struct Rb_tree_const_iterator
				{
					typedef T  										value_type;
					typedef const T& 								reference;
					typedef const T* 								pointer;

					typedef Rb_tree_iterator<value_type> 			iterator;

					typedef std::bidirectional_iterator_tag			iterator_category;
					typedef std::ptrdiff_t							difference_type;

					typedef Rb_tree_const_iterator<T>				_Self;
					typedef typename s_tree_node<T>::m_const_ptr	_Base_ptr;
					typedef const s_tree_node<T>*					_Link_type;

					Rb_tree_const_iterator()
					: m_node() { }
				
					explicit
					Rb_tree_const_iterator(_Link_type x)
					: m_node(x) { }

					Rb_tree_const_iterator(const iterator& it)
					: m_node(it.m_node) { }

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
							else if (node->isOnLeft() && node->m_parent != NULL)
									return (node->m_parent);
							else
							{
								while (!node->isOnLeft())
									node = node->m_parent;
								return (node->m_parent);
							}
						}

						_Base_ptr
						Rb_tree_decrement(_Base_ptr node)
						{
							if (node->m_left != NULL)
								return (node->m_left->maximum(node->m_left));
							else if (!node->isOnLeft()
									&& node->m_parent != NULL)
									return (node->m_parent);
							else
							{
								while (node->isOnLeft())
									node = node->m_parent;
								return (node->m_parent);
							}
						}
					};

		   template<typename Val>
		    	inline bool
		    	operator==(const _Rb_tree_iterator<Val>& x,
							const _Rb_tree_const_iterator<Val>& y)
				{ return x._M_node == y._M_node; }

		   template<typename Val>
				inline bool
				operator!=(const _Rb_tree_iterator<Val>& x,
							const _Rb_tree_const_iterator<Val>& y)
				{ return x._M_node != y._M_node; }

		template<typename Key, typename Val/* Pair */,
				typename Compare, typename Alloc = std::allocator<Val> >
		class Rb_tree
		{
			public:
				typedef	struct	s_tree_node<Val>				tree_node;
				typedef std::allocator<tree_node>				Node_allocator;
				typedef std::size_t								size_type;

				typedef ft::Rb_tree_iterator<Val> 				iterator;
				typedef ft::Rb_tree_const_iterator<Val>			const_iterator;
				typedef ft::reverse_iterator<iterator>      	reverse_iterator;
				typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

				typedef std::bidirectional_iterator_tag			iterator_category;
				typedef std::ptrdiff_t							difference_type;

			protected:
				Compare			m_comp;
				Node_allocator	m_node_allocator;
				Alloc			m_val_allocator;
				tree_node		m_header;
				tree_node		m_end;
				tree_node		m_begin;
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

				void
				_M_reset_centinels( void )
				{
					m_header.m_left				= m_header.minimum(_M_get_root());
					m_header.m_right			= m_header.maximum(_M_get_root());

					m_header.m_right->m_right	= &m_end;
					m_end.m_parent				= m_header.m_right;
					m_header.m_right			= &m_end;

					m_header.m_left->m_left		= &m_begin;
					m_begin.m_parent			= m_header.m_left;
					m_header.m_left				= &m_begin;
				}

				tree_node *BSTreplace(tree_node *x)
				{
					if (x->m_left != NULL && x->m_right != NULL)
						return (Rb_tree::tree_node::minimum(x->m_right));
					if (x->m_left == NULL && x->m_right == NULL)
						return NULL;
					if (x->m_left != NULL)
						return x->m_left;
					else
						return x->m_right;
				}

				void leftRotate(tree_node *x)
				{
					tree_node *nParent = x->m_right;
				
					if (x == m_header.m_parent)
						m_header.m_parent = nParent;
					x->moveDown(nParent);
					x->m_right = nParent->m_left;
					if (nParent->m_left != NULL)
					nParent->m_left->m_parent = x;
					nParent->m_left = x;
				}
				
				void rightRotate(tree_node *x)
				{
					tree_node *nParent = x->m_left;
				
					if (x == m_header.m_parent)
						m_header.m_parent = nParent;
					x->moveDown(nParent);
					x->m_left = nParent->m_right;
					if (nParent->m_right != NULL)
					nParent->m_right->m_parent = x;
					nParent->m_right = x;
				}

				void fixRedRed(tree_node *x)
				{
					if (x == m_header.m_parent) {
						x->m_color = _rb_black;
						return;
					}
				
					tree_node	*parent = x->m_parent;
					tree_node	*grandparent = parent->m_parent;
					tree_node	*uncle = x->uncle();
				
					if (parent->m_color == _rb_black)
						return ;
					if (uncle != NULL && uncle->m_color == _rb_red)
					{
						parent->m_color = _rb_black;
						uncle->m_color = _rb_black;
						grandparent->m_color = _rb_red;
						fixRedRed(grandparent);
					}
					else
					{
						if (parent->isOnLeft())
						{
							if (x->isOnLeft())
								Rb_tree::tree_node::swapColors(parent, grandparent);
							else
							{
								leftRotate(parent);
								Rb_tree::tree_node::swapColors(x, grandparent);
							}
							rightRotate(grandparent);
						}
						else
						{
							if (x->isOnLeft())
							{
								rightRotate(parent);
								Rb_tree::tree_node::swapColors(x, grandparent);
							}
							else
								Rb_tree::tree_node::swapColors(parent, grandparent);
							leftRotate(grandparent);
						}
					}
				}

				void fixDoubleBlack(tree_node *x)
				{
					if (x == m_header.m_parent)
						return;
				
					tree_node *sibling = x->sibling();
					tree_node *parent = x->m_parent;

					if (sibling == NULL)
					{
						fixDoubleBlack(parent);
						return ;
					}
					if (sibling->m_color == _rb_red)
					{
						parent->m_color = _rb_red;
						sibling->m_color = _rb_black;
						if (sibling->isOnLeft())
							rightRotate(parent);
						else
							leftRotate(parent);
						fixDoubleBlack(x);
					} 
					else
					{
						if (sibling->hasRedChild())
						{
							if (sibling->m_left != NULL && sibling->m_left->m_color == _rb_red)
							{
								if (sibling->isOnLeft()) {
									sibling->m_left->m_color = sibling->m_color;
									sibling->m_color = parent->m_color;
									rightRotate(parent);
								}
								else {
									sibling->m_left->m_color = parent->m_color;
									rightRotate(sibling);
									leftRotate(parent);
								}
							}
							else
							{
								if (sibling->isOnLeft()) {
									sibling->m_right->m_color = parent->m_color;
									leftRotate(sibling);
									rightRotate(parent);
								}
								else {
									sibling->m_right->m_color = sibling->m_color;
									sibling->m_color = parent->m_color;
									leftRotate(parent);
								}
							}
							parent->m_color = _rb_black;
						}
						else
						{
							sibling->m_color = _rb_red;
							if (parent->m_color == _rb_black)
								fixDoubleBlack(parent);
							else
								parent->m_color = _rb_black;
						}
					}
				}

				void
				_M_deallocate_node(tree_node *node)
				{
					if (node)
					{
						m_val_allocator.destroy(node->m_value);
						m_val_allocator.deallocate(node->m_value, 1);
						m_node_allocator.destroy(node);
						m_node_allocator.deallocate(node, 1);
						// delete node;
					}
				}

				void
				deleteNode(tree_node *v)
				{
					tree_node *u = BSTreplace(v);
				
					bool uvBlack = ((u == NULL || u->m_color == _rb_black)
									&& (v->m_color == _rb_black));
					tree_node *parent = v->m_parent;
					
					if (u == NULL)
					{
						if (v == m_header.m_parent)
							m_header.m_parent = NULL;
						else
						{
							if (uvBlack)
								fixDoubleBlack(v);
							else {
								if (v->sibling() != NULL)
									v->sibling()->m_color = _rb_red;
							}
							if (v->isOnLeft())
								parent->m_left = NULL;
							else
								parent->m_right = NULL;
						}
						_M_deallocate_node(v);
						return ;
					}
					if (v->m_left == NULL || v->m_right == NULL)
					{
						if (v == m_header.m_parent)
						{
							m_val_allocator.destroy(v->m_value);
							m_val_allocator.deallocate(v->m_value, 1);
							v->m_value = u->m_value;
							v->m_left = v->m_right = NULL;
							// m_node_allocator.destroy(u);
							// m_node_allocator.deallocate(u, 1);
							delete (u);
						}
						else
						{
							if (v->isOnLeft())
								parent->m_left = u;
							else
								parent->m_right = u;
							_M_deallocate_node(v);
							u->m_parent = parent;
							if (uvBlack)
								fixDoubleBlack(u);
							else
								u->m_color = _rb_black;
						}
						return ;
					}
					Rb_tree::tree_node::swapValues(u, v);
					deleteNode(u);
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
					(root->m_color == _rb_red)
					? std::cout << RED
					: std::cout << RESET;
					if (root->m_value != NULL)
						std::cout<< *root->m_value <<"\n";
					else
						std::cout<< "NODE" <<"\n";
					std::cout << RESET;
					print2DUtil(root->m_left, space);
				}

				void print2D()
				{
					this->print2DUtil(_M_get_root(), 0);
				}

				Rb_tree()
				: m_node_count(0)
				{
					this->m_header.m_color	= _rb_red;
					this->m_header.m_value	= NULL;
					this->m_header.m_parent	= NULL;
					this->m_begin.m_parent	= NULL;
					this->m_end.m_parent	= NULL;
					this->m_header.m_left	= &this->m_header;
					this->m_header.m_right	= &this->m_header;
				}

				~Rb_tree()
				{ }

				// _ITERATORS_ || MANQUE LES CONST ITERATORS

				iterator
				begin()
				{ return (iterator(m_header.m_left->m_parent)); }

				const_iterator
				begin() const
				{ return (const_iterator(m_header.m_left->m_parent)); }

				iterator
				end()
				{ return (iterator(m_header.m_right)); }

				const_iterator
				end() const
				{ return (const_iterator(m_header.m_right)); }

				reverse_iterator
				rbegin()
				{ return (reverse_iterator(m_header.m_right->m_parent)); }

				const_reverse_iterator
				rbegin() const
				{ return (const_reverse_iterator(m_header.m_right->m_parent)); }

				reverse_iterator
				rend()
				{ return (reverse_iterator(m_header.m_left)); }

				const_reverse_iterator
				rend() const
				{ return (const_reverse_iterator(m_header.m_left)); }

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


				// __Modifiers__
				void
				insert(Val n)
				{
					if (m_end.m_parent)
						m_end.m_parent->m_right	 = NULL;
					if (m_begin.m_parent)
						m_begin.m_parent->m_left = NULL;

					tree_node *temp = find(n);

					if (m_header.m_parent && temp != &m_end && temp != &m_begin
						&& *temp->m_value == n)
					{
						_M_reset_centinels();						
						return ;
					}

					tree_node *newNode = createNode(n);

					if (m_header.m_parent == NULL)
					{
						newNode->m_color = _rb_black;
						m_header.m_parent = newNode;
					}
					else
					{
						newNode->m_parent = temp;
						if (m_comp(n, *temp->m_value))
							temp->m_left = newNode;
						else
							temp->m_right = newNode;
						fixRedRed(newNode);
					}
					m_node_count++;
					_M_reset_centinels();
				}

				void erase(Val n)
				{
					tree_node	*v = find(n);

					if (m_end.m_parent)
						m_end.m_parent->m_right	 = NULL;
					if (m_begin.m_parent)
						m_begin.m_parent->m_left = NULL;
					
					if (m_header.m_parent == NULL)
						return ;
				
					if (!v
						|| v == &m_begin
						|| v == &m_end
						|| *v->m_value != n)
					{
						std::cout << "No node found to delete with value:" << n << endl;
						return ;
					}
					deleteNode(v);
					m_node_count--;
					if (m_node_count)
						_M_reset_centinels();
				}

				void
				clear( void )
				{
					while (size())
						erase(*begin().m_node->m_value);
				}

				// __Operations__
				tree_node*
				find(Val to_find)
				{
					tree_node *temp = m_header.m_parent;

					while (temp != NULL
							&& temp != &m_begin
							&& temp != &m_end)
					{
						if (m_comp(to_find, *temp->m_value))
						{
							if (temp->m_left == NULL)
								break ;
							else
								temp = temp->m_left;
						}
						else if (to_find == *temp->m_value)
							break ;
						else
						{
							if (temp->m_right == NULL)
								break ;
							else
								temp = temp->m_right;
						}
					} 
					return (temp);
				}
		};
}

#endif