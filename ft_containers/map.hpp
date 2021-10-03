#ifndef MAP_HPP
#define MAP_HPP

#include "enable_if.hpp"
#include "rbtree.hpp"
#include "lexicographical_compare.hpp"
#include "equal.hpp"
#include <memory>

namespace ft
{
template <class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
    class map
{
public:
    typedef Key                                               key_type;
    typedef T                                                 mapped_type;
    typedef typename ft::pair<const key_type, mapped_type>    value_type;

private:

    class value_compare
{
    friend class map;
protected:
    Compare _comp;
    value_compare(Compare c) : _comp(c) {}

public:
    typedef bool result_type;
    typedef value_type first_argument_type;
    typedef value_type second_argument_type;
    bool operator()(const value_type& x, const value_type& y) const {
        return _comp(x.first, y.first);
    }
};

    public:

    typedef Compare                                                                                  key_compare;
    typedef Alloc                                                                                    allocator_type;
    typedef typename allocator_type::reference                                                       reference;
    typedef typename allocator_type::const_reference                                                 const_reference;
    typedef typename allocator_type::pointer                                                         pointer;
    typedef typename allocator_type::const_pointer                                                   const_pointer;
    typedef typename ft::bidirectional_iterator<value_type, false>                iterator;
    typedef typename ft::bidirectional_iterator<value_type, true>    const_iterator;
    typedef typename ft::reverse_iterator<iterator>                                                  reverse_iterator;
    typedef typename ft::reverse_iterator<const_iterator>                                            const_reverse_iterator;
    typedef typename std::size_t                                                                     size_type;
    typedef typename std::ptrdiff_t                                                                  difference_type;

    ///////////////////////*************Member functions*************\\\\\\\\\\\\\\\\\\\\\\\\\\*

    explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
    //m_tree((value_compare(comp), alloc)) {}
    m_tree(rbtree<value_type, value_compare, allocator_type>(value_compare(comp), alloc)) {}

    template <class InputIterator>
    map(InputIterator first, typename ft::enable_if<
                !std::numeric_limits<InputIterator>::is_integer,
                    InputIterator>::type last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
    m_tree(rbtree<value_type, value_compare, allocator_type>(value_compare(comp), alloc))
    {
        insert(first, last);
    }

    map(const map& x) :
    m_tree(rbtree<value_type, value_compare, allocator_type>(value_compare(Compare()), Alloc()))
    {
        m_tree.insert(x.m_tree.begin(), x.m_tree.end());
    }

        ~map() {}

    map& operator=(const map& x)
    {
        m_tree.clear();
        m_tree.insert(x.m_tree.begin(), x.m_tree.end());
        return(*this);
    }

    allocator_type get_allocator() const
    { return allocator_type(); }

    ///////////////////////*************Member functions*************\\\\\\\\\\\\\\\\\\\\\\\\\\*


    ///////////////////////*************Element access*************\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

    T& operator[] (const key_type& k)
    {
    iterator tmp = this->find(k);

    if (tmp == this->end())
        this->insert(ft::make_pair(k, mapped_type()));
    tmp = this->find(k);
    return ((*tmp).second);
    }

    T& at( const Key& k )
    {
        iterator tmp = this->find(k);

        if (tmp == this->end())
            throw std::out_of_range("out of range!\n");
        tmp = this->find(k);
        return ((*tmp).second);
    }

    const T& at( const Key& k ) const
    {
        iterator tmp = this->find(k);

        if (tmp == this->end())
            throw std::out_of_range("out of range!\n");
        tmp = this->find(k);
        return ((*tmp).second);
    }

    ///////////////////////*************Element access*************\\\\\\\\\\\\\\\\\\\\\*


    ///////////////////////*************Iterators*************\\\\\\\\\\\\\\\\\\\\\\\\\\\*

    iterator begin()
    { return m_tree.begin(); }
    const_iterator begin() const
    { return m_tree.begin(); }

    iterator end()
    { return m_tree.end(); }
    const_iterator end() const
    { return m_tree.end(); }

    reverse_iterator rbegin()
    { return m_tree.rbegin(); }
    const_reverse_iterator rbegin() const
    { return m_tree.rbegin(); }

    reverse_iterator rend()
    { return m_tree.rend(); }
    const_reverse_iterator rend() const
    { return m_tree.rend(); }

    ///////////////////////*************Iterators*************\\\\\\\\\\\\\\\\\\\\\\\\\\\\*


    ///////////////////////*************Capacity*************\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

    bool empty() const
    { return m_tree.empty(); }

    size_type size() const
    { return m_tree.size(); }

    size_type max_size() const
    { return m_tree.max_size();}

    ///////////////////////*************Capacity*************\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*


    ///////////////////////*************Modifiers*************\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

    void clear()
    { m_tree.clear(); }

    pair<iterator,bool> insert (const value_type& val)
    { return m_tree.insert(val) ; }

    iterator insert (iterator position, const value_type& val)
    { return m_tree.insert(position, val); }

    template <class InputIterator>
    void insert (InputIterator first, typename ft::enable_if<
        !std::numeric_limits<InputIterator>::is_integer,
                    InputIterator>::type last)
    { return m_tree.insert(first, last); }

    void erase (iterator position)
    { m_tree.erase(position); }

    size_type erase (const key_type& k)
    { return m_tree.erase(ft::make_pair(k, mapped_type())); }

    void erase (iterator first, iterator last)
    { m_tree.erase(first, last); }

    void swap(map& x)
    { m_tree.swap(x.m_tree); }

    ///////////////////////*************Modifiers*************\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*


    ///////////////////////*************Lookup*************\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

    iterator find (const key_type& k)
    { return m_tree.find(ft::make_pair(k, mapped_type())); }

    const_iterator find (const key_type& k) const
    { return m_tree.find(ft::make_pair(k, mapped_type())); }

    size_type count (const key_type& k) const
    { return m_tree.count(ft::make_pair(k, mapped_type())); }

    iterator lower_bound (const key_type& k)
    { return m_tree.lower_bound(ft::make_pair(k, mapped_type())); }

    const_iterator lower_bound (const key_type& k) const
    { return m_tree.lower_bound(ft::make_pair(k, mapped_type())); }

    iterator upper_bound (const key_type& k)
    { return m_tree.upper_bound(ft::make_pair(k, mapped_type())); }

    const_iterator upper_bound (const key_type& k) const
    { return m_tree.upper_bound(ft::make_pair(k, mapped_type())); }

    pair<const_iterator,const_iterator> equal_range (const key_type& k) const
    { return m_tree.equal_range(ft::make_pair(k, mapped_type())); }

    pair<iterator,iterator> equal_range (const key_type& k)
    { return  m_tree.equal_range(ft::make_pair(k, mapped_type())); }

    ///////////////////////*************Lookup*************\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*


    ///////////////////////*************Observers*************\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

    key_compare key_comp() const
    { return m_tree.value_comp()._comp; }

    value_compare value_comp() const
    { return m_tree.value_comp(); }

    ///////////////////////*************Observers*************\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

private:
    rbtree<value_type, value_compare, allocator_type> m_tree;
};

template<class K, class T, class C, class A >
bool operator==( const ft::map<K, T, C, A>& lhs,
                const ft::map<K, T, C, A>& rhs )
{ return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin())); }

template<class K, class T, class C, class A >
bool operator!=( const ft::map<K, T, C, A>& lhs,
                const ft::map<K, T, C, A>& rhs )
{ return !(lhs == rhs); }

template<class K, class T, class C, class A >
bool operator<( const ft::map<K, T, C, A>& lhs,
                const ft::map<K, T, C, A>& rhs )
{ return ( ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

template<class K, class T, class C, class A >
bool operator<=( const ft::map<K, T, C, A>& lhs,
                const ft::map<K, T, C, A>& rhs )
{ return !( rhs < lhs); }

template<class K, class T, class C, class A >
bool operator>( const ft::map<K, T, C, A>& lhs,
                const ft::map<K, T, C, A>& rhs )
{ return rhs < lhs; }

template<class K, class T, class C, class A >
bool operator>=( const ft::map<K, T, C, A>& lhs,
                const ft::map<K, T, C, A>& rhs )
{ return !(lhs < rhs); }

template<class K, class T, class C, class A >
void swap( ft::map<K, T, C, A>& lhs,
                ft::map<K, T, C, A>& rhs )
{ lhs.swap(rhs); }

}

#endif /* MAP */
