#ifndef TREE_HPP
# define TREE_HPP

# include <memory>
# include <iostream>
# include <stdio.h>
# include "pair.hpp"
# define COUNT 10
# define RED "\x1b[31;1m"
# define RESET "\x1b[0m"



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

			static void swapColors(m_ptr x1, m_ptr x2) {
				rb_tree_color temp;
				temp = x1->m_color;
				x1->m_color = x2->m_color;
				x2->m_color = temp;
			}
			
			static void swapValues(m_ptr u, m_ptr v) {
				Val *temp;
				temp = u->m_value;
				u->m_value = v->m_value;
				v->m_value = temp;
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
				Compare			m_comp;
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

				tree_node *rotateLeft(tree_node *node)
    			{
    			    tree_node *x = node->m_right;
    			    tree_node *y = x->m_left;
    			    x->m_left = node;
    			    node->m_right = y;
    			    node->m_parent = x; // m_parent resetting is also important->
    			    if(y!= NULL)
    			        y->m_parent = node;
    			    return(x);
    			}
    			//this function performs m_right rotation
    			tree_node *rotateRight(tree_node *node)
    			{
    			    tree_node *x = node->m_left;
    			    tree_node *y = x->m_right;
    			    x->m_right = node;
    			    node->m_left = y;
    			    node->m_parent = x;
    			    if(y!=NULL)
    			        y->m_parent = node;
    			    return(x);
    			}

				tree_node *insertAndReblance(tree_node *root, Val data)
				{
					static bool ll = false;
					static bool rr = false;
					static bool lr = false;
					static bool rl = false;

					bool f = false;
					
					if(root == NULL)
						return(createNode(data));
					else if(m_comp(data, *root->m_value))
					{
						root->m_left = insertAndReblance(root->m_left, data);
						root->m_left->m_parent = root;
						if(root!=m_header.m_parent)
						{
							if(root->m_color==_rb_red && root->m_left->m_color==_rb_red)
								f = true;
						}
					}
					else
					{
						root->m_right = insertAndReblance(root->m_right,data);
						root->m_right->m_parent = root;
						if(root!=m_header.m_parent)
						{
							if(root->m_color==_rb_red && root->m_right->m_color==_rb_red)
								f = true;
						}
					}
					if(ll) // for m_left rotate.
					{
						root = rotateLeft(root);
						root->m_color = _rb_black;
						root->m_left->m_color = _rb_red;
						ll = false;
					}
					else if(rr) // for m_right rotate
					{
						root = rotateRight(root);
						root->m_color = _rb_black;
						root->m_right->m_color = _rb_red;
						rr  = false;
					}
					else if(rl)  // for m_right and then m_left
					{
						root->m_right = rotateRight(root->m_right);
						root->m_right->m_parent = root;
						root = rotateLeft(root);
						root->m_color = _rb_black;
						root->m_left->m_color = _rb_red;
			
						rl = false;
					}
					else if(lr)  // for m_left and then m_right->
					{
						root->m_left = rotateLeft(root->m_left);
						root->m_left->m_parent = root;
						root = rotateRight(root);
						root->m_color = _rb_black;
						root->m_right->m_color = _rb_red;
						lr = false;
					}
					if(f)
					{
						if(root->m_parent->m_right == root)
						{
							if(root->m_parent->m_left==NULL || root->m_parent->m_left->m_color==_rb_black)
							{
								if(root->m_left!=NULL && root->m_left->m_color==_rb_red)
									rl = true;
								else if(root->m_right!=NULL && root->m_right->m_color==_rb_red)
									ll = true;
							}
							else
							{
								root->m_parent->m_left->m_color = _rb_black;
								root->m_color = _rb_black;
								if(root->m_parent!=m_header.m_parent)
									root->m_parent->m_color = _rb_red;
							}
						}
						else  
						{
							if(root->m_parent->m_right==NULL || root->m_parent->m_right->m_color==_rb_black)
							{
								if(root->m_left!=NULL && root->m_left->m_color==_rb_red)
									rr = true;
								else if(root->m_right!=NULL && root->m_right->m_color==_rb_red)
									lr = true;
							}
							else
							{
								root->m_parent->m_right->m_color = _rb_black;
								root->m_color = _rb_black;
								if(root->m_parent!=m_header.m_parent)
									root->m_parent->m_color = _rb_red;
							}
						}
						f = false;
					}
					return(root); 
				}

				tree_node *BSTreplace(tree_node *x)
				{
					// when node have 2 children
					if (x->m_left != NULL && x->m_right != NULL)
						return (Rb_tree::tree_node::minimum(x->m_right));
				
					// when leaf
					if (x->m_left == NULL && x->m_right == NULL)
						return NULL;
				
					// when single child
					if (x->m_left != NULL)
						return x->m_left;
					else
						return x->m_right;
				}

				void fixDoubleBlack(tree_node *x)
				{
					if (x == m_header.m_parent)
						return;
				
					tree_node *sibling = x->sibling();
					tree_node *parent = x->m_parent;

					if (sibling == NULL)
						fixDoubleBlack(parent);
					else
					{
						if (sibling->m_color == _rb_red)
						{
							parent->m_color = _rb_red;
							sibling->m_color = _rb_black;
							if (sibling->isOnLeft())
							{
								rotateRight(parent);
							}
							else
							{
								rotateLeft(parent);
							}
							fixDoubleBlack(x);
						} 
						else
						{
							if (sibling->hasRedChild())
							{
								if (sibling->m_left != NULL && sibling->m_left->m_color == _rb_red)
								{
									if (sibling->isOnLeft()) {
										// m_left m_left
										sibling->m_left->m_color = sibling->m_color;
										sibling->m_color = parent->m_color;
										rotateRight(parent);
									}
									else {
										// right m_left
										sibling->m_left->m_color = parent->m_color;
										rotateRight(sibling);
										rotateLeft(parent);
									}
								}
								else
								{
									if (sibling->isOnLeft()) {
										// m_left right
										sibling->m_right->m_color = parent->m_color;
										rotateLeft(sibling);
										rotateRight(parent);
									}
									else {
										// m_right m_right
										sibling->m_right->m_color = sibling->m_color;
										sibling->m_color = parent->m_color;
										rotateLeft(parent);
									}
								}
								parent->m_color = _rb_black;
							}
							else
							{
								// 2 black children
								sibling->m_color = _rb_red;
								if (parent->m_color == _rb_black)
									fixDoubleBlack(parent);
								else
									parent->m_color = _rb_black;
							}
						}
					}
				}

				void deleteNode(tree_node *v)
				{
					tree_node *u = BSTreplace(v);
				
					// True when u and v are both black
					bool uvBlack = ((u == NULL || u->m_color == _rb_black) && (v->m_color == _rb_black));
					tree_node *parent = v->m_parent;
				
					if (u == NULL) {
						// u is NULL therefore v is leaf
						if (v == m_header.m_parent)
							m_header.m_parent = NULL;
						else {
							if (uvBlack)
								fixDoubleBlack(v);
							else {
							// u or v is red
								if (v->sibling() != NULL)
									v->sibling()->m_color = _rb_red;
							}
					
							// delete v from the tree
							if (v->isOnLeft())
								parent->m_left = NULL;
							else
								parent->m_right = NULL;
						}
						delete v;
						return;
					}
					if (v->m_left == NULL or v->m_right == NULL) {
						// v has 1 child
						if (v == m_header.m_parent) {
							// v is root, assign the value of u to v, and delete u
							v->m_value = u->m_value;
							v->m_left = v->m_right = NULL;
							delete u;
						}
						else {
							// Detach v from tree and move u up
							if (v->isOnLeft()) {
								parent->m_left = u;
							}
							else {
								parent->m_right = u;
							}
							delete v;
							u->m_parent = parent;
							if (uvBlack) {
							// u and v both black, fix double black at u
								fixDoubleBlack(u);
							} else {
							// u or v red, m_color u black
								u->m_color = _rb_black;
							}
						}
						return;
					}
					// v has 2 children, swap values with successor and recurse
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


				void insert(Val data)
				{
					if(m_header.m_parent==NULL)
					{
						m_header.m_parent = createNode(data);
						m_header.m_parent->m_color = _rb_black;
					}
					else
						m_header.m_parent = insertAndReblance(m_header.m_parent, data);
				}


				void erase(Val n)
				{
					if (m_header.m_parent == NULL)
					// Tree is empty
					return;
				
					tree_node	*v = find(n);
					// tree_node	*u;
				
					if (*v->m_value != n)
					{
						std::cout << "No node found to delete with value:" << n << endl;
						return;
					}
					deleteNode(v);
				}

				tree_node *find(Val to_find)
				{
					tree_node *temp = m_header.m_parent;
					while (temp != NULL)
					{
						if (to_find < *temp->m_value) {//remplacer par le compare
							if (temp->m_left == NULL)
							break;
							else
							temp = temp->m_left;
						}
						else if (to_find == *temp->m_value) {
							break;
						}
						else {
							if (temp->m_right == NULL)
							break;
							else
							temp = temp->m_right;
						}
					} 
					return (temp);
				}
		};
}

#endif