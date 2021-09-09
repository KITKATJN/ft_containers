#ifndef BDEA1AEC_42FD_4D5D_A47C_A249D0BB0834
#define BDEA1AEC_42FD_4D5D_A47C_A249D0BB0834

#include <memory>
#include <limits>

namespace ft
{
	template < class T, class Alloc = std::allocator<T> > class vector
	{
		typedef Alloc vector_allocator;
		typedef T value_type;
		typedef size_t size_type;
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
		{if (pos >= size())
			throw std::out_of_range;
		return (*this)[pos]}

		const_reference at( size_type pos ) const
		{{if (pos >= size())
			throw std::out_of_range;
		return (*this)[pos]}}

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
		{ return begin() == end(); }
		//{ return (size() == 0); } так нельзя?

		size_type size() const
		{ return (begin() - end()); }
		//return m_size;

		size_type capacity() const
		{ return m_capacity; }

		size_type max_size() const
		{ return (std::min)(std::numeric_limits<size_type>::max() / sizeof(), //sizeof what?
		std::numeric_limits<std::ptrdiff_t>::max()) }

		void reserve( size_type new_cap )
		{ }

		void clear()
		{ }

	private:
		T m_arr;
		size_type m_size;
		size_type m_capacity;
		allocator_type m_allocator; //typedef for allocator_type
	};
};
#endif /* BDEA1AEC_42FD_4D5D_A47C_A249D0BB0834 */

