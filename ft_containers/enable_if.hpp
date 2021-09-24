#ifndef ENABLE_IF
#define ENABLE_IF

namespace ft{

template<bool B, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T> { typedef T type; };

template<typename T>
struct less: public std::binary_function<T, T, bool>
{
    bool operator()(const T& x, const T& y) const {
        return (x < y);
    }
};

template <class T1, class T2>
struct pair
{
public :
    typedef T1 first_type;
    typedef T2 second_type;

    first_type first;
    second_type second;

    pair()
    :
        first(),
        second()
    {}

    template<class U, class V>
    pair (const pair<U, V>& pr)
    :
        first(pr.first),
        second(pr.second)
    {}

    pair (const first_type& a, const second_type& b)
    :
        first(a),
        second(b)
    {}

    pair& operator= (const pair& pr)
    {
        if (*this == pr)
            return (*this);
        this->first = pr.first;
        this->second = pr.second;
        return (*this);
    }
};
}


#endif /* ENABLE_IF */
