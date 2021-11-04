#ifndef LEXICOGRAPHICAL_COMPARE
# define LEXICOGRAPHICAL_COMPARE

namespace ft
{
	template<typename In, typename In2>
	bool lexicographical_compare(In first, In last, In2 first2, In2 last2)
	{
		for( ; first !=last && first2 != last2; ++first, ++first2)
		{
			if (*first < *first2)
				return true;
			if (*first2 < *first)
				return false;
		}
		return (first == last && first2 == last2);
	};


	/*
	template<class InputIt1, class InputIt2>
	bool equal( InputIt first1, InputIt1 last1, inputIt2 first2 )
	{
		while (first1 != last1) {
			if (!(*first1 == *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}
	*/

}

#endif