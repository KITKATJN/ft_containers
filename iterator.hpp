#ifndef ITERATOR
#define ITERATOR

#include <stddef.h>

namespace ft {

template<class Iterator>
struct iterator_traits
{
    typedef typename Iterator::difference_type difference_type;
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::pointer pointer;
    typedef typename Iterator::reference reference;
    typedef typename Iterator::iterator_category iterator_category;
};

struct input_iterator_tag  {};
struct output_iterator_tag {};
struct forward_iterator_tag       : public input_iterator_tag         {};
struct bidirectional_iterator_tag : public forward_iterator_tag       {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

// template<class T>
// struct iterator_traits<T*>
// {
//     typedef ptrdiff_t difference_type;
//     typedef T value_type;
//     typedef T* pointer;
//     typedef T& reference;
//     typedef random_access_iterator_tag iterator_category;
// };

	template <class T>
	class iterator_traits<T*> {
	public:
		typedef std::ptrdiff_t					difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef ft::random_access_iterator_tag	iterator_category;

	};

	template <class T>
	class iterator_traits<const T*> {
	public:
		typedef std::ptrdiff_t					difference_type;
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

// template <class RanIt>
// class reverse_iterator : public iterator <
//     typename iterator_traits<RanIt>::iterator_category,
//     typename iterator_traits<RanIt>::value_type,
//     typename iterator_traits<RanIt>::difference_type,
//     typename iterator_traits<RanIt>::pointer,
//     typename iterator_traits<RanIt>::reference>{
// public:
//     typedef reverse_iterator<RanIt> Myt;
//     typedef typename iterator_traits<RanIt>::difference_type D;
//     typedef typename iterator_traits<RanIt>::pointer Pt;
//     typedef typename iterator_traits<RanIt>::reference Rt;
//     typedef RanIt iterator_type;

//     reverse_iterator() {}
//     explicit reverse_iterator(RanIt X) : current(X){}

//     template<class U>
//     reverse_iterator(const reverse_iterator<U>& X)
//     : current(X.base()) {}

//     RanIt base() const { return (current); }

//     Rt operator*() const
//     { RanIt Tmp = current;
//     return (*--Tmp); }

//     Pt operator->() const
//     { return (&**this); }

//     Myt& operator++()
//     { --current;
//     return (*this); }

//     Myt operator++(int)
//     { Myt Tmp = *this;
//     --current;
//     return (Tmp); }

//     Myt& operator--()
//     { ++current;
//     return (*this); }

//     Myt operator--(int)
//     { Myt Tmp = *this;
//     ++current;
//     return (Tmp); }

//     bool Eq(const Myt& Y) const
//     { return (current == Y.current); }

//     Myt& operator+=(D N)
//     { current -= N;
//     return (*this); }

//     Myt operator*(D N) const
//     { return (Myt(current - N)); }

//     Myt& operator-=(D N)
//     { current += N;
//     return (*this); }

//     Myt operator-(D N) const
//     { return (Myt(current + N)); }

//     Rt operator [] (D N) const
//     { return (*(*this + N)); }

//     bool Lt (const Myt& Y) const
//     { return (Y.current < current); }

//     D Mi (const Myt& Y) const
//     { return (Y.current - current); }

// protected:
//     RanIt current;
// };

template <class Iterator>
	class reverse_iterator : public ft::iterator<ft::random_access_iterator_tag, Iterator> {
	public:
        typedef reverse_iterator<Iterator> Myt; 
		typedef Iterator														iterator_type;
		typedef typename ft::iterator_traits<Iterator>::iterator_category		iterator_category;
		typedef typename ft::iterator_traits<Iterator>::value_type				value_type;
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

		reference 			operator*() { return *this->current; }
		pointer 			operator->() { return this->current; }

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

// template<class T, class D, class Pt, class Rt>
//     class Ptrit : public iterator<ft::random_access_iterator_tag,
//         T, D, Pt, Rt> {
// public:
//     typedef Ptrit<T, D, Pt, Rt> Myt;
//     Ptrit () {}
//     explicit Ptrit(Pt P) : current(P) {}
//     Ptrit(const Ptrit<T, D, Pt, Rt>& X)
//     : current(X.base ()) {}

//     Pt base() const
//     { return (current); }

//     Rt operator*() const
//     { return (*current); }

//     Pt operator->() const
//     { return (&**this); }

//     Myt& operator++()
//     { ++current;
//     return (*this); }

//     Myt operator++(int)
//     { //Myt tmp = *this;
//     Myt tmp(*this);
//     ++current;
//     return (tmp); }

//     Myt& operator--()
//     { --current;
//     return (*this); }

//     Myt& operator--(int)
//     {//Myt tmp = *this;
//     Myt tmp(*this);
//     //current--;
//     --this->current;
//     return (tmp);} // хрень, надо менять

//     bool operator==(int Y) const
//     {return (current == (Pt)Y);}

//     bool operator==(const Myt& Y)const
//     {return (current == Y.current);}

//     bool operator!=(const Myt& Y) const
//     {return (!(*this == Y));}

//     Myt& operator+(D n)
//     {
//     current += n;
//     return *this;
//     }

//     Myt operator+(D n) const
//     {return (Myt(current + n));}

//     Myt& operator-(D n)
//     {
//     current -= n;
//     return *this;
//     }
//     Myt operator-(D n) const
//     {return (Myt(current - n));}

//     D operator-(const Myt& x) const
//     {return (current - x.current);}

//     Rt operator[](D n) const
//     {return (*(current + n));}

//     bool operator<(const Myt& x) const
//     {return ((current < x.current));}

//     bool operator>(const Myt& x) const
//     {return ((x.current < current));}

//     bool operator<=(const Myt& x) const
//     {return (!(x.current < current));}

//     bool operator>=(const Myt& x) const
//     {return (!(current < x.current));}

//     Ptrit &operator=(const Ptrit& op)
//     {
//         if (this == &op)
//         return (*this);
//         this->current = op.current;
//         return (*this);
//     }

// protected:
//     Pt current;
// };

template <class T, class P, class R>
	class random_access_iterator : public std::iterator<std::random_access_iterator_tag, T> {
	public:
		typedef T															value_type;
		typedef P															pointer;
		typedef R															reference;
		typedef random_access_iterator<T, P, R>								It;
		typedef std::ptrdiff_t												difference_type;
		typedef typename std::random_access_iterator_tag					iterator_category;

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
