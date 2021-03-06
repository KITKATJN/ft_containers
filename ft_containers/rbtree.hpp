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
    typedef typename allocator_type::reference                          reference;
    typedef const T                                                     &const_reference;
    typedef T                                                           *pointer;
    typedef const T                                                     *const_pointer;
    typedef Compare                                                     compare_type;
    typedef typename ft::bidirectional_iterator<T, false>              iterator;
    typedef typename ft::bidirectional_iterator<T, true>  const_iterator;
    typedef typename ft::reverse_iterator<iterator>                     reverse_iterator;
    typedef typename ft::reverse_iterator<const_iterator>               const_reverse_iterator;
    typedef ptrdiff_t                                                   difference_type;
    typedef size_t                                                      size_type;
    typedef Node<value_type>                                            *NodePtr;


//////////////////////////////*********Member functions*********//////////////////////////////


    explicit rbtree(const compare_type comp = Compare(), const allocator_type &alloc = Alloc(),
        const nalloc_type &nalloc = NAlloc()) :
        m_compare(comp), m_allocator(alloc), m_nodeAllocator(nalloc), m_root(NULL), m_size(0)
    {
        m_end = m_nodeAllocator.allocate(1);
        m_nodeAllocator.construct(m_end, Node<value_type>(NULL));
    }

    template <class InputIterator>
  		rbtree(InputIterator first, typename ft::enable_if<
                !std::numeric_limits<InputIterator>::is_integer,
                    InputIterator>::type last, const compare_type comp = Compare(), const allocator_type &alloc = Alloc(), const nalloc_type &nalloc = NAlloc()) :
		m_compare(comp), m_allocator(alloc), m_nodeAllocator(nalloc), m_root(NULL), m_size(0)
		{
			m_end = m_nodeAllocator.allocate(1);
			m_nodeAllocator.construct(m_end, Node<value_type>(NULL));
			insert(first, last);
		}

    ~rbtree()
    {
        clear();
        m_nodeAllocator.destroy(m_end);
        m_nodeAllocator.deallocate(m_end, 1);
    }

    rbtree(const rbtree &c) : m_compare(c.m_compare), m_allocator(c.m_allocator),
        m_nodeAllocator(c.m_nodeAllocator), m_root(NULL),  m_size(0)
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

    iterator end()
    { return iterator(m_end); }
    const_iterator end() const
    { return const_iterator(m_end); }

    reverse_iterator rbegin()
    { return(reverse_iterator(end())); }
    const_reverse_iterator rbegin() const
    { return(const_reverse_iterator(end())); }

    reverse_iterator rend()
    { return(reverse_iterator(begin())); }
    const_reverse_iterator rend() const
    { return(const_reverse_iterator(begin())); }

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

    void clear()
    {
        if (m_size == 0)
            return ;
        m_size = 0;
        fixClear(m_root);
        m_root = NULL;
    }

    ft::pair<iterator, bool> insert( const value_type& val )
    {
        if (find(val) != end())
            return ft::make_pair(find(val), true);
        if(m_root)
            m_root->parent = NULL;

        pointer p = m_allocator.allocate(1);
        m_allocator.construct(p, val);
        NodePtr no = m_nodeAllocator.allocate(1);
        m_nodeAllocator.construct(no, Node<value_type>(p));
        if(!m_root) {
            m_size++;
            m_root = no;
            m_root->color = false;
            return (ft::make_pair(iterator(m_root), true));
        }
        NodePtr res = findNode(val);

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
        fixTree(no);
        m_root->parent = m_end;
        m_end->left = m_root;
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

    void erase( iterator pos )
    {
        m_size--;
        m_root->parent = NULL;
        fixTree(fixErase(pos.base()));
        if (m_root != NULL)
        {
            m_root->parent = m_end;
            m_end->left = m_root;
        }
    }

    void erase(iterator first, iterator last) {
        iterator tmp;

        while (first != last) {
            tmp = first;
            first++;
            erase(tmp);
        }
    }

    size_type erase( const value_type& key )
    {
        if (m_root == NULL || find(key) == end())
            return 0;
        erase(find(key));
        return 1;
    }

    void swap( rbtree& other )
    {
        ft::swap(m_compare, other.m_compare);
        ft::swap(m_allocator, other.m_allocator);
        ft::swap(m_nodeAllocator, other.m_nodeAllocator);
        ft::swap(m_end, other.m_end);
        ft::swap(m_root, other.m_root);
        ft::swap(m_size, other.m_size);
    }

//////////////////////////////*********Modifiers*********//////////////////////////////


//////////////////////////////*********Lookup*********//////////////////////////////

    size_type count( const value_type& key ) const
    { return find(key) == end() ? 0 : 1; }

    iterator find( const value_type& value )
    {
        NodePtr tmp = findNode(value);
        if (tmp == NULL)
            return end();
        if(!m_compare(*tmp->data, value) && !m_compare(value,*tmp->data))
            return(iterator(tmp));
        return(end());
    }

    const_iterator find( const value_type& value ) const
    {
        NodePtr tmp = findNode(value);

        if(!m_compare(*tmp->data, value) && !m_compare(value,*tmp->data))
            return(const_iterator(tmp));
        return(end());
    }

    pair<const_iterator,const_iterator> equal_range(const value_type &value) const
    {
        if (this->lower_bound(value) == this->end() && this->upper_bound(value) == this->end())
            return (ft::make_pair<const_iterator, const_iterator>(this->begin(), this->begin()));
        return (ft::make_pair<const_iterator, const_iterator>(this->lower_bound(value), this->upper_bound(value)));
    }

    pair<iterator,iterator>             equal_range(const value_type &value)
    {
        if (this->lower_bound(value) == this->end() && this->upper_bound(value) == this->end())
            return (ft::make_pair<iterator, iterator>(this->begin(), this->begin()));
        return (ft::make_pair<iterator, iterator>(this->lower_bound(value), this->upper_bound(value)));
    }

    iterator lower_bound( const value_type& key )
    {
        iterator start = begin();
        for (; start != end(); start++)
        {
            if ((!m_compare(*start, key) && !m_compare(key, *start)) || m_compare(key, *start))
                return start;
        }
        return end();
    }

    const_iterator lower_bound( const value_type& key ) const
    {
        iterator start = begin();
        for (; start != end(); start++)
        {
            if ((!m_compare(*start, key) && !m_compare(key, *start)) || m_compare(key, *start))
                return start;
        }
        return end();
    }

    iterator upper_bound( const value_type& key )
    {
        iterator start = begin();
        for (; start != end(); start++)
        {
            if (m_compare(key, *start))
                return start;
        }
        return end();
    }

    const_iterator upper_bound( const value_type& key ) const
    {
        iterator start = begin();
        for (; start != end(); start++)
        {
            if (m_compare(key, *start))
                return start;
        }
        return end();
    }

//////////////////////////////*********Lookup*********//////////////////////////////


//////////////////////////////*********Observers*********//////////////////////////////

    compare_type value_comp() const
    { return m_compare; }

//////////////////////////////*********Observers*********//////////////////////////////

    void delete_(T data)
    {
        deleteNode(this->m_root, data);
    }

    NodePtr findNode(const_reference val) const
    {
        NodePtr x = m_root;
        NodePtr y = NULL;

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

    void rightRotate(NodePtr node)
    {
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

private:

    NodePtr fixErase(NodePtr node)
    {
        if(!node)
            return(NULL);

        NodePtr tmp = NULL;

        if(!node->left || !node->right)
        {
            if(!node->left && !node->right)
            {
                tmp = node->parent;
                if(tmp == NULL)
                {
                    m_root = NULL;
                }
                else if (tmp->left == node)
                {
                    tmp->left = NULL;
                }
                else
                {
                    tmp->right = NULL;
                }
            }
            else
            {
                tmp = !node->right ? node->left : node->right;
                if(node->parent == NULL)
                {
                    m_root = tmp;
                    tmp->parent = NULL;
                }
                else if(node->parent->left == node)
                {
                    node->parent->left = tmp;
                    tmp->parent = node->parent;
                }
                else
                {
                    node->parent->right = tmp;
                    tmp->parent = node->parent;
                }
            }
            clear_ForfixErase(node);
            return (tmp);
        }
        tmp = node->left;
        while(tmp->right)
            tmp = tmp->right;
        m_allocator.destroy(node->data);
        m_allocator.construct(node->data, *tmp->data);
        return(fixErase(tmp));
    }

    void clear_ForfixErase(NodePtr node)
    {
        if (!node)
            return;

        m_allocator.destroy(node->data);
        m_allocator.deallocate(node->data, 1);
        m_nodeAllocator.destroy(node);
        m_nodeAllocator.deallocate(node, 1);
    }

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

    void fixTree(NodePtr node)
    {
        if(!node)
            return;
        NodePtr parent = NULL;
        NodePtr grandpa = NULL;
        NodePtr uncle = NULL;

        while ((node != m_root) && (node->color != false) && (node->parent->color == true))
        {
            parent = node->parent;
            grandpa = node->parent->parent;
            if (parent == grandpa->left)
            {
                uncle = grandpa->right;

                if (uncle && uncle->color == true)
                {
                    grandpa->color = true;
                    parent->color = false;
                    uncle->color = false;
                    node = grandpa;
                }
                else
                {
                    if (node == parent->right)
                    {
                        leftRotate(parent);
                        node = parent;
                        parent = node->parent;
                    }
                    rightRotate(grandpa);
                    ft::swap(parent->color, grandpa->color);
                    node = parent;
                }
            }
            else
            {
                uncle = grandpa->left;
                if (uncle && uncle->color == true)
                {
                    grandpa->color = true;
                    parent->color = false;
                    uncle->color = false;
                    node = grandpa;
                }
                else
                {
                    if (node == parent->left)
                    {
                        rightRotate(parent);
                        node = parent;
                        parent = node->parent;
                    }
                    leftRotate(grandpa);
                    ft::swap(parent->color, grandpa->color);
                    node = parent;
                }
            }
        }
        m_root->color = false;
    }

    Compare             m_compare;
    allocator_type      m_allocator;
    nalloc_type         m_nodeAllocator;
    NodePtr             m_end;
    NodePtr             m_root;
    size_type           m_size;

};
}

 #endif /* RBTREE */
