#ifndef VECTOR
#define VECTOR

#include <memory>
#include <limits>
#include <algorithm>
#include <iostream>
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
    typedef random_access_iterator<T,  pointer, reference> iterator;
    typedef reverse_iterator<iterator> reverse_iterator;
    typedef random_access_iterator<T,  const_pointer, const_reference> const_iterator;
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
    { return reverse_iterator(end() - 1); }

    const_reverse_iterator rbegin() const
    { return const_reverse_iterator(end() - 1); }

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
        for (size_type i = 0; i < m_size; i++)
        { m_allocator.destroy(m_vector + i); }
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
        for (size_type i = 0; i < count; i++)
        {
            m_allocator.construct(m_vector + i, value);
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
        //std::uninitialized_copy(first, last, m_vector);
        size_type i = 0;
        for (; first != last; first++)
        {
            m_allocator.construct(m_vector + i, *first);// std::iterator_traits<InputIt>::value_type);
            i++;
        }
    }

    iterator erase (iterator position)
    {
        difference_type pos = position - begin();
        //std::cout << *(m_vector + pos) << "<--------------------\n";
        m_allocator.destroy(m_vector + pos);
        for (size_type i = static_cast<size_type>(pos); i < m_size - 1; i++){
            m_allocator.construct(m_vector + i, m_vector[i + 1]);
        }
        //std::copy(position + 1, end(), position - 1);
        m_size--;
        return position;
        //return erase(position, position + 1);
    }

    iterator erase (iterator first, iterator last)
    {
        if (m_size == 0)
            return first;
        if (first != last){
            size_type destr = last - begin();
            for (size_type i = static_cast<size_type>(first - begin()); i < destr; i++){
                m_allocator.destroy(m_vector + i);
                //std::cout << " d-> " << m_vector[i];
            }
            //std::cout << std::endl;
            for (size_type i = static_cast<size_type>(first - begin()); i < m_size - (last - first); i++){
                m_allocator.construct(m_vector + i, m_vector[i + (last - first)]);
                //std::cout << " c-> " << m_vector[i + (last - first)];
            }
            //std::cout << std::endl;
        m_size -= (last - first);
        //  // iterator ret;
        //  // for (; first != last; first++)
        //  // {
        //  //   ret = erase(first);
        //  // }
        //  // return ret;
        //  // for (size_type i = 0; i < static_cast<size_type>(last - first); i++){
        //  //   ret = erase(first++);
        //      //first = begin() + fir;
        //      //std::cout << "d " << m_vector[i] << i;
        //  //}
        //  //return ret;
        }
        else{
            erase(first);
        }
        return first;

        // iterator ret = first;
        // for (; &(*first) != &(*first); first++)
        // {
        //  m_allocator.destroy(&(*first));
        // }
        // for (int i = 0; i < (last - ret); i++)
        // {
        //  //m_allocator.construct()
        //  m_allocator.construct(first + i, last + i);
        //  m_allocator.destroy(&(*last) + i);
        // }
        // m_size -= (last - ret);
        // return (iterator(ret));

        // std::cout << *first << " <-f2 \n";
        // first++;
        // iterator ret;
        // for (; first != last; first++)
        // {
        //  std::cout << *first << " <-f "; // это не работает, хотя должно!
        //  ret = erase(first);
        // }
        // return ret;

        // iterator fir = first;

        // if (first != last)
        // {
        //  while (first != last)
        //  {
        //      m_allocator.destroy(m_vector + (first - begin()));
        //      ++first;
        //  }
        //  std::copy(last, end(), fir - 1);
        //  m_size -= (last - fir);
        // }
        // return fir;
    }

    void push_back( const T& value )
    {
        if (m_capacity == 0)
            reserve(4);
        else if (m_size < m_capacity)
            reserve(2 * m_capacity);
        m_allocator.construct(m_vector + m_size, value);
        m_size++;
    }

    void resize( size_type count, T value = T() )
    {
        //std::cout << "value = " << value << std::endl;
        if (count == m_capacity)
            return ;
        if (count > m_capacity)
        {
            reserve(count);
            for (size_type i = m_size; i < m_capacity; i++)
            {
                //::new((void*)(m_vector + i)) T();
                //std::cout << "value = " << value << std::endl;
                m_allocator.construct(m_vector + i, value);
            }
        }
        else
            reserve(count);
        m_size = count;
    }

    iterator insert( iterator pos, const T& value )
    {
        if (m_capacity == m_size)
        {
            //size_type old_m_size = m_size;
            reserve(2 * m_capacity);
            //m_size = old_m_size;
        }
        for (size_type i = m_size; i != static_cast<size_type>(pos - begin()); i--)
        {
            //std::cout << " f->" << m_vector[i] << " s->" << m_vector[i - 1] << std::endl;
            m_allocator.construct(m_vector + i, m_vector[i - 1]);
        }
        m_allocator.construct(m_vector + static_cast<size_type>(pos - begin()), value);
        m_size++;
        return pos;
    }

    void insert (iterator pos, size_type n, const value_type& value)
    {
        if (m_capacity == m_size)
        {
            //size_type old_m_size = m_size;
            reserve(2 * m_capacity > n ? 2 * m_capacity : n);
            //m_size = old_m_size;
        }
        for (size_type i = m_size; i != static_cast<size_type>(pos - begin()); i--)
        {
            //std::cout << " f->" << m_vector[i] << " s->" << m_vector[i - 1] << std::endl;
            m_allocator.construct(m_vector + i + n - 1, m_vector[i - 1]);
        }
        for (size_type i = 0; i < n; i++)
        {
            m_allocator.construct(m_vector + static_cast<size_type>(pos - begin()) + i, value);
        }
        //m_allocator.construct(m_vector + static_cast<size_type>(pos - begin()), value);
        m_size += n;
    }

    template <class InputIterator>
    void insert (iterator position, InputIterator first, typename ft::enable_if<
                    !std::numeric_limits<InputIterator>::is_integer,
                        InputIterator>::type last)
    {
        (void)position;
        m_size = static_cast<size_type>(last - first);
        m_capacity = m_size;
        m_vector = m_allocator.allocate(m_capacity);
        for (size_t i = 0; i < m_size; i++)
        {
            m_allocator.construct(m_vector + i, *(first + i));
        }

    }

    void swap (vector& x)
    {
        pointer m_vector_swap = x.m_vector;
        size_type m_size_swap = x.m_size;
        size_type m_capacity_swap = x.m_capacity;
        std::allocator<T> m_allocator_swap = x.m_allocator;

        x.m_allocator = this->m_allocator;
        x.m_capacity = this->m_capacity;
        x.m_size = this->m_size;
        x.m_vector = this->m_vector;
        this->m_vector = m_vector_swap;
        this->m_size = m_size_swap;
        this->m_capacity = m_capacity_swap;
        this->m_allocator = m_allocator_swap;
    }

    explicit vector (const allocator_type& alloc = allocator_type()):
        m_vector(0), m_size(0), m_capacity(0), m_allocator(alloc) {
        m_vector = m_allocator.allocate(0);
        //m_allocator.construct(m_vector, 1);
    }

    explicit vector (size_type n, const value_type& val = value_type(),
        const allocator_type& alloc = allocator_type()):
    m_size(n), m_capacity(n)
    {
        (void)alloc;
        m_vector = m_allocator.allocate(n);
        for (size_type i = 0; i < n; i++)
        {
            m_allocator.construct(m_vector + i, val);
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
            for (size_type i = 0; i < m_size; i++)
            {
                m_allocator.construct(m_vector + i, *(first + i));
            }
        }

    ~vector()
    {
        clear();
        //std::cout << "-*--*--*-destructor call\n";
        m_allocator.deallocate(m_vector, m_capacity);
    }

private:
    pointer             m_vector;
    size_type           m_size;
    size_type           m_capacity;
    std::allocator<T>   m_allocator; //typedef for allocator_type
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

