#ifndef BDEA1AEC_42FD_4D5D_A47C_A249D0BB0834
#define BDEA1AEC_42FD_4D5D_A47C_A249D0BB0834

#include <memory>
#include <limits>
#include <algorithm>
#include <iostream>
#include "iterator.hpp"
#include "enable_if.hpp"

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
    typedef Ptrit<T, difference_type, pointer, reference> iterator;
    typedef reverse_iterator<iterator> reverse_iterator;
    typedef Ptrit<T, difference_type, const_pointer, const_reference> const_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

    iterator begin()
    { return iterator(m_vector); }

    const_iterator begin() const
    { return iterator(m_vector); }

    iterator end()
    { return iterator(m_vector + m_size); }

    const_iterator end() const
    { return iterator(m_vector + m_size); }

    reverse_iterator rbegin()
    { return reverse_iterator(end() - 1); }

    // const_reverse_iterator rbegin() const;
    // { return const_reverse_iterator(end() - 1); }

    reverse_iterator rend();
    const_reverse_iterator rend() const;

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
        return nullptr;
    else
        return begin();}

    const T* data() const
    {if (size() == 0)
        return nullptr;
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


    // iterator insert( iterator pos, const T& value )
    // {}

    explicit vector (const allocator_type& alloc = allocator_type()):
        m_vector(nullptr), m_size(0), m_capacity(0), m_allocator(alloc) {
        // m_vector = m_allocator.allocate(1);
        // m_allocator.construct(m_vector, 1);
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

    // template <class InputIterator>
    // vector (InputIterator first, InputIterator last,
    //  const allocator_type& alloc = allocator_type());

    ~vector()
    {
        clear();
        std::cout << "-*--*--*-destructor call\n";
        m_allocator.deallocate(m_vector, m_capacity);
    }

private:
    pointer m_vector;
    size_type m_size;
    size_type m_capacity;
    std::allocator<T> m_allocator; //typedef for allocator_type
};
};
#endif /* BDEA1AEC_42FD_4D5D_A47C_A249D0BB0834 */

