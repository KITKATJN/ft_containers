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

    void delete_(T data)
    {
        deleteNode(this->m_root, data);
    }

    Node<value_type> *_move(const_reference val) const
		{
			Node<value_type> *x = m_root;
			Node<value_type> *y = NULL;

			while(x)
			{
				y = x;
				if(m_compare(*x->data, val))
					x = y->right;
				else if (m_compare(val, *x->data))
					x = y->left;
				else
					return (y);
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
        NodePtr res = _move(val);

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

        m_root->parent = m_end;
        m_end->left = m_root;

        return (ft::make_pair(iterator(no), true));
    }



    void rightRotate(NodePtr x) {
        NodePtr y = x->left;
        x->left = y->right;
        if (y->right != m_end) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == NULL) {
            this->m_root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }


    void leftRotate(NodePtr x)
    {
        NodePtr y = x->right;
        x->right = y->left;
        if (y->left != m_end)
            y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == NULL)
            m_root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    NodePtr maximum(NodePtr node)
    {
        while (node->right != m_end)
            node = node->right;
        return node;
    }

    NodePtr minimum(NodePtr node)
    {
        while (node->left != m_end)
            node = node->left;
        return node;
    }

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

    void fixInsert(NodePtr k)
    {
        NodePtr u;
        while (k->parent->color == true)
        {
            if (k->parent == k->parent->parent->right)
            {
                u = k->parent->parent->left;
                if (u->color)
                {
                    u->color = false;
                    k->parent->color = false;
                    k->parent->parent->color = true;
                    k = k->parent->parent;
                }
                else
                {
                    if (k == k->parent->left)
                    {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = false;
                    k->parent->parent->color = true;
                    leftRotate(k->parent->parent);
                }
            }
            else
            {
                u = k->parent->parent->right;
                if (u->color)
                {
                    u->color = false;
                    k->parent->color = false;
                    k->parent->parent->color = true;
                    k = k->parent->parent;
                }
                else
                {
                    if (k == k->parent->right)
                    {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = false;
                    k->parent->parent->color = true;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == m_root)
                break ;
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
