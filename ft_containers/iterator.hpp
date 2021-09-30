#ifndef ITERATOR
#define ITERATOR

#include <stddef.h>
#include <memory>
#include "enable_if.hpp"

namespace ft {

struct input_iterator_tag  {};
struct output_iterator_tag {};
struct forward_iterator_tag       : public input_iterator_tag         {};
struct bidirectional_iterator_tag : public forward_iterator_tag       {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template<class Iterator>
struct iterator_traits
{
    typedef typename Iterator::difference_type difference_type;
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::pointer pointer;
    typedef typename Iterator::reference reference;
    typedef typename Iterator::iterator_category iterator_category;
};

	template <class T>
	class iterator_traits<T*> {
	public:
		typedef ptrdiff_t					difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef ft::random_access_iterator_tag	iterator_category;

	};

	template <class T>
	class iterator_traits<const T*> {
	public:
		typedef ptrdiff_t					difference_type;
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef ft::random_access_iterator_tag	iterator_category;
	};

template<class Category, class T, class Distance = ptrdiff_t,
        class Pointer = T*, class Reference = T&>
struct iterator
{
    typedef T         value_type;
    typedef Distance  difference_type;
    typedef Pointer   pointer;
    typedef Reference reference;
    typedef Category  iterator_category;
};

template <class Iterator>
	class reverse_iterator : public ft::iterator<
	typename iterator_traits<Iterator>::iterator_category,
	typename iterator_traits<Iterator>::value_type,
	typename iterator_traits<Iterator>::difference_type,
	typename iterator_traits<Iterator>::pointer,
	typename iterator_traits<Iterator>::reference
	>

	// ft::random_access_iterator_tag, Iterator> , public ft::iterator<ft::bidirectional_iterator_tag, Iterator>
{
	public:
        typedef reverse_iterator<Iterator> Myt;
		typedef Iterator														iterator_type;
		// typedef typename ft::iterator_traits<Iterator>::iterator_category		iterator_category;
		// typedef typename ft::iterator_traits<Iterator>::value_type				value_type;
		typedef typename ft::iterator_traits<Iterator>::difference_type			difference_type;
		typedef typename ft::iterator_traits<Iterator>::pointer					pointer;
		typedef typename ft::iterator_traits<Iterator>::reference				reference;

		reverse_iterator() { this->current = 0; }

		explicit reverse_iterator (iterator_type it) { this->current = it; }

		template <class Iter>
		reverse_iterator(const reverse_iterator<Iter>& rev_it) { this->current = rev_it; }

		template< class U >
		reverse_iterator& operator=( const reverse_iterator<U>& other ) {
			if (*this != other)
				this->current = other.getIterator();
			return *this;
		}

		iterator_type		base() const { return (current); }

		reference 			operator*() const { Iterator tmp = current; tmp--; return *tmp; }//return *this->current; }
		pointer 			operator->() {
			//return this->current;}
			return std::__addressof(operator*()); }

		reference 			operator[]( difference_type n ) const { return this->current[-n]; };

		reverse_iterator&	operator++() { --this->current; return *this; }
		reverse_iterator&	operator--() { ++this->current; return *this; }
		reverse_iterator	operator++(int) {reverse_iterator it(*this); --this->current; return it; }
		reverse_iterator	operator--(int) {reverse_iterator it(*this); ++this->current; return it; }
		reverse_iterator	operator+( difference_type n ) const { return reverse_iterator(this->current - n); }
		reverse_iterator	operator-( difference_type n ) const { return reverse_iterator(this->current + n); }
		reverse_iterator&	operator+=( difference_type n ) { return reverse_iterator(this->current -= n); }
		reverse_iterator&	operator-=( difference_type n ) { return reverse_iterator(this->current += n); }

		iterator_type getIterator() const { return this->current; }

        bool Eq(const Myt& Y) const
        { return current == Y.current; }

	private:
		iterator_type current;

	};

template< class Iterator1, class Iterator2 >
bool operator==( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) {
    return lhs.Eq(rhs);
}

template< class Iterator1, class Iterator2 >
bool operator!=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) {
    return !(lhs == rhs);
}

template< class Iterator1, class Iterator2 >
bool operator<( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) {
    return lhs.base() > rhs.base();
}

template< class Iterator1, class Iterator2 >
bool operator<=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) {
    return lhs.base() >= rhs.base();
}

template< class Iterator1, class Iterator2 >
bool operator>( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) {
    return lhs.base() < rhs.base();
}

template< class Iterator1, class Iterator2 >
bool operator>=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) {
    return lhs.base() <= rhs.base();
}

template< class Iter >
reverse_iterator<Iter> operator+( typename reverse_iterator<Iter>::difference_type n,
                                    const reverse_iterator<Iter>& it ) {
    return reverse_iterator<Iter>(it - n);
}

template< class Iter >
reverse_iterator<Iter> operator-( typename reverse_iterator<Iter>::difference_type n,
                                    const reverse_iterator<Iter>& it ) {
    return reverse_iterator<Iter>(it + n);
}

template<typename T, typename Pointer, typename Reference>
	class bidirectional_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T>{
	public:

		typedef ft::bidirectional_iterator_tag	iterator_category;
		typedef T								value_type;
		typedef ptrdiff_t						difference_type;
		typedef Pointer							pointer;
		typedef Reference						reference;

	private:
		Node<value_type> *current;

	public:

		bidirectional_iterator() : current(NULL) {}

		~bidirectional_iterator() {}

		explicit bidirectional_iterator(Node<value_type> *point) : current(point) {}

		bidirectional_iterator(bidirectional_iterator<T, Pointer, Reference> const &c) : current(c.base()) {}

		Node<value_type> *base() const { return current; }

		bidirectional_iterator &operator=(bidirectional_iterator<T, Pointer, Reference> const &c) {
			current = c.base();
			return *this;
		}

		reference operator*() const { return *current->data; }

		pointer operator->() const { return current->data; }

		bidirectional_iterator operator++() {
			Node<value_type> *p;

			if(current->right)
			{
				current = current->right;
				while(current->left)
					current = current->left;
			}
			else
			{
				p = current->parent;
				while(p && current == p->right)
				{
					current = p;
					p = p->parent;

				}
				current = current->parent;
			}
			return(*this);
		}

		const bidirectional_iterator operator++(int) {
			bidirectional_iterator it(*this);
			++(*this);
			return it;
		}

		bidirectional_iterator operator--() {
			Node<value_type> *p;

			if(current->left)
			{
				current = current->left;
				while(current->right)
					current = current->right;
			}
			else
			{
				p = current->parent;
				while(p && current == p->left)
				{
					current = p;
					p = p->parent;
				}
				current = current->parent;
			}
			return(*this);
		}

		const bidirectional_iterator operator--(int) {
			bidirectional_iterator it(*this);
			--(*this);
			return (it);
		}
	};

template<typename T, typename FPointer, typename FReference, typename SPointer, typename SReference>
	bool operator==(bidirectional_iterator<T, FPointer, FReference> const &first, bidirectional_iterator<T, SPointer, SReference> const &second) {
		return(first.base() == second.base());
	}

	template<typename T, typename FPointer, typename FReference, typename SPointer, typename SReference>
	bool operator!=(bidirectional_iterator<T, FPointer, FReference> const &first, bidirectional_iterator<T, SPointer, SReference> const &second) {
		return(first.base() != second.base());
	}

template <class T, class P, class R>
class random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, T> {
	public:
		typedef T															value_type;
		typedef P															pointer;
		typedef R															reference;
		typedef random_access_iterator<T, P, R>								It;
		typedef ptrdiff_t													difference_type;
		typedef typename ft::random_access_iterator_tag						iterator_category;

		random_access_iterator() : _ptr(0) {}

		random_access_iterator(pointer ptr) : _ptr(ptr) {}

		random_access_iterator(random_access_iterator<T, T*, T&> const &rhs) : _ptr( rhs.getPointer() ) {}

		virtual ~random_access_iterator() {}

		It				&operator=(const It &rhs) {
			if (this == &rhs)
				return *this;
			this->_ptr = rhs._ptr;
			return *this;
		}

		reference		operator*() { return *this->_ptr; }

		pointer			operator->() { return this->_ptr; }

		reference		operator[](difference_type index) { return this->_ptr[index]; }
        reference		operator[](difference_type index) const { return this->_ptr[index]; }

		It&				operator++() { ++this->_ptr; return *this; }
		It&				operator--() { --this->_ptr; return *this; }
		It				operator++(int) { It it(*this); ++this->_ptr; return it; }
		It				operator--(int) { It it(*this); --this->_ptr; return it; }
		It				operator+(difference_type n) const { return random_access_iterator(this->_ptr + n); }
		It				operator-(difference_type n) const { return random_access_iterator(this->_ptr - n); }
		It&				operator+=(difference_type n) const { return random_access_iterator(this->_ptr += n); }
		It&				operator-=(difference_type n) const { return random_access_iterator(this->_ptr -= n); }

		pointer getPointer() const { return this->_ptr; }

	private:
		pointer		_ptr;
	};

template <class T, class P, class R>
random_access_iterator<T, P, R>operator+
(typename random_access_iterator<T, P, R>::difference_type n, random_access_iterator<T, P, R> &rhs) {
    return (rhs + n);
}

template <class T, class P, class R>
typename random_access_iterator<T, P, R>::difference_type operator-(const random_access_iterator<T, P, R> &lhs,
    const random_access_iterator<T, P, R> &rhs) {
    return (lhs.getPointer() - rhs.getPointer());
}

template <class T, class P, class R>
bool operator==(const random_access_iterator<T, P, R> &lhs, const random_access_iterator<T, P, R> &rhs) {
    return (lhs.getPointer() == rhs.getPointer());
}

template <class T, class P, class R>
bool operator!=(const random_access_iterator<T, P, R> &lhs, const random_access_iterator<T, P, R> &rhs) {
    return (!(lhs == rhs));
}

template <class T, class P, class R>
bool operator>(const random_access_iterator<T, P, R> &lhs, const random_access_iterator<T, P, R> &rhs) {
    return (lhs.getPointer() > rhs.getPointer());
}

template <class T, class P, class R>
bool operator<(const random_access_iterator<T, P, R> &lhs, const random_access_iterator<T, P, R> &rhs) {
    return (lhs.getPointer() <rhs.getPointer());
}

template <class T, class P, class R>
bool operator>=(const random_access_iterator<T, P, R> &lhs, const random_access_iterator<T, P, R> &rhs) {
    return (lhs > rhs || lhs == rhs);
}

template <class T, class P, class R>
bool operator<=(const random_access_iterator<T, P, R> &lhs, const random_access_iterator<T, P, R> &rhs) {
    return (lhs < rhs || lhs == rhs);
}


};

#endif /* ITERATOR */
