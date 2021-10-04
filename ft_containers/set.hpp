// #ifndef SET_HPP
// #define SET_HPP

// #include "rbtree.hpp"

// namespace ft
// {
// template<
//     class Key,
//     class Compare = ft::less<Key>,
//     class Alloc = std::allocator<Key>
// > class set
// {
//  public:
//     typedef Key                                         key_type;
//     typedef Key                                         value_type;
//     typedef Compare                                     key_compare;
//     typedef Compare                                     value_compare;
//     typedef Alloc                                       allocator_type;
//     typedef typename allocator_type::reference                 reference;
//     typedef typename allocator_type::const_reference           const_reference;
//     typedef typename allocator_type::pointer                   pointer;
//     typedef typename allocator_type::const_pointer             const_pointer;

//     typedef typename ft::bidirectional_iterator<value_type, false>                                   iterator;
//     typedef typename ft::bidirectional_iterator<value_type, true>                                    const_iterator;
//     typedef typename ft::reverse_iterator<iterator>                                                  reverse_iterator;
//     typedef typename ft::reverse_iterator<const_iterator>                                            const_reverse_iterator;

//     typedef typename std::size_t                                                                     size_type;
//     typedef typename std::ptrdiff_t                                                                  difference_type;


//     explicit set(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
//     m_tree(rbtree<value_type, value_compare, allocator_type>(value_compare(comp), alloc)) {}

//     template <class InputIterator>
//     set(InputIterator first, typename ft::enable_if<
//                 !std::numeric_limits<InputIterator>::is_integer,
//                     InputIterator>::type last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
//     m_tree(comp, alloc)
//     {
//         insert(first, last);
//     }

//     explicit set(const key_compare& comp = key_compare(),
//                 const allocator_type& alloc = allocator_type())
//         : m_tree(comp, alloc) {}

//     // template <class InputIterator>
//     // set(InputIterator first, typename ft::enable_if<
//     //             !std::numeric_limits<InputIterator>::is_integer,
//     //                 InputIterator>::type last,
//     //     const key_compare& comp = key_compare(),
//     //     const allocator_type& alloc = allocator_type())
//     //     : m_tree(first, last, comp, alloc) {}

//     set(const set& x) : m_tree(x.m_tree) {}
//     ~set() {}
//     set& operator=(const set& x)
//     {
//         m_tree = x.m_tree;
//         return *this;
//     }

//     explicit set(const key_compare& comp = key_compare(),
//                  const allocator_type& alloc = allocator_type())
//         : m_tree(value_compare(comp), alloc) {}
//     template <class InputIterator>
//     set(InputIterator first, typename ft::enable_if<
//                 !std::numeric_limits<InputIterator>::is_integer,
//                     InputIterator>::type last,
//         const key_compare& comp = key_compare(),
//         const allocator_type& alloc = allocator_type())
//         : m_tree(first, last, comp, alloc) {}
//     set(const set& x) : m_tree(x.m_tree) {}
//     ~set() {}
//     set& operator=(const set& x) {
//         m_tree = x.m_tree;
//         return (*this);
//     }

//     Iterators
//     iterator begin()
//     { return (m_tree.begin()); }
//     const_iterator begin() const
//     { return (m_tree.begin()); }

//     iterator end()
//     { return (m_tree.end()); }
//     const_iterator end() const
//     { return (m_tree.end()); }

//     reverse_iterator rbegin()
//     { return (m_tree.rbegin()); }
//     const_reverse_iterator rbegin() const
//     { return (m_tree.rbegin()); }

//     reverse_iterator rend()
//     { return (m_tree.rend()); }
//     const_reverse_iterator rend() const
//     { return (m_tree.rend()); }

//     Capacity
//     bool empty() const
//     { return (m_tree.empty()); }
//     size_type size() const
//     { return (m_tree.size()); }
//     size_type max_size() const
//     { return (m_tree.max_size()); }

//     Modifiers
//     ft::pair<iterator, bool> insert(const value_type& val)
//     { return (m_tree.insert(val)); }
//     iterator insert(iterator position, const value_type& val)
//     { return (m_tree.insert(position, val)); }
//     template <class InputIterator>
//     void insert(
//         InputIterator first, typename ft::enable_if<
//                 !std::numeric_limits<InputIterator>::is_integer,
//                     InputIterator>::type last)
//         { return (m_tree.insert(first, last)); }

//     void erase(iterator position)
//     { m_tree.erase(position); }
//     size_type erase(const key_type& k)
//     { return (m_tree.erase(k)); }
//     void erase(iterator first, iterator last)
//     { m_tree.erase(first, last); }

//     void swap(set& x)
//     { m_tree.swap(x.m_tree); }
//     void clear()
//     { m_tree.clear(); }

//     Observers
//     key_compare key_comp() const
//     { return (key_compare()); }
//     value_compare value_comp() const
//     { return (key_comp()); }

//     Operatrions
//     iterator find(const key_type& k)
//     { return (m_tree.find(k)); }
//     const_iterator find(const key_type& k) const
//     { return (m_tree.find(k)); }

//     size_type count(const key_type& k) const
//     { return (m_tree.count(k)); }

//     iterator lower_bound(const key_type& k)
//     { return (m_tree.lower_bound(k)); }
//     const_iterator lower_bound(const key_type& k) const
//     { return (m_tree.lower_bound(k)); }
//     iterator upper_bound(const key_type& k)
//     { return (m_tree.upper_bound(k)); }
//     const_iterator upper_bound(const key_type& k) const
//     { return (m_tree.upper_bound(k)); }
//     ft::pair<const_iterator, const_iterator> equal_range(
//         const key_type& k) const
//         { return (m_tree.equal_range(k)); }
//     ft::pair<iterator, iterator> equal_range(const key_type& k)
//     { return (m_tree.equal_range(k)); }

//     Allocator
//     allocator_type get_allocator() const
//     { return (m_tree.get_allocator()); }

// private:
//     rbtree<value_type, value_compare, allocator_type> m_tree;
// };

// #endif

#ifndef __SET_HPP__
#define __SET_HPP__

#include "rbtree.hpp"

namespace ft {
template <class Key, class Compare = std::less<Key>,
          class Alloc = std::allocator<Key> >
class set {
 public:
    typedef Key key_type;
    typedef Key value_type;
    typedef Compare key_compare;
    typedef Compare value_compare;
    typedef rbtree<value_type, value_compare, Alloc> rb_type;
    typedef Alloc allocator_type;
    typedef typename rb_type::reference reference;
    typedef typename rb_type::const_reference const_reference;
    typedef typename rb_type::pointer pointer;
    typedef typename rb_type::const_pointer const_pointer;
    typedef typename rb_type::iterator iterator;
    typedef typename rb_type::const_iterator const_iterator;
    typedef typename rb_type::reverse_iterator reverse_iterator;
    typedef typename rb_type::const_reverse_iterator const_reverse_iterator;
    typedef typename rb_type::difference_type difference_type;
    typedef typename rb_type::size_type size_type;

    explicit set(const key_compare& comp = key_compare(),
                 const allocator_type& alloc = allocator_type())
        : m_tree(value_compare(comp), alloc) {}
    template <class InputIterator>
    set(InputIterator first, typename ft::enable_if<
                !std::numeric_limits<InputIterator>::is_integer,
                    InputIterator>::type last,
        const key_compare& comp = key_compare(),
        const allocator_type& alloc = allocator_type())
        : m_tree(first, last, comp, alloc) {}
    set(const set& x) : m_tree(x.m_tree) {}
    ~set() {}
    set& operator=(const set& x) {
        m_tree = x.m_tree;
        return (*this);
    }

    iterator begin()
    { return (m_tree.begin()); }
    const_iterator begin() const
    { return (m_tree.begin()); }

    iterator end()
    { return (m_tree.end()); }
    const_iterator end() const
    { return (m_tree.end()); }

    reverse_iterator rbegin()
    { return (m_tree.rbegin()); }
    const_reverse_iterator rbegin() const
    { return (m_tree.rbegin()); }

    reverse_iterator rend()
    { return (m_tree.rend()); }
    const_reverse_iterator rend() const
    { return (m_tree.rend()); }

    // Capacity
    bool empty() const
    { return (m_tree.empty()); }
    size_type size() const
    { return (m_tree.size()); }
    size_type max_size() const
    { return (m_tree.max_size()); }

    // Modifiers
    ft::pair<iterator, bool> insert(const value_type& val)
    { return (m_tree.insert(val)); }
    iterator insert(iterator position, const value_type& val)
    { return (m_tree.insert(position, val)); }
    template <class InputIterator>
    void insert(
        InputIterator first, typename ft::enable_if<
                !std::numeric_limits<InputIterator>::is_integer,
                    InputIterator>::type last)
        { return (m_tree.insert(first, last)); }

    void erase(iterator position)
    { m_tree.erase(position); }
    size_type erase(const key_type& k)
    { return (m_tree.erase(k)); }
    void erase(iterator first, iterator last)
    { m_tree.erase(first, last); }

    void swap(set& x)
    { m_tree.swap(x.m_tree); }
    void clear()
    { m_tree.clear(); }

    // Observers
    key_compare key_comp() const
    { return (key_compare()); }
    value_compare value_comp() const
    { return (key_comp()); }

    // Operatrions
    iterator find(const key_type& k)
    { return (m_tree.find(k)); }
    const_iterator find(const key_type& k) const
    { return (m_tree.find(k)); }

    size_type count(const key_type& k) const
    { return (m_tree.count(k)); }

    iterator lower_bound(const key_type& k)
    { return (m_tree.lower_bound(k)); }
    const_iterator lower_bound(const key_type& k) const
    { return (m_tree.lower_bound(k)); }
    iterator upper_bound(const key_type& k)
    { return (m_tree.upper_bound(k)); }
    const_iterator upper_bound(const key_type& k) const
    { return (m_tree.upper_bound(k)); }
    ft::pair<const_iterator, const_iterator> equal_range(
        const key_type& k) const
        { return (m_tree.equal_range(k)); }
    ft::pair<iterator, iterator> equal_range(const key_type& k)
    { return (m_tree.equal_range(k)); }

    // Allocator
    allocator_type get_allocator() const
    { return (m_tree.get_allocator()); }

private:
    rbtree<value_type, value_compare, Alloc> m_tree;

};

}  // namespace ft
#endif /* ifndef __SET_HPP__ */
