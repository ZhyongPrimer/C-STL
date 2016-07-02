#ifndef _UNINITIALIZEDFUNCTIONS_H_
#define _UNINITIALIZEDFUNCTIONS_H_

#include"Algorithm.h"
#include"Construct.h"
#include"Iterator.h"
#include"TypeTraits.h"

namespace MySTL{
	//三个全局函数，用于未初始化空间上
	/***********************************************************/
	template<class InputIterator,class ForwardIterator>
	ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last,
		ForwardIterator result, _true_type);
	template<class InputIterator, class ForwardIterator>
	ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last,
		ForwardIterator result, _false_type);

	template<class InputIterator, class ForwardIterator>
	inline ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result){
		typedef typename _type_traits<iterator_traits<InputIterator>::value_type>::is_POD_type is_POD;
		return _uninitialized_copy_aux(first, last, result, is_POD());
	}
	//POD
	template<class InputIterator, class ForwardIterator>
	inline ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last,
		ForwardIterator result, _true_type){
		//return copy(first, last, result);
		memcpy(result, first, (last - first)*sizeof(*first));
		return result + (last - first);
	}
	//non-POD 必须一个一个的元素构造，无法批量进行
	template<class InputIterator, class ForwardIterator>
	ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last,
		ForwardIterator result, _false_type){
		ForwardIterator cur = result;
		for (; first != last; ++first,++cur){
			construct(cur, *first);	
		}
		return cur;
	}
	/*****************************************************************/
	template<class ForwardIterator,class T>
	void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last,
		const T& value,_true_type);
	template<class ForwardIterator, class T>
	void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last,
		const T& value,_false_type);

	template<class ForwardIterator, class T>
	void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& value){
		typedef typename _type_traits<iterator_traits<ForwardIterator>::value_type>::is_POD_type is_POD;
		 _uninitialized_fill_aux(first, last, value, is_POD());
	}
	//POD类型，由函数模板的参数推导机制得到
	template<class ForwardIterator, class T>
	inline void  _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last,
		const T& value, _true_type){
		fill(first, last, value);
	}
	//non-POD 同上
	template<class ForwardIterator, class T>
	void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last,
		const T& value, _false_type){
		ForwardIterator cur = first;
		for (; cur != last; ++cur){
			construct(cur, value);
		}
	}

	/*********************************************************************************/
	template<class ForwardIterator,class Size,class T>
	inline ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& value, _true_type){
		return fill_n(first, n, value);
	}
	template<class ForwardIterator, class Size, class T>
	ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& value, _false_type){
		ForwardIterator cur = first;
		for (; n > 0; --n, ++cur){
			construct(cur, value);
		}
		return cur;
	}
	template<class ForwardIterator, class Size, class T>
	inline ForwardIterator _uninitialized_fill_n(ForwardIterator first, Size n, const T& value, T*){
		typedef typename _type_traits<T>::is_POD_type is_POD;
		return _uninitialized_fill_n_aux(first, n, value, is_POD());
	}
	template<class ForwardIterator, class Size, class T>
	inline ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n, const T& value){
		return _uninitialized_fill_n(first, n, value, value_type(first));
	}



}
#endif