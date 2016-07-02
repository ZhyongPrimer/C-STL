#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include <cstring>
#include <utility>

#include "Allocator.h"
//#include "Functional.h"
#include "Iterator.h"
#include "TypeTraits.h"
#include "Utility.h"


namespace MySTL{
	//********* [fill] ********************
	//********* [Algorithm Complexity: O(N)] ****************
	template<class ForwardIterator, class T>
	void fill(ForwardIterator first, ForwardIterator last, const T& value)
	{
		for (; first != last; ++first)
			*first = value;
	}
	inline void fill(char *first, char *last, const char& value)
	{
		memset(first, static_cast<unsigned char>(value), last - first);
	}
	inline void fill(wchar_t *first, wchar_t *last, const wchar_t& value)
	{
		memset(first, static_cast<unsigned char>(value), (last - first) * sizeof(wchar_t));
	}
	//********* [fill_n] ********************
	//********* [Algorithm Complexity: O(N)] ****************
	template<class OutputIterator, class Size, class T>
	OutputIterator fill_n(OutputIterator first, Size n, const T& value)
	{
		for (; n > 0; --n, ++first)
			*first = value;
		return first;
	}
	template<class Size>
	char *fill_n(char *first, Size n, const char& value)
	{
		memset(first, static_cast<unsigned char>(value), n);
		return first + n;
	}
	template<class Size>
	wchar_t *fill_n(wchar_t *first, Size n, const wchar_t& value)
	{
		memset(first, static_cast<unsigned char>(value), n * sizeof(wchar_t));
		return first + n;
	}
//********** [distance] ******************************
//********* [Algorithm Complexity: O(N)] ****************
template<class InputIterator>
typename iterator_traits<InputIterator>::difference_type
_distance(InputIterator first, InputIterator last, input_iterator_tag){
	typename iterator_traits<InputIterator>::difference_type dist = 0;
	while (first++ != last){
		++dist;
	}
	return dist;
}
template<class RandomIterator>
typename iterator_traits<RandomIterator>::difference_type
_distance(RandomIterator first, RandomIterator last, random_access_iterator_tag){
	auto dist = last - first;
	return dist;
}
template<class Iterator>
typename iterator_traits<Iterator>::difference_type
distance(Iterator first, Iterator last){
	typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
	return _distance(first, last, iterator_category());
}

//********* [Algorithm Complexity: O(1)] ****************
template <class T>
const T& max(const T& a, const T& b){
	return (a < b) ? b : a;
}
template <class T, class Compare>
const T& max(const T& a, const T& b, Compare comp){
	return (copm(a, b)) ? b : a;
}


}
#endif