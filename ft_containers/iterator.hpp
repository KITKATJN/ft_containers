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
class iterator_traits<T*>
{
public:
    typedef ptrdiff_t difference_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef ft::random_access_iterator_tag iterator_category;
};

template <class T>
class iterator_traits<const T*> {
public:
    typedef ptrdiff_t difference_type;
    typedef T value_type;
    typedef const T* pointer;
    typedef const T& reference;
    typedef ft::random_access_iterator_tag iterator_category;
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

{
public:
    typedef reverse_iterator<Iterator> Myt;
    typedef Iterator iterator_type;
    typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
    typedef typename ft::iterator_traits<Iterator>::pointer pointer;
    typedef typename ft::iterator_traits<Iterator>::reference reference;

    reverse_iterator() : current(){ }

    explicit reverse_iterator (iterator_type it) : current(it) { }

    reverse_iterator(const reverse_iterator<Iterator>& iter) : current(iter.base()){ }

    template <class Iter>
    reverse_iterator(const reverse_iterator<Iter>& iter) : current(iter.base()){ }

    template< class U >
    reverse_iterator& operator=( const reverse_iterator<U>& other )
    {
        if (*this != other)
            this->current = other.getIterator();
        return *this;
    }

    iterator_type base() const
    { return (current); }

    reference operator*() const
    { Iterator tmp = current;tmp--;return *tmp; }

    pointer operator->()
    { return std::addressof(operator*()); }

    reference operator[]( difference_type n ) const { return *(*this + n);}
    reverse_iterator&    operator++() { --this->current; return *this; }
    reverse_iterator&    operator--() { ++this->current; return *this; }
    reverse_iterator    operator++(int) {reverse_iterator it(*this); --this->current; return it; }
    reverse_iterator    operator--(int) {reverse_iterator it(*this); ++this->current; return it; }
    reverse_iterator    operator+( difference_type n ) const { return reverse_iterator(current - n); }
    reverse_iterator    operator-( difference_type n ) const { return reverse_iterator(current + n); }
    reverse_iterator&    operator+=( difference_type n )
    {
        current -= n;
        return *this;
    }
    reverse_iterator& operator-=( difference_type n )
    {
        current += n;
        return *this;
    }

    iterator_type getIterator() const { return this->current; }

    // bool Eq(const Myt& Y) const
    // { return current == Y.current; }

private:
    iterator_type current;

};

template <class Iterator, class Iter>
bool operator==(const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iter>& rhs) {
    return (lhs.base() == rhs.base());
}
template <class Iterator, class Iter>
bool operator!=(const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iter>& rhs) {
    return (lhs.base() != rhs.base());
}
template <class Iterator, class Iter>
bool operator<(const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iter>& rhs) {
    return (lhs.base() > rhs.base());
}
template <class Iterator, class Iter>
bool operator<=(const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iter>& rhs) {
    return (lhs.base() >= rhs.base());
}
template <class Iterator, class Iter>
bool operator>(const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iter>& rhs) {
    return (lhs.base() < rhs.base());
}
template <class Iterator, class Iter>
bool operator>=(const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iter>& rhs) {
    return (lhs.base() <= rhs.base());
}

template <class Iterator>
reverse_iterator<Iterator> operator+(
             typename reverse_iterator<Iterator>::difference_type n,
             const reverse_iterator<Iterator>& rev_it) {
    return (rev_it + n);
}
template <class Iterator>
typename reverse_iterator<Iterator>::difference_type operator-(
    const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>& rhs) {
    return (rhs.base() - lhs.base());
}

// template< class Iterator1, class Iterator2 >
// bool operator==( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) {
//     return lhs.Eq(rhs);
// }

// template< class Iterator1, class Iterator2 >
// bool operator!=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) {
//     return !(lhs == rhs);
// }

// template< class Iterator1, class Iterator2 >
// bool operator<( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) {
//     return lhs.base() > rhs.base();
// }

// template< class Iterator1, class Iterator2 >
// bool operator<=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) {
//     return lhs.base() >= rhs.base();
// }

// template< class Iterator1, class Iterator2 >
// bool operator>( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) {
//     return lhs.base() < rhs.base();
// }

// template< class Iterator1, class Iterator2 >
// bool operator>=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) {
//     return lhs.base() <= rhs.base();
// }

// template< class Iter >
// reverse_iterator<Iter> operator+( typename reverse_iterator<Iter>::difference_type n,
//                                     const reverse_iterator<Iter>& it ) {
//     return reverse_iterator<Iter>(it - n);
// }

// template< class Iter >
// reverse_iterator<Iter> operator-( typename reverse_iterator<Iter>::difference_type n,
//                                     const reverse_iterator<Iter>& it ) {
//     return reverse_iterator<Iter>(it + n);
// }

template<typename Value, bool IsConst>
class bidirectional_iterator : public iterator<bidirectional_iterator_tag, Value> {
 public:
     typedef typename conditional<IsConst, const Value, Value>::type    value_type;
     typedef typename conditional<IsConst, const Value*, Value*>::type  pointer;
     typedef typename conditional<IsConst, const Value&, Value&>::type  reference;
     typedef random_access_iterator_tag                                 iterator_category;
     typedef ptrdiff_t                                                  difference_type;

 protected:
     typedef Node<Value>* link_type;
     link_type  current;

 public:
     // Default things
     bidirectional_iterator() : current() { };
     bidirectional_iterator(link_type type) : current(type) { };
     virtual ~bidirectional_iterator() { }
     bidirectional_iterator(const bidirectional_iterator<Value, IsConst> &copy) : current(copy.current) { }

     // operators
     bidirectional_iterator<Value, IsConst>&    operator=(bidirectional_iterator<Value, IsConst> const & copy) {
         if (this == &copy)
             return (*this);
         current = copy.current;
         return (*this);
     }
     operator bidirectional_iterator<Value, true>() const {
         return (bidirectional_iterator<Value, true>(current));
     }

     // logical
     bool   operator==(bidirectional_iterator<Value, IsConst> const & other) { return (current == other.current); }
     bool   operator!=(bidirectional_iterator<Value, IsConst> const & other) { return (current != other.current); }

     // arithmetic
     bidirectional_iterator<Value, IsConst> operator++()
    {
       Node<Value> *p;

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
        return *this;
    }
     bidirectional_iterator<Value, IsConst>   operator++(int) {
         bidirectional_iterator<Value, IsConst> it(*this);
        ++(*this);
        return it;
     }
     bidirectional_iterator<Value, IsConst>&   operator--() {
         Node<Value> *p;

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
     bidirectional_iterator<Value, IsConst>   operator--(int) {
         bidirectional_iterator<Value, IsConst> tmp(*this);

         operator--();
         return (tmp);
     }

     link_type&     base() { return (current); }
     // other
     Value&         operator*() { return (*current->data); }
     const Value&   operator*() const { return (*current->data); }
     Value*         operator->() { return (current->data); }
};

// template<typename T, bool IsConst>
//     bool operator==(bidirectional_iterator<T, FPointer, FReference, IsConst> const &first, bidirectional_iterator<T, SPointer, SReference, IsConst> const &second)
//     { return(first.base() == second.base()); }

// template<typename T, typename FPointer, typename FReference, typename SPointer, typename SReference, bool IsConst>
//     bool operator!=(bidirectional_iterator<T, FPointer, FReference, IsConst> const &first, bidirectional_iterator<T, SPointer, SReference, IsConst> const &second)
//     { return(first.base() != second.base()); }

template <class T, class P, class R>
class random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, T>
{
    public:
        typedef T                                         value_type;
        typedef P                                         pointer;
        typedef R                                         reference;
        typedef random_access_iterator<T, P, R>           It;
        typedef ptrdiff_t                                 difference_type;
        typedef typename ft::random_access_iterator_tag   iterator_category;

        random_access_iterator() : current(0) {}

        random_access_iterator(pointer ptr) : current(ptr) {}

        random_access_iterator(random_access_iterator<T, T*, T&> const &rhs) : current( rhs.getPointer() ) {}

        pointer getPointer() const { return this->current; }

        virtual ~random_access_iterator() {}

        It &operator=(const It &rhs) {
            if (this == &rhs)
                return *this;
            this->current = rhs.current;
            return *this;
        }

        reference operator*() { return *this->current; }
        reference operator*() const { return *this->current; }
        pointer operator->() { return this->current; }
        reference operator[](difference_type index) { return this->current[index]; }

        It& operator++() { ++this->current; return *this; }
        It& operator--() { --this->current; return *this; }
        It  operator++(int) { It it(*this); ++this->current; return it; }
        It  operator--(int) { It it(*this); --this->current; return it; }
        It  operator+(difference_type n) const { return random_access_iterator(this->current + n); }
        It  operator-(difference_type n) const { return random_access_iterator(this->current - n); }
        It& operator+=(difference_type n)  { current += n; return *this; }
        It& operator-=(difference_type n)  { current -= n; return *this; }

        bool   operator==(It const & other) { return (current == other.current); }
        bool   operator!=(It const & other) { return (current != other.current); }
        bool   operator<(It const & other) { return (current < other.current); }
        bool   operator>(It const & other) { return (current > other.current); }
        bool   operator<=(It const & other) { return (current <= other.current); }
        bool   operator>=(It const & other) { return (current >= other.current); }


    private:
        pointer current;
};

template <class T, class P, class R>
random_access_iterator<T, P, R>operator+
(typename random_access_iterator<T, P, R>::difference_type n, random_access_iterator<T, P, R> &rhs) {
    return (rhs + n);
}

template <class T, class P, class R>
random_access_iterator<T, P, R>operator-
(typename random_access_iterator<T, P, R>::difference_type n, random_access_iterator<T, P, R> &rhs) {
    return (rhs - n);
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

// template <class T, class P, class R>
// bool operator!=(const random_access_iterator<T, P, R> &lhs, const random_access_iterator<T, P, R> &rhs) {
//     return (!(lhs == rhs));
// }

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
