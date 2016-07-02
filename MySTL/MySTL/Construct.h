#ifndef _CONSTRUCT_H_
#define _CONSTRUCT_H_

#include<new>
#include"TypeTraits.h"

namespace MySTL{
	template<class T1,class T2>
	inline void construct( T1* p, const T2& value){
		//placement new 是在p指向的地址构建一个T1对象，其中以T2类型value为构造函数的参数
		new(p)T1(value);
	}
	//第一个版本 接收一个指针
	template<class T>
	inline void destory(T* ptr){
		ptr->~T();
	}

	//第二个版本，接受两个迭代器，使用迭代器traits，找到迭代器指向类型
	//forwarditerator迭代器允许写入型算法在此区间进行读写操作
	template<class ForwardIterator>
	inline void destory(ForwardIterator first, ForwardIterator last){
		//_前缀为系统级函数，不可见细节
		//traits迭代器指向对象的类型
		_destory(first, last, value_type(first));
	}
	//traits是否为POD，不同的西沟方式
	template<class ForwardIterator, class T>
	inline void _destory(ForwardIterator first, ForwardIterator last, T*){
		typedef typename _type_traits<T>::has_trivial_destructor destructor;
		_destory_aux(first, last, destructor());
	}
	//有自定义析构函数，non-trivial_destructor
	template<class ForwardIterator>
	inline void _destory_aux(ForwardIterator first, ForwardIterator last, _false_type){
		for (; first != last; ++first){
			destory(&*first);
		}
	}
	//默认缺省析构函数执行
	template<class ForwardIterator>
	inline void _destory_aux(ForwardIterator first, ForwardIterator last, _true_type){}





}
#endif