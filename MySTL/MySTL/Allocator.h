#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_
#include"Alloc.h"
#include"Construct.h"

#include<new>
#include<cassert>
namespace MySTL{
	//以变量数目为单位分配

	template<class T>
	class allocator{
	public:
		typedef T			value_type;
		typedef T*			pointer;
		typedef const T*	const_pointer;
		typedef T&			reference;
		typedef const T&	const_reference;
		typedef size_t		size_type;
		typedef ptrdiff_t	difference_type;
	public:
		//对空间配置操作的函数
		static T* allocate();  //default 分配一个单位的该类型对象
		static T* allocate(size_t n);
		static void deallocate(T* ptr);
		static void deallocate(T* ptr, size_t n);

		//对象构造销毁的函数
		//有指针数据成员变量
		static void construct(T* ptr);
		static void construct(T* ptr, const T& value);
		static void destroy(T* ptr);
		static void destroy(T* first, T* last);
	};
	template<class T>
	T* allocator<T>::allocate(){
		return static_cast<T*>(alloc::allocate(sizeof(T)));
	}
	template<class T>
	T* allocator<T>::allocate(size_t n){
		if (0 == n)
			return 0;
		return static_cast<T*>(alloc::allocate(n*sizeof(n)));
	}

	template<class T>
	void allocator<T>::deallocate(T* ptr){
		alloc::deallocate(static_cast<T*>(ptr), sizeof(T));
	}
	template<class T>
	void allocator<T>::deallocate(T* ptr, size_t n){
		if (0 == n)
			return;
		alloc::deallocate(static_cast<T*>(ptr), n*sizeof(T));
	}

	//placement new 是在p指向的地址构建一个T1对象，其中以T2类型value为构造函数的参数
	template<class T>
	void allocator<T>::construct(T* ptr){
		new(ptr)T();
	}
	template<class T>
	void allocator<T>::construct(T* ptr, const T& value){
		new(ptr)T(value);
	}

	//类似construct 第一个版本  
	template<class T>
	void allocator<T>::destroy(T* ptr){
		ptr->~T();
	}
	//trivial-destroy   non-is_POD
	template<class T>
	void allocator<T>::destroy(T* first, T* last){
		for (; first != last; ++first){
			first->~T();
		}
	}

}
#endif