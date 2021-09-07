#ifndef AD0D52DA_0548_4615_A1E0_3A1DF85E73A1
#define AD0D52DA_0548_4615_A1E0_3A1DF85E73A1

template <class RanIt>
class reverse_iterator : public iterator <
	typename iterator_traits<RanIt>::iterator_category,
	typename iterator_traits<RanIt>::value_type,
	typename iterator_traits<RanIt>::difference_type,
	typename iterator_traits<RanIt>::pointer,
	typename iterator_traits<RanIt>::reference>{
public:
	typedef reverse_iterator<RanIt> Myt;
	typedef typename iterator_traits<RanIt>::difference_type D;
	typedef typename iterator_traits<RanIt>::pointer Pt;
	typedef typename iterator_traits<RanIt>::reference Rt;
	typedef RanIt iterator_type;
	reverse_iterator(){}
	explicit reverse_iterator(RanIt X) : current(X){}
	template<class U>
	reverse_iterator(const reverse_iterator<U>& X)
	: current(X.base()) {}
	RanIt base() const { return (current); }
	Rt operator*() const
	{ RanIt Tmp = current;
	return (*--Tmp); }
	Pt operator->() const
	{ return (&**this); }
	Myt& operator++()
	{ --current;
	return (*this); }
	Myt operator++(int)
	{ Myt Tmp = *this;
	--current;
	return (Tmp); }
	Myt& operator--()
	{ ++current;
	return (*this); }
	Myt operator--(int)
	{ Myt Tmp = *this;
	++current;
	return (Tmp); }
	bool Eq(const Myt& Y) const
	{ return (current == Y.current); }
	Myt& operator+=(D N)
	{ current -= N;
	return (*this); }
	Myt operator*(D N) const
	{ return (Myt(current - N)); }
	Myt& operator-=(D N)
	{ current += N;
	return (*this); }
	Myt operator-(D N) const
	{ return (Myt(current + N)); }
	Rt operator [] (D N) const
	{ return (*(*this + N)); }
	bool Lt (const Myt& Y) const
	{ return (Y.current < current); }
	D Mi (const Myt& Y) const
	{ return (Y.current - current); }
protected:
	RanIt current;
};

#endif /* AD0D52DA_0548_4615_A1E0_3A1DF85E73A1 */
