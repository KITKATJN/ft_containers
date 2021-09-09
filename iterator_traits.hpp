#ifndef ITERATOR_TRAITS
#define ITERATOR_TRAITS

namespace ft {
template<class It>
struct iterator_traits
{
	typedef typename It::iterator_category iterator_category;
	typedef typename It::value_type value_type;
	typedef typename It::distance_type distance_type;
	typedef typename It::pointer pointer;
	typedef typename It::reference reference;
};
};

#endif /* ITERATOR_TRAITS */
