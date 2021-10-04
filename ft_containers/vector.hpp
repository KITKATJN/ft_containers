#ifndef VECTOR
#define VECTOR

#include <memory>
#include <limits>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <iostream> // delete
#include "iterator.hpp"
#include "enable_if.hpp"
#include "lexicographical_compare.hpp"
#include "equal.hpp"

namespace ft
{
template < class T, class Alloc = std::allocator<T> > class vector
{
public:
    typedef Alloc allocator_type;
    typedef T value_type;
    typedef size_t size_type;
    typedef typename allocator_type::reference reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;
    typedef typename allocator_type::difference_type difference_type;
    typedef random_access_iterator<T, false> iterator;
    typedef reverse_iterator<iterator> reverse_iterator;
    typedef random_access_iterator<T, true> const_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

    iterator begin()
    { return iterator(m_vector); }

    const_iterator begin() const
    { return const_iterator(m_vector); }

    iterator end()
    { return iterator(m_vector + m_size); }

    const_iterator end() const
    { return const_iterator(m_vector + m_size); }

    reverse_iterator rbegin()
    { return reverse_iterator(end()); }

    const_reverse_iterator rbegin() const
    { return const_reverse_iterator(end()); }

    reverse_iterator rend()
    { return reverse_iterator(begin()); }

    const_reverse_iterator rend() const
    { return const_reverse_iterator(begin()); }

    reference at( size_type pos )
    { if (pos >= size())
    throw std::out_of_range("out of range\n");
    return (*this)[pos]; }

    const_reference at( size_type pos ) const
    { if (pos >= size())
    throw std::out_of_range("out of range\n");
    return (*this)[pos]; }

    reference operator[]( size_type pos )
    { return (*(begin() + pos)); }

    const_reference operator[]( size_type pos ) const
    { return (*(begin() + pos)); }

    reference front()
    { return (*begin()); }

    const_reference front() const
    { return (*begin()); }

    reference back()
    { return (*(end() - 1)); }

    const_reference back() const
    { return (*(end() - 1)); }

    T* data()
    {if (size() == 0)
        return 0;
    else
        return begin();}

    const T* data() const
    {if (size() == 0)
        return 0;
    else
        return begin();}

    bool empty() const
    { return (m_size == 0); }

    size_type size() const
    { return m_size; }

    size_type capacity() const
    { return m_capacity; }

    size_type max_size() const
    { return m_allocator.max_size(); }

    allocator_type get_allocator() const
    { return m_allocator; }

    void reserve( size_type new_cap )
    {
        if (new_cap <= m_capacity)
            return ;
        pointer new_arr = m_allocator.allocate(new_cap);
        std::uninitialized_copy(begin(), end(), new_arr);
        for (size_type dist = 0; dist < m_size; dist++)
        { m_allocator.destroy(m_vector + dist); }
        m_allocator.deallocate(m_vector, m_capacity);
        m_vector = new_arr;
        m_capacity = new_cap;
    }

    void clear()
    { erase(begin(), end()); }

    void pop_back()
    { erase(end() - 1); }

    void assign( size_type count, const T& value )
    {
        clear();
        m_allocator.deallocate(m_vector, m_capacity);
        m_vector = m_allocator.allocate(count);
        m_capacity = count;
        m_size = count;
        for (size_type dist = 0; dist < count; dist++)
        {
            m_allocator.construct(m_vector + dist, value);
        }
    }

    template< class Iter >
    void assign(Iter first, typename ft::enable_if<
                    !std::numeric_limits<Iter>::is_integer,
                        Iter>::type last)
    {
        clear();
        m_allocator.deallocate(m_vector, m_capacity);
        size_type count = static_cast<size_type>(last - first);
        m_vector = m_allocator.allocate(count);
        m_capacity = count;
        m_size = count;
        size_type dist = 0;
        for (; first != last; first++)
        {
            m_allocator.construct(m_vector + dist, *first);
            dist++;
        }
    }

    iterator erase (iterator position)
    {
        difference_type pos = position - begin();
        m_allocator.destroy(m_vector + pos);
        for (size_type dist = static_cast<size_type>(pos); dist < m_size - 1; dist++){
            m_allocator.construct(m_vector + dist, m_vector[dist + 1]);
        }
        m_size--;
        return position;
    }

    iterator erase (iterator first, iterator last)
    {
        if (m_size == 0)
            return first;
        if (first != last){
            size_type destr = last - begin();
            for (size_type dist = static_cast<size_type>(first - begin()); dist < destr; dist++)
            {
                m_allocator.destroy(m_vector + dist);
            }
            for (size_type dist = static_cast<size_type>(first - begin()); dist < m_size - (last - first); dist++){
                m_allocator.construct(m_vector + dist, m_vector[dist + (last - first)]);
            }
        m_size -= (last - first);
        }
        else{
            erase(first);
        }
        return first;
    }

    void push_back( const T& value )
    {
        if (m_capacity == 0)
            reserve(4);
        else if (m_size >= m_capacity)
            reserve(2 * m_capacity);
        m_allocator.construct(m_vector + m_size, value);
        m_size++;
    }

    void resize( size_type count, T value = T() )
    {
        if (count == m_capacity)
            return ;
        if (count > m_capacity)
        {
            reserve(count);
            for (size_type dist = m_size; dist < m_capacity; dist++)
            {
                m_allocator.construct(m_vector + dist, value);
            }
        }
        else
            reserve(count);
        m_size = count;
    }

    iterator insert( iterator pos, const T& value )
    {
        if (m_capacity == 0)
        {
            reserve(4);
            m_allocator.construct(m_vector + 0, value);
            m_size++;
            return begin();
        }
        if (m_capacity == m_size)
        {
            reserve(2 * m_capacity);
        }
        for (size_type dist = m_size; dist != static_cast<size_type>(pos - begin()); dist--)
        {
            m_allocator.construct(m_vector + dist, m_vector[dist - 1]);
        }
        m_allocator.construct(m_vector + static_cast<size_type>(pos - begin()), value);
        m_size++;
        return pos;
    }

    void insert (iterator pos, size_type n, const value_type& value)
    {
        size_type dist = static_cast<size_type>(pos - this->begin());
        if (dist > m_size)
            return ;
        if (m_size + n >= m_capacity)
            this->reserve(m_size * 2 + n);
        std::memmove(m_vector + dist + n, m_vector + dist, (size_t)(m_size - dist) * sizeof(value_type));
        for (size_type j = 0; j < n; ++j)
            m_allocator.construct(m_vector + dist + j, value);
        m_size += n;
    }

    template <class InputIterator>
    void insert (iterator pos, InputIterator first, typename ft::enable_if<
                    !std::numeric_limits<InputIterator>::is_integer,
                        InputIterator>::type last)
    {
        size_type dist = static_cast<size_type>(pos - this->begin());
        size_type iterDistance = static_cast<size_type>(last - first);
        if (dist > m_size)
            return ;
        if (m_size + iterDistance >= m_capacity)
            this->reserve(m_size * 2 + iterDistance);
        std::memmove(m_vector + dist + iterDistance, m_vector + dist, (size_t)(m_size - dist) * sizeof(value_type));
        for (size_type j = 0; j < iterDistance; ++j)
            m_allocator.construct(m_vector + dist + j, *(first + j));
        m_size += iterDistance;
    }

    void swap (vector& x)
    {
        ft::swap(m_size, x.m_size);
        ft::swap(m_capacity, x.m_capacity);
        ft::swap(m_vector, x.m_vector);
    }

    explicit vector (const allocator_type& alloc = allocator_type()):
        m_vector(NULL), m_size(0), m_capacity(0), m_allocator(alloc) {
        m_vector = m_allocator.allocate(1);
    }

    explicit vector (size_type n, const value_type& val = value_type(),
        const allocator_type& alloc = allocator_type()):
    m_size(n), m_capacity(n)
    {
        (void)alloc;
        m_vector = m_allocator.allocate(n);
        for (size_type dist = 0; dist < n; dist++)
        {
            m_allocator.construct(m_vector + dist, val);
        }
    }

    template <class InputIterator>
    vector (InputIterator first, typename ft::enable_if<
                    !std::numeric_limits<InputIterator>::is_integer,
                        InputIterator>::type last,
        const allocator_type& alloc = allocator_type()):m_vector(0), m_size(0), m_capacity(0), m_allocator(alloc)
        {
            m_size = static_cast<size_type>(last - first);
            m_capacity = m_size;
            m_vector = m_allocator.allocate(m_capacity);
            for (size_type dist = 0; dist < m_size; dist++)
            {
                m_allocator.construct(m_vector + dist, *(first + dist));
            }
        }

        vector (const vector &copy): m_vector(0), m_size(0), m_capacity(0), m_allocator(copy.m_allocator)
        {
            m_vector = m_allocator.allocate(0);
            reserve(copy.capacity());
            try
            {
                for (size_type i = 0; i < copy.size(); i++)
                    push_back(copy[i]);
            }
            catch(...)
            {
                clear();
                m_allocator.deallocate(m_vector, m_capacity);
            }
        }

    vector& operator= ( const vector &x )
    {
        if (this == &x)
            return *this;
        this->~vector();
        m_vector = m_allocator.allocate(x.m_capacity);
        m_size = x.m_size;
        m_capacity = x.m_capacity;
        for (size_type dist = 0; dist < m_size; dist++)
        {
            m_allocator.construct(m_vector + dist, *(x.m_vector + dist));
        }
        return *this;
    }

    ~vector()
    {
        clear();
        m_allocator.deallocate(m_vector, m_capacity);
    }

private:
    pointer             m_vector;
    size_type           m_size;
    size_type           m_capacity;
    allocator_type  m_allocator; //typedef for allocator_type
};

template< class T, class Alloc >
bool operator==( const ft::vector<T,Alloc>& lhs,
                const ft::vector<T,Alloc>& rhs )
{ return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin())); }

template< class T, class Alloc >
bool operator!=( const ft::vector<T,Alloc>& lhs,
                const ft::vector<T,Alloc>& rhs )
{ return !(lhs == rhs); }

template< class T, class Alloc >
bool operator<( const ft::vector<T,Alloc>& lhs,
                const ft::vector<T,Alloc>& rhs )
{ return ( ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

template< class T, class Alloc >
bool operator<=( const ft::vector<T,Alloc>& lhs,
                const ft::vector<T,Alloc>& rhs )
{ return !( rhs < lhs); }

template< class T, class Alloc >
bool operator>( const ft::vector<T,Alloc>& lhs,
                const ft::vector<T,Alloc>& rhs )
{ return rhs < lhs; }

template< class T, class Alloc >
bool operator>=( const ft::vector<T,Alloc>& lhs,
                const ft::vector<T,Alloc>& rhs )
{ return !(lhs < rhs); }

template< class T, class Alloc >
void swap( ft::vector<T,Alloc>& lhs,
                ft::vector<T,Alloc>& rhs )
{ lhs.swap(rhs); }

};
#endif /* VECTOR */

