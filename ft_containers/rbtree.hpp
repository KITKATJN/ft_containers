#ifndef RBTREE_HPP
#define RBTREE_HPP

#include "iterator.hpp"
#include "enable_if.hpp"
#include <string>
#include <iostream>
#include <memory>
#include <limits>
#include <algorithm>
#include <functional>

namespace ft
{

template <typename T, typename Compare = std::less<T>, typename Alloc = std::allocator<T>, typename NAlloc = std::allocator<Node<T> > >
class rbtree
{
public:
    typedef T                                                           value_type;
    typedef Alloc                                                       allocator_type;
    typedef NAlloc                                                      nalloc_type;
    typedef const T                                                     &const_reference;
    typedef T                                                           *pointer;
    typedef const T                                                     *const_pointer;
    typedef Compare                                                     compare_type;
    typedef typename ft::bidirectional_iterator<T, T*, T&>              iterator;
    typedef typename ft::bidirectional_iterator<T, const T*, const T&>  const_iterator;
    typedef typename ft::reverse_iterator<iterator>                     reverse_iterator;
    typedef typename ft::reverse_iterator<const_iterator>               const_reverse_iterator;
    typedef	ptrdiff_t                                                   difference_type;
    typedef size_t                                                      size_type;
    typedef Node<value_type>                                            *NodePtr;


//////////////////////////////*********Member functions*********//////////////////////////////

    explicit rbtree(const compare_type comp = Compare(), const allocator_type &alloc = Alloc(), const nalloc_type &nalloc = NAlloc()) :
        m_compare(comp), m_allocator(alloc), m_nodeAllocator(nalloc), m_root(NULL), m_size(0) {
        m_end = m_nodeAllocator.allocate(1);
        m_nodeAllocator.construct(m_end, Node<value_type>(NULL));
    }

    ~rbtree()
    {
        clear();
        m_nodeAllocator.destroy(m_end);
        m_nodeAllocator.deallocate(m_end, 1);
    }

    rbtree(const rbtree &c) : m_compare(c.m_compare), m_allocator(c.m_allocator), m_nodeAllocator(c.m_nodeAllocator), m_root(NULL),  m_size(0)
    {
        m_end = m_nodeAllocator.allocate(1);
        m_nodeAllocator.construct(m_end, Node<value_type>(NULL));
        insert(c.begin(), c.end());
    }

    rbtree &operator=(const rbtree &c)
    {
        if(this == &c)
            return (*this);
        m_compare = c.m_compare;
        m_allocator = c.m_allocator;
        m_nodeAllocator = c.m_nodeAllocator;
        insert(c.begin(), c.end());
        return(*this);
    }

    allocator_type get_allocator() const
    { return m_allocator; }

//////////////////////////////*********Member functions*********//////////////////////////////


//////////////////////////////*********Iterators*********//////////////////////////////

    iterator begin()
    {
        if (m_root == NULL || m_size == 0)
            return end();

        NodePtr node = m_root;
        while (node->left != NULL)
            node = node->left;
        return iterator(node);
    }

    const_iterator begin() const
    {
        if (m_root == NULL || m_size == 0)
            return end();

        NodePtr node = m_root;
        while (node->left != NULL)
            node = node->left;
        return const_iterator(node);
    }

    iterator end()  { return iterator(m_end); }
    const_iterator end() const  { return const_iterator(m_end); }

    reverse_iterator rbegin() { return(reverse_iterator(end())); }
    const_reverse_iterator rbegin() const {	return(const_reverse_iterator(end())); }

    reverse_iterator rend() { return(reverse_iterator(begin())); }
    const_reverse_iterator rend() const { return(const_reverse_iterator(begin())); }

//////////////////////////////*********Iterators*********//////////////////////////////



//////////////////////////////*********Capacity*********//////////////////////////////

    bool empty() const
    { return m_size == 0; }

    size_type size() const
    { return m_size; }

    size_type max_size() const
    { return m_allocator.max_size() > m_nodeAllocator.max_size() ?
            m_nodeAllocator.max_size() : m_allocator.max_size(); }

//////////////////////////////*********Capacity*********//////////////////////////////

//////////////////////////////*********Modifiers*********//////////////////////////////

    void delete_(T data)
    {
        deleteNode(this->m_root, data);
    }

    NodePtr findToWhereInsert(const_reference val) const
    {
        NodePtr x = m_root;
        NodePtr y = NULL;

        while(x)
        {
            y = x;
            if (m_compare(*x->data, val))
                x = y->right;
            else if (!m_compare(*x->data, val))
                x = y->left;
            else
            {
                std::cout << "need to delete me!\n";
                return (y);
            }
        }
        return (y);
    }

    ft::pair<iterator, bool> insert( const value_type& val )
    {
        if(m_root)
            m_root->parent = NULL;

        pointer p = m_allocator.allocate(1);
        m_allocator.construct(p, val);
        //std::cout << "111111111113\n";
        NodePtr no = m_nodeAllocator.allocate(1);
        m_nodeAllocator.construct(no, Node<value_type>(p));
        //std::cout << "111111111114\n";
        if(!m_root) {
            m_size++;
            m_root = no;
            m_root->color = false;
            return (ft::make_pair(iterator(m_root), true));
        }

        // Node<value_type> *res = _move(val);

        // Node<value_type> *x = _root;
        // Node<value_type> *y = NULL;

        // while(x)
        // {
        //     y = x;
        //     if(m_compare(*x->value, val))
        //         x = y->right;
        // 	else if (m_compare(val, *x->value))
        //         x = y->left;
        //     else
        //         return (y);
        // }
        // return (y);
        //std::cout << "111111111115\n";
        NodePtr res = findToWhereInsert(val);

        //std::cout << "11111111111\n";
        if(!m_compare(*res->data, val) && !m_compare(val, *res->data)) {
            fixClear(no);
            m_root->parent = m_end;
            m_end->left = m_root;
            return (ft::make_pair(iterator(res), false));
        }
        m_size++;
        if(m_compare(*res->data, val))
            res->right = no;
        else
            res->left = no;
        no->parent = res;
        //std::cout << "11111111111\n";
        fixInsert(no);
        //std::cout << "111111111eee11\n";
        m_root->parent = m_end;
        m_end->left = m_root;
        //std::cout << "111111111118888\n";
        return (ft::make_pair(iterator(no), true));
    }

    iterator insert( iterator hint, const value_type& value )
    {
        hint = insert(value).first;
        return hint;
    }

    template< class InputIt >
    void insert( InputIt first, InputIt last )
    {
        while(first != last)
        {
            insert(*first);
            first++;
        }
    }

    void rightRotate(NodePtr node) {

        NodePtr left = node->left;
        node->left = left->right;
        if (node->left)
            node->left->parent = node;
        left->parent = node->parent;
        if (!node->parent)
            m_root = left;
        else if (node == node->parent->left)
            node->parent->left = left;
        else
            node->parent->right = left;
        left->right = node;
        node->parent = left;
    }


    void leftRotate(NodePtr node)
    {
        NodePtr right = node->right;
        node->right = right->left;
        if (node->right)
            node->right->parent = node;
        right->parent = node->parent;
        if (!node->parent)
            m_root = right;
        else if (node == node->parent->left)
            node->parent->left = right;
        else
            node->parent->right = right;
        right->left = node;
        node->parent = right;
    }

    // T& at( const value_type& key )
    // {
    //     const iterator f = find(key);
    //     if (f == end())
    //         throw std::out_of_range("out of range\n");
    //     return *f->m_point->data;
    // }

    iterator find( const value_type& val )
    {
        NodePtr x = m_root;
        NodePtr y = NULL;

        while(x)
        {
            y = x;
            if (m_compare(*x->data, val))
                x = y->right;
            else if (!m_compare(*x->data, val))
                x = y->left;
            else
            {
                return (y);
            }
        }
        return (end());
    }

    const_iterator find( const value_type& val ) const
    {
        NodePtr x = m_root;
        NodePtr y = NULL;

        while(x)
        {
            y = x;
            if (m_compare(*x->data, val))
                x = y->right;
            else if (!m_compare(*x->data, val))
                x = y->left;
            else
            {
                return (y);
            }
        }
        return (end());
    }


    void clear()
    {
        if (m_size == 0)
            return ;
        m_size = 0;
        fixClear(m_root);
        m_root = NULL;
    }


    void printHelper(NodePtr root, std::string indent, bool last) {
        // print the tree structure on the screen
        //std::cout << "22222222222\n";
        if (root != NULL) {
           std::cout<<indent;
           //std::cout << "222222222225\n";
           if (last) {
              std::cout<<"R----";
              indent += "     ";
           } else {
              std::cout<<"L----";
              indent += "|    ";
           }
            //std::cout << root<< "222222222226\n";
           std::string sColor = root->color?"RED":"BLACK";
           //std::cout << "222222222228\n";
           std::cout<<*root->data<<"("<<sColor<<")"<<std::endl;
           printHelper(root->left, indent, false);
           //std::cout << "222222222227\n";
           printHelper(root->right, indent, true);
        }
        // cout<<root->left->data<<endl;
    }

    void prettyPrint() {
        //std::cout << "11111111111\n";
        if (m_root) {
            printHelper(this->m_root, "", true);
        }
    }


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:

    void fixClear(NodePtr n)
    {
        if (n == NULL)
            return ;
        fixClear(n->right);
        fixClear(n->left);
        m_allocator.destroy(n->data);
        m_allocator.deallocate(n->data, 1);
        m_nodeAllocator.destroy(n);
        m_nodeAllocator.deallocate(n, 1);
    }

    void fixDelete(NodePtr x)
    {
        NodePtr s;
        while (x != m_root && x->color == false)
        {
            if (x == x->parent->left)
            {
                s = x->parent->right;
                if (s->color)
                {
                    s->color = false;
                    x->parent->color = true;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }
                if (s->left->color == false && s->right->color == false)
                {
                    s->color = true;
                    x = x->parent;
                }
                else
                {
                    if (s->right->color == false)
                    {
                        s->left->color = false;
                        s->color = true;
                        rightRotate(s);
                        s = x->parent->right;
                    }
                    s->color = x->parent->color;
                    x->parent->color = false;
                    s->right->color = false;
                    leftRotate(x->parent);
                    x = m_root;
                }
            }
            else
            {
                s = x->parent->left;
                if (s->color)
                {
                    s->color = false;
                    x->parent->color = true;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }
                if (s->right->color == false && s->left->color == false)
                {
                    s->color = true;
                    x = x->parent;
                }
                else
                {
                    if (s->left->color == false)
                    {
                        s->right->color = false;
                        s->color = true;
                        leftRotate(s);
                        s = x->parent->left;
                    }
                    s->color = x->parent->color;
                    x->parent->color = false;
                    s->left->color = false;
                    rightRotate(x->parent);
                    x = m_root;
                }
            }
        }
        x->color = false;
    }

    void rbTransplant(NodePtr u, NodePtr v)
    {
        if (u->parent == NULL)
            m_root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        v->parent = u->parent;
    }

    void deleteNode(NodePtr node, T key)
    {
        NodePtr z = m_end;
        NodePtr x,y;
        while (node != m_end)
        {
            if (node->data == key)
                z = node;
            if (node->data <= key)
                node = node->right;
            else
                node = node->left;
        }
        if (z == m_end)
        {
            // no the same key
            return ;
        }
        y = z;
        bool y_orig_color = y->color;
        if (z->left == m_end)
        {
            x = z->right;
            rbTransplant(z, z->right);
        }
        else if (z->right == m_end)
        {
            x = z->left;
            rbTransplant(z, z->left);
        }
        else
        {
            y = minimum(z->right);
            y_orig_color = y->color;
            x = y->right;
            if (y->parent == z)
                x->parent = y;
            else
            {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_orig_color == false)
            fixDelete(x);
    }


        void fixInsert(Node<value_type> *node)
		{
			if(!node)
				return;
			Node<value_type> *parent = NULL;
			Node<value_type> *grandpa = NULL;
			Node<value_type> *uncle = NULL;

			while ((node != m_root) && (node->color != false) &&
				(node->parent->color == true)) {
				parent = node->parent;
				grandpa = node->parent->parent;

				if (parent == grandpa->left) {
					uncle = grandpa->right;

					if (uncle && uncle->color == true) {
						grandpa->color = true;
						parent->color = false;
						uncle->color = false;
						node = grandpa;
					}
					else {
						if (node == parent->right) {
							leftRotate(parent);
							node = parent;
							parent = node->parent;
						}
						rightRotate(grandpa);
						std::swap(parent->color, grandpa->color);
						node = parent;
					}
				}
				else {
					uncle = grandpa->left;

					if (uncle && uncle->color == true) {
						grandpa->color = true;
						parent->color = false;
						uncle->color = false;
						node = grandpa;
					}
					else {
						if (node == parent->left) {
							rightRotate(parent);
							node = parent;
							parent = node->parent;
						}
						leftRotate(grandpa);
						std::swap(parent->color, grandpa->color);
						node = parent;
					}
				}
			}
			m_root->color = false;
		}

    NodePtr             m_root;
    NodePtr             m_end;
    Compare             m_compare;
    allocator_type      m_allocator;
    nalloc_type         m_nodeAllocator;
    size_type           m_size;

};

}

 #endif /* RBTREE */
