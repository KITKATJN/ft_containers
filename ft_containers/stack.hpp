#ifndef C6211693_4050_4270_B471_19CD1E4B0F1B
#define C6211693_4050_4270_B471_19CD1E4B0F1B

#include "vector.hpp"

namespace ft{
template <class T, class Container = ft::vector<T> > class stack
{
public:
    typedef T value_type;
    typedef Container container_type;
    typedef size_t size_type;

    explicit stack (const container_type& ctnr = container_type()) : m_stack(ctnr)
    {  }

    bool empty() const
    { return m_stack.empty(); }

    size_type size() const
    { return m_stack.size(); }

    value_type& top()
    { return m_stack.back(); }

    const value_type& top() const
    { return m_stack.back(); }

    void push (const value_type& val)
    { m_stack.push_back(val); }

    void pop()
    { m_stack.pop_back(); }

    bool Eq(const stack<T, Container> &X) const
    { return (m_stack == X.m_stack); }

    bool Lt(const stack<T, Container> &X) const
    { return (m_stack < X.m_stack); }

private:
    container_type m_stack;
};

template <class T, class Container>
  bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
  { return (lhs.Eq(rhs)); }

  template <class T, class Container>
  bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
  { return !(lhs == rhs); }

  template <class T, class Container>
  bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
  { return lhs.Lt(rhs); }

template <class T, class Container>
  bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
  { return !(rhs < lhs); }

template <class T, class Container>
  bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
  { return rhs < lhs; }

template <class T, class Container>
  bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
  { return !(lhs < rhs); }

}
#endif /* C6211693_4050_4270_B471_19CD1E4B0F1B */
