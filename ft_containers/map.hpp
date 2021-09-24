#ifndef MAP_HPP
#define MAP_HPP

#include "enable_if.hpp"
#include <memory>

template<
    class Key,
    class T,
    class Compare = ft::less<Key>,
    class Allocator = std::allocator<std::pair<const Key, T> >
> class map
{
public:
    typedef std::ptrdiff_t difference_type;
    typedef size_t size_type;
    typedef K key_type;
    typedef T mapped_type;
    typedef std::pair<const Key, T> value_type;
    typedef Compare key_compare;
    typedef Allocator allocator_type;
    typedef value_type& reference;
    typedef value_type const & const_reference;
    typedef Allocator::pointer pointer;
    typedef Allocator::const_pointer const_pointer;


    // typedef Compare value_compare;
    // typedef Tree<value_type, key_compare> tree_type;
    // typedef typename tree_type::Node node_type;
    // typedef node_type* node_pointer;
    // typedef TreeIterator<value_type, node_type> iterator;
    // typedef TreeIterator<value_type const, node_type const> const_iterator;
    // typedef ReverseIterator<iterator> reverse_iterator;
    // typedef ReverseIterator<const_iterator> const_reverse_iterator;
}
#endif
