#ifndef BDEA1AEC_42FD_4D5D_A47C_A249D0BB0834
#define BDEA1AEC_42FD_4D5D_A47C_A249D0BB0834

#include <memory>

namespace ft
{
	template < class T, class Alloc = std::allocator<T> > class vector
	{
		typedef Alloc vector_allocator;
		typedef T value_type;
		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		reverse_iterator rend();
		const_reverse_iterator rend() const;

		size_type size() const
		{ return m_size; }

		reference at( size_type pos )
		{}

		const_reference at( size_type pos ) const
		{}

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

		T* data();

		const T* data() const;

	private:
		T m_arr;
		size_type m_size;
		size_type m_capacity;
		allocator_type m_allocator;
	}
}
#endif /* BDEA1AEC_42FD_4D5D_A47C_A249D0BB0834 *

