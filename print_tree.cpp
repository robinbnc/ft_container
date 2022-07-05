#include <iostream>
#define COUNT 10

void print2DUtil(struct	ft::s_tree_node<std::pair<char, int> > *root, int space)
{
    if (root == NULL)
        return;
 
    space += COUNT;
    print2DUtil(root->m_right, space);
    std::cout<< std::endl;
    for (int i = COUNT; i < space; i++)
        std::cout<<" ";
    std::cout<</* root->data */"NODE"<<"\n";
    print2DUtil(root->m_left, space);
}

void print2D(struct	ft::s_tree_node<std::pair<char, int> > *root)
{
    print2DUtil(root, 0);
}