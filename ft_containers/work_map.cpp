#ifndef MAP_HPP
#define MAP_HPP

#include "enable_if.hpp"
#include "rbtree.hpp"
#include "lexicographical_compare.hpp"
#include "equal.hpp"
#include <memory>

namespace ft
{
// template<
//     class Key,
//     class T,
//     class Compare = ft::less<Key>,
//     class Allocator = std::allocator<std::pair<const Key, T> >
// > class map
// {
// public:
//     typedef std::ptrdiff_t                                  difference_type;
//     typedef size_t                                          size_type;
//     typedef Key                                               key_type;
//     typedef T                                               mapped_type;
//     typedef Compare                                         key_compare;
//     typedef Allocator                                       allocator_type;
//     typedef typename ft::pair<const key_type, mapped_type>  value_type;
//     typedef typename allocator_type::reference														reference;
//     typedef typename allocator_type::const_reference												const_reference;
//     typedef typename allocator_type::pointer														pointer;
//     typedef typename allocator_type::const_pointer                                                  const_pointer;
//     typedef typename ft::bidirectional_iterator<value_type, value_type*, value_type&>               iterator;
//     typedef typename ft::bidirectional_iterator<value_type, const value_type*, const value_type&>   const_iterator;
//     typedef typename ft::reverse_iterator<iterator>													reverse_iterator;
//     typedef typename ft::reverse_iterator<const_iterator>											const_reverse_iterator;

//     class value_compare : ft::binary_function<value_type, value_type, bool>
//     {
//         friend class map;
//         private:
//             bool result_type;
//             Compare comp;
//             value_type first_argument_type;
//             value_type second_argument_type;

//         protected:
//             value_compare( Compare c ):comp(c) {}

//         public:
//             bool operator()( const value_type& lhs, const value_type& rhs ) const
//             { return comp(lhs.first, rhs.first); }
//     };

//     //map() : m_tree() {}

//     //map();
//     explicit map( const Compare& comp = Compare(), const Allocator& alloc = Allocator() )
//         :  m_tree(rbtree<value_type, value_compare, allocator_type>(value_compare(comp), alloc)) {}

//     template< class InputIt >
//     map(InputIt first, typename ft::enable_if<
//                     !std::numeric_limits<InputIt>::is_integer,
//                         InputIt>::type last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) // ft::
//         : m_tree(rbtree<value_type, value_compare, allocator_type>(value_compare(comp), alloc))
//         { insert(first, last); }

//     map( const map& other ) : m_tree(other.m_tree)
//         { m_tree.insert(other.m_tree.begin(), other.m_tree.end()); }

//     ~map(){ }

//     map& operator=( const map& other )
//     {
//         if (other != *this)
//         {
//             m_tree.clear();
//             m_tree.insert(other.m_tree.begin(), other.m_tree.end());
//         }
//         return *this;
//     }

//     allocator_type get_allocator() const
//     { return allocator_type(); }

//     T& at( const Key& key )
//     {
//         if (m_tree.find(key) == m_tree.end())
//             throw std::out_of_range("out of range");
//         *m_tree.find(key);
//     }

//     const T& at( const Key& key ) const
//     {
//         if (m_tree.find(key) == m_tree.end())
//             throw std::out_of_range("out of range"); //check
//         *m_tree.find(key);
//     }

//     T& operator[]( const Key& key )
//     { return((*((this->insert(ft::make_pair(key, mapped_type()))).first)).second); } ///

//     iterator begin()
//     { return m_tree.begin(); }
//     const_iterator begin() const
//     { return m_tree.begin(); }

//     iterator    end()
//     { return m_tree.end(); }
//     const_iterator  end() const
//     { return m_tree.end(); }

//     reverse_iterator    rbegin()
//     { return m_tree.rbegin(); }
//     const_reverse_iterator  rbegin() const
//     { return m_tree.rbegin(); }

//     reverse_iterator    rend()
//     { return m_tree.rend(); }
//     const_reverse_iterator  rend() const
//     { return m_tree.rend(); }

//     bool empty() const
//     { return m_tree.empty(); }

//     size_type	size() const
//     { return m_tree.size(); }

//     size_type	max_size() const
//     { return m_tree.max_size(); }

//     void clear()
//     { m_tree.clear(); }

//     ft::pair<iterator, bool> insert( const value_type& value )
//     { return m_tree.insert(value); }

//     iterator insert( iterator hint, const value_type& value )
//     { return m_tree.insert(hint, value); }

//     template< class InputIt >
//     void insert( InputIt first, typename ft::enable_if<
//                     !std::numeric_limits<InputIt>::is_integer,
//                         InputIt>::type last) // ft::
//     { m_tree.insert(first, last); }

//     void erase( iterator pos )
//     { m_tree.erase(pos); }

//     void erase( iterator first, iterator last )
//     { m_tree.erase(first, last); }

//     size_type erase( const key_type& key )
//     { return erase(ft::make_pair(key, mapped_type())); }

//     void swap( map& other )
//     { return m_tree.swap(other.swap); }

//     size_type count( const Key& key ) const
//     { return m_tree.count(ft::make_pair(key, mapped_type())); }
//     //{ return m_tree.count(key); }

//     iterator find( const Key& key )
//     { return m_tree.find(ft::make_pair(key, mapped_type())); }

//     const_iterator find( const Key& key ) const
//     { return m_tree.find(ft::make_pair(key, mapped_type())); }

//     ft::pair<iterator,iterator> equal_range( const Key& key )
//     { return m_tree.equal_range(ft::make_pair(key, mapped_type())); }

//     std::pair<const_iterator,const_iterator> equal_range( const Key& key ) const
//     { return m_tree.equal_range(ft::make_pair(key, mapped_type())); }

//     iterator        lower_bound (const key_type& key) { return m_tree.lower_bound(ft::make_pair(key, mapped_type())); }
//     const_iterator  lower_bound (const key_type& key) const { return m_tree.lower_bound(ft::make_pair(key, mapped_type())); }

//     iterator    upper_bound (const key_type& key) { return m_tree.upper_bound(ft::make_pair(key, mapped_type())); }
//     const_iterator  upper_bound (const key_type& key) const { return m_tree.upper_bound(ft::make_pair(key, mapped_type())); }

//     key_compare key_comp() const
//     { return key_compare(); }

//     value_compare value_comp() const
//     { return (value_compare(key_compare())); }
// private:

//     rbtree<value_type, value_compare, allocator_type> m_tree;
    //rbtree<value_type, value_compare, allocator_type> m_tree;


	template <class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map {
	public:
		typedef Key																						key_type;
		typedef T																						mapped_type;
		typedef typename ft::pair<const key_type, mapped_type>											value_type;

	private:

		class value_compare
		{
			friend class map;
		protected:
			Compare _comp;
			value_compare(Compare c) : _comp(c) {}

		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator()(const value_type& x, const value_type& y) const {
				return _comp(x.first, y.first);
			}
		};

	public:

		typedef Compare																					key_compare;
		typedef Alloc																					allocator_type;
		typedef typename allocator_type::reference														reference;
		typedef typename allocator_type::const_reference												const_reference;
		typedef typename allocator_type::pointer														pointer;
		typedef typename allocator_type::const_pointer													const_pointer;

		typedef typename ft::bidirectional_iterator<value_type, value_type*, value_type&>				iterator;
		typedef typename ft::bidirectional_iterator<value_type, const value_type*, const value_type&>	const_iterator;

		typedef typename ft::reverse_iterator<iterator>													reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>											const_reverse_iterator;

		typedef typename std::size_t																	size_type;
		typedef typename std::ptrdiff_t																	difference_type;

		///////////////////////MEMBER FUNCTION///////////////////////

		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
		_tree(rbtree<value_type, value_compare, allocator_type>(value_compare(comp), alloc)) {}

		template <class InputIterator>
  		map(InputIterator first, typename ft::enable_if<
                    !std::numeric_limits<InputIterator>::is_integer,
                        InputIterator>::type last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
		_tree(rbtree<value_type, value_compare, allocator_type>(value_compare(comp), alloc))
		{
			insert(first, last);
		}

		map(const map& x) :
		_tree(rbtree<value_type, value_compare, allocator_type>(value_compare(Compare()), Alloc()))
		{
			_tree.insert(x._tree.begin(), x._tree.end());
		}

		~map() {}

		map& operator=(const map& x)
		{
			_tree.clear();
			_tree.insert(x._tree.begin(), x._tree.end());
			return(*this);
		}

		/////////////////////////////////////////////////////////////

		/////////////////////////ITERATORS///////////////////////////

		iterator				begin() { return _tree.begin(); }
		const_iterator			begin() const { return _tree.begin(); }

		iterator				end() { return _tree.end(); }
		const_iterator			end() const { return _tree.end(); }

		reverse_iterator		rbegin() { return _tree.rbegin(); }
		const_reverse_iterator	rbegin() const { return _tree.rbegin(); }

		reverse_iterator		rend() { return _tree.rend(); }
		const_reverse_iterator	rend() const { return _tree.rend(); }

		/////////////////////////////////////////////////////////////

		//////////////////////////CAPACITY///////////////////////////

		bool		empty() const { return _tree.empty(); }

		size_type	size() const { return _tree.size(); }

		size_type	max_size() const { return _tree.max_size();}

		/////////////////////////////////////////////////////////////

		///////////////////////ELEMENT ACCESS////////////////////////

		mapped_type& operator[] (const key_type& k) {
			return((*((this->insert(ft::make_pair(k, mapped_type()))).first)).second);
		}

		/////////////////////////////////////////////////////////////

		//////////////////////////MODIFIERS//////////////////////////

		pair<iterator,bool>	insert (const value_type& val) { return _tree.insert(val) ; }

		iterator			insert (iterator position, const value_type& val) { return _tree.insert(position, val); }

		template <class InputIterator>
  		void				insert (InputIterator first, typename ft::enable_if<
                    !std::numeric_limits<InputIterator>::is_integer,
                        InputIterator>::type last) {
			return _tree.insert(first, last);
		}

		void		erase (iterator position) { _tree.erase(position); }

		size_type	erase (const key_type& k) { return _tree.erase(ft::make_pair(k, mapped_type())); }

     	void		erase (iterator first, iterator last) { _tree.erase(first, last); }

		void		swap(map& x) { _tree.swap(x._tree); }

		void		clear() { _tree.clear(); }

		/////////////////////////////////////////////////////////////

		//////////////////////////OBSERVERS//////////////////////////

		key_compare		key_comp() const { return _tree.value_comp()._comp; }

		value_compare	value_comp() const { return _tree.value_comp(); }

		/////////////////////////////////////////////////////////////

		//////////////////////////OPERATION//////////////////////////

		iterator		find (const key_type& k) { return _tree.find(ft::make_pair(k, mapped_type())); }
		const_iterator	find (const key_type& k) const { return _tree.find(ft::make_pair(k, mapped_type())); }

		size_type 		count (const key_type& k) const { return _tree.count(ft::make_pair(k, mapped_type())); }

		iterator		lower_bound (const key_type& k) { return _tree.lower_bound(ft::make_pair(k, mapped_type())); }
		const_iterator	lower_bound (const key_type& k) const { return _tree.lower_bound(ft::make_pair(k, mapped_type())); }

		iterator		upper_bound (const key_type& k) { return _tree.upper_bound(ft::make_pair(k, mapped_type())); }
		const_iterator	upper_bound (const key_type& k) const { return _tree.upper_bound(ft::make_pair(k, mapped_type())); }

		pair<const_iterator,const_iterator> equal_range (const key_type& k) const {	return _tree.equal_range(ft::make_pair(k, mapped_type()));}
		pair<iterator,iterator>             equal_range (const key_type& k) { return  _tree.equal_range(ft::make_pair(k, mapped_type()));}

		/////////////////////////////////////////////////////////////

		//////////////////////////ALLOCATOR//////////////////////////

		allocator_type get_allocator() const { return allocator_type(); }

		/////////////////////////////////////////////////////////////
	private:
		rbtree<value_type, value_compare, allocator_type>				_tree;

};

template<class K, class T, class C, class A >
bool operator==( const ft::map<K, T, C, A>& lhs,
                const ft::map<K, T, C, A>& rhs )
{ return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin())); }

template<class K, class T, class C, class A >
bool operator!=( const ft::map<K, T, C, A>& lhs,
                const ft::map<K, T, C, A>& rhs )
{ return !(lhs == rhs); }

template<class K, class T, class C, class A >
bool operator<( const ft::map<K, T, C, A>& lhs,
                const ft::map<K, T, C, A>& rhs )
{ return ( ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

template<class K, class T, class C, class A >
bool operator<=( const ft::map<K, T, C, A>& lhs,
                const ft::map<K, T, C, A>& rhs )
{ return !( rhs < lhs); }

template<class K, class T, class C, class A >
bool operator>( const ft::map<K, T, C, A>& lhs,
                const ft::map<K, T, C, A>& rhs )
{ return rhs < lhs; }

template<class K, class T, class C, class A >
bool operator>=( const ft::map<K, T, C, A>& lhs,
                const ft::map<K, T, C, A>& rhs )
{ return !(lhs < rhs); }

template<class K, class T, class C, class A >
void swap( ft::map<K, T, C, A>& lhs,
                ft::map<K, T, C, A>& rhs )
{ lhs.swap(rhs); }

}

#endif /* MAP */
