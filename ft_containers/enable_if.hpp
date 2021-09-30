#ifndef ENABLE_IF
#define ENABLE_IF

namespace ft{

template<bool B, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T> { typedef T type; };

// template<typename T>
// struct less: public std::binary_function<T, T, bool>
// {
//     bool operator()(const T& x, const T& y) const {
//         return (x < y);
//     }
// };

	template <class Arg1, class Arg2, class Result>
  	struct binary_function
	{
    	typedef Arg1 	first_argument_type;
    	typedef Arg2 	second_argument_type;
    	typedef Result 	result_type;
  	};

	template <class T>
	struct less : binary_function <T,T,bool>
	{
  		bool operator() (const T& x, const T& y) const
		{
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

    // pair& operator= (const pair& pr)
    // {
    //     if (*this == pr)
    //         return (*this);
    //     this->first = pr.first;
    //     this->second = pr.second;
    //     return (*this);
    // }
};

template <class T1, class T2>
    bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
        return lhs.first == rhs.first && lhs.second == lhs.second; }

    template <class T1, class T2>
    bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(lhs == rhs); }

    template <class T1, class T2>
    bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
        return lhs.first < rhs.first || !(rhs.first < lhs.first && lhs.second < rhs.second);
    }

    template <class T1, class T2>
    bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(rhs < lhs); }

    template <class T1, class T2>
    bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return rhs < lhs; }

    template <class T1, class T2>
    bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(lhs < rhs); }

    template <class T1, class T2>
        pair<T1, T2> make_pair(const T1& x, const T2& y) { return ft::pair<T1,T2>(x,y); }

template <typename T>
struct Node
{
    T    *data;
    Node *parent;
    Node *left;
    Node *right;
    bool color; //true = red false = black

    Node(T *data) {
        this->data = data;
        left = right = parent = NULL;
        this->color = true;
    }
};

template <typename T>
void swap(T &t1, T &t2)
{
    T tmp = t1;
    t1 = t2;
    t2 = tmp;
}

}


#endif /* ENABLE_IF */
