#ifndef BDEA1AEC_42FD_4D5D_A47C_A249D0BB0834
#define BDEA1AEC_42FD_4D5D_A47C_A249D0BB0834

#include <memory>
#include <limits>
#include "random_access_iterator_tag.hpp"
#include "reverse_iterator.hpp"

namespace ft
{
	template < class T, class Alloc = std::allocator<T> > class vector
	{
		typedef Alloc allocator_type;
		typedef T value_type;
		typedef size_t size_type;
		typedef allocator_type::reference reference;
		typedef allocator_type::const_reference const_reference;
		typedef allocator_type::pointer pointer;
		typedef allocator_type::const_pointer const_pointer;
		typedef allocator_type::difference_type difference_type;
		typedef Ptrit<T, difference_type, pointer, reference> iterator;
		typedef reverse_iterator<iterator> reverse_iterator;
		typedef reverse_iterator<const_iterator> const_reverse_iterator;
		typedef iterator_traits<iterator>::difference_type difference_type;


		iterator begin()
		{ return iterator(m_arr); }

		const_iterator begin() const
		{ return iterator(m_arr); }

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
		//{ return begin() == end(); }
		{ return (m_size == 0); }// так нельзя?

		size_type size() const
		//{ return (begin() - end()); }
		return m_size;

		size_type capacity() const
		{ return m_capacity; }

		size_type max_size() const
		{ return m_allocator.max_size(); }
		//{ return (std::min)(std::numeric_limits<size_type>::max() / sizeof(), //sizeof what?
		//std::numeric_limits<std::ptrdiff_t>::max()) }

		void reserve( size_type new_cap )
		{ }

		void clear()
		{ }

		explicit vector (const allocator_type& alloc = allocator_type()):
			m_size(0), m_capacity(0), m_arr(0), m_allocator(alloc) {
				m_arr = m_allocator.allocate(1);
				m_allocator.construct(m_arr, 1);
			}

		explicit vector (size_type n, const value_type& val = value_type(),
			const allocator_type& alloc = allocator_type()):
			m_size(n), m_capacity()
			{
				m_arr = m_allocator.allocate(n);
				for (size_type i = 0; i < n; i++)
				{
					m_allocator.construct(m_arr + i, val);
				}

			}

		template <class InputIterator>
		vector (InputIterator first, InputIterator last,
			const allocator_type& alloc = allocator_type());

	private:
		pointer m_arr;
		size_type m_size;
		size_type m_capacity;
		std::allocator<T> m_allocator; //typedef for allocator_type
	};
};
#endif /* BDEA1AEC_42FD_4D5D_A47C_A249D0BB0834 */

