#ifndef BDEA1AEC_42FD_4D5D_A47C_A249D0BB0834
#define BDEA1AEC_42FD_4D5D_A47C_A249D0BB0834

#include <memory>
#include <limits>
#include <algorithm>
#include "iterator.hpp"

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
	{ return iterator(m_arr); }

	const_iterator begin() const
	{ return iterator(m_arr); }

	iterator end()
	{ return iterator(m_arr + m_size); }

	const_iterator end() const
	{ return iterator(m_arr + m_size); }

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

	void reserve( size_type new_cap )
	{
		if (new_cap <= m_capacity)
			return ;
		pointer new_arr = allocator_type::allocate(new_cap);
		std::uninitialized_copy(begin(), end(), new_arr);
		for (size_type i = 0; i < m_size; i++)
		{ m_allocator.destroy(m_arr + i); }
		m_allocator.deallocate();
		m_arr = new_arr;
		m_capacity = new_cap;
	}

	void clear()
	{ erase(begin(), end()); }

	void pop_back()
	{ erase(end() - 1); }

	iterator erase (iterator position)
	{
		std::copy(position + 1, end(), position);
		std::_Destroy(end() - 2, end() - 1); // правильный ли дестрой? std::_Destroy(end() - 1, end())
		m_size--;
		return position;
	}

	iterator erase (iterator first, iterator last)
	{
		if (first != last)
		{
			//std::copy(last + 1, end(), last);
			std::_Destroy(std::copy(last + 1, end(), last), end());
			m_size -= (last - first);
		}
		return first;
	}


	// iterator insert( iterator pos, const T& value )
	// {}

	explicit vector (const allocator_type& alloc = allocator_type()):
		m_arr(nullptr), m_size(0), m_capacity(0), m_allocator(alloc) {
		// m_arr = m_allocator.allocate(1);
		// m_allocator.construct(m_arr, 1);
	}

	explicit vector (size_type n, const value_type& val = value_type(),
		const allocator_type& alloc = allocator_type()):
	m_size(n), m_capacity(n)
	{
        (void)alloc;
		m_arr = m_allocator.allocate(n);
		for (size_type i = 0; i < n; i++)
		{
			m_allocator.construct(m_arr + i, val);
		}
	}

	// template <class InputIterator>
	// vector (InputIterator first, InputIterator last,
	// 	const allocator_type& alloc = allocator_type());

	~vector()
	{ clear(begin(), end()); }

private:
	pointer m_arr;
	size_type m_size;
	size_type m_capacity;
	std::allocator<T> m_allocator; //typedef for allocator_type
};
};
#endif /* BDEA1AEC_42FD_4D5D_A47C_A249D0BB0834 */

