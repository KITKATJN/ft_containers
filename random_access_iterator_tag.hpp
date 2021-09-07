#ifndef D8E59AD7_9804_44EC_AAF4_BC3939597654
#define D8E59AD7_9804_44EC_AAF4_BC3939597654

template<class T, class D, class Pt, class Rt, class Pt2, class Rt2>
	class Ptrit : public ierator<random_access_iterator_tag,
		T, D, Pt, Rt> {
public:
	typedef Ptrit<T, D, Pt, Rt, Pt2, Rt2> Myt;
	Ptrit () {}
	explicit Ptrit(Pt P) : current(P) {}
	Ptrit(const Ptrit<T, D, Pt2, Rt2, Pt2, Rt2>& X)
		: current(X.base ()) {}

	Pt base() const
	{ return (current); }

	Rt operator*() const
	{ return (*current); }

	Pt operator->() const
	{ return (&**this); }

	Myt& operator++()
	{ ++current;
	return (*this); }

	Myt operator++(int)
	{ Myt Tmp = *this;
	++current;
	return (Tmp); }

	Myt& operator--()
	{ --current;
	return (*this); }

	Myt& operator--(int)
	{Myt tmp = *this;
	current--;
	return (tmp);}

	bool operator==(int Y) const
	{return (current == (Pt)Y);}

	bool operator==(const Myt& Y)const
	{return (current == Y.current);}

	bool operator!=(const Myt& Y) const
	{return (!(*this == Y));}

	Myt& operator+(D n)
	{
		current += n;
		return *this;
	}

	Myt operator+(D n) const
	{return (Myt(current + n));}

	Myt& operator-(D n)
	{
		current -= n;
		return *this;
	}
	Myt operator-(D n) const
	{return (Myt(current - n));}

	D operator-(const Myt& x) const
	{return (current - x.current);}

	Rt operator[](D n) const
	{return (*(current + n));}

	bool operator<(const Myt& x) const
	{return ((current < x.current));}

	bool operator>(const Myt& x) const
	{return ((x.current < current));}

	bool operator<=(const Myt& x) const
	{return (!(x.current < current));}

	bool operator>=(const Myt& x) const
	{return (!(current < x.current));}

protected:
	Pt current;
};
#endif /* D8E59AD7_9804_44EC_AAF4_BC3939597654 */
