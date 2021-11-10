#ifndef LEXICOGRAPHICAL_COMPARE
# define LEXICOGRAPHICAL_COMPARE

namespace ft
{
	template<typename In, typename In2>
	bool lexicographical_compare(In first1, In last1, In2 first2, In2 last2)
	{
		while (first1 != last1)
		{
			if (first2==last2 || *first2<*first1) 
				return false;
			else if (*first1 < *first2) 
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	};


	template<class InputIt1, class InputIt2>
	bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2 )
	{
		while (first1 != last1) {
			if (!(*first1 == *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	};

}

#endif