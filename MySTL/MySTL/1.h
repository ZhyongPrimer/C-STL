#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <algorithm>
#include <type_traits>

#include "Allocator.h"
#include "Algorithm.h"
#include "Iterator.h"
#include "ReverseIterator.h"
#include "UninitializedFunctions.h"

namespace MySTL{
	template<class T, class Alloc = allocator<T>>
	class vector{
	public:
		typedef T			value_type;
		typedef T*			pointer;
		typedef T*			iterator;
		typedef const T*	const_iterator;
		typedef T&			reference;
		typedef const T&	const_reference;
		typedef ptrdiff_t	difference_type;
		typedef size_t		size_type;  //什么类型？

		typedef reverse_iterator_t<T*>			reverse_iterator;
		typedef reverse_iterator_t<const T*>	const_reverse_iterator;
		//反向迭代器嵌套型别定义

	protected:
		typedef allocator<T> data_allocator;
	private:
		iterator start;
		iterator finish;    //表示目前使用空间的尾
		iterator end_of_storage;  //表示目前可用空间的尾

		//用于指定vector大小n和初值value 构造函数使用
		//用于填充并初始化
		//void fill_uninitialized(size_type n, const T& value);


		//构造、拷贝、析构函数相关
	public:
		vector() :start(0), finish(0), end_of_storage(0){}//默认构造
		//分配n个并且用value填充初始化
		vector(size_type n, const T& value);
		vector(int n, const T& value);
		vector(long n, const T& value);
		explicit vector(size_type n);  //显示初始化 
		//用两个迭代器之间的值初始化
		template<class InputIterator>
		vector(InputIterator first, InputIterator last);

		vector(const vector& v);//拷贝构造
		vector(vector&& v); //移动拷贝构造

		vector& operator=(const vector& v);//赋值操作符
		vector& operator=(vector&& v);//右值  移动赋值操作符
		~vector();

		//比较操作相关
		bool operator==(const vector& v)const;
		bool operator!=(const vector& v)const;

		//迭代器相关
		iterator begin(){ return start; }
		const_iterator begin()const { return (start); }   //const重载
		const_iterator cbegin()const{ return (start); }
		iterator end(){ return finish; }
		const_iterator end()const { return finish; }
		const_iterator cend()const { return finish; }
		reverse_iterator rbegin(){ return reverse_iterator(finish); }
		const_reverse_iterator crbegin()const { return const_reverse_iterator(finish); }
		reverse_iterator rend(){ return reverse_iterator(start); }
		const_reverse_iterator crend()const { return const_reverse_iterator(start); }

		//与容器相关
		difference_type size() const{ return finish - start; }
		difference_type capacity()const	{ return end_of_storage - start; }
		bool empty()const { return start == finish; }
		void resize(size_type n, value_type val = value_type());//调整容器大小为n，初始化为默认值
		void resize(size_type n){ resize(n, value_type()); }
		void reserve(size_type n);  //申请至少可以容纳n个元素的大小
		void shrink_to_fit();        //申请容器减少它的容量达到合适的大小

		//访问元素相关
		reference operator[](const difference_type i){ return *(begin() + i); }
		const_reference operator[](const difference_type i)const { return *(begin() + i); }
		reference front(){ return *(begin()); }//返回vector第一个元素
		const_reference front()const { return *(begin()); }
		reference back(){ return *(end() - 1); }
		const_reference back()const { return *(end() - 1); }
		pointer data(){ return start; } //返回vector第一个元素的指针
		const_iterator data()const { return start; }

		//修改容器相关的操作
		//清空容器 ，销毁容器中的所有对象并使容器的size为0，但不回收容器已有的空间
		void clear();
		void swap(vector& v);
		void push_back(const value_type& value);
		void pop_back();
		iterator insert(iterator position, const value_type& value);
		void insert(iterator posotion, const size_type n, const value_type& value);
		template<class InputIterator>
		void insert(iterator posotion, InputIterator first, InputIterator last);
		iterator erase(iterator position);
		iterator erase(iterator first,iterator last);

		//容器的空间配置器相关
		Alloc get_allocator(){ return data_allocator; }
	private:
		void destroy_and_deallocate_all();
		void allocate_and_fill_n(const size_type n, const value_type& value);
		template<class InputIterator>
		void allocate_and_copy(InputIterator first, InputIterator last);

		template<class InputIterator>
		void vector_aux(InputIterator first, InputIterator last, std::false_type);
		template<class Integer>
		void vector_aux(Integer n, const value_type& value, std::true_type);
		template<class InputIterator>
		void insert_aux(iterator position, InputIterator first, InputIterator last, std::false_type);
		template<class Integer>
		void insert_aux(iterator position, Integer n, const value_type& value, std::true_type);

		void reallocate_and_fill_n(iterator position, const size_type& n, const value_type& value);
		template<class InputIterator>
		void reallocate_and_copy(iterator position, InputIterator first, InputIterator last);
		size_type get_new_capacity(size_type len)const;  //返回申请新的容量

		//友元函数 一般声明在最后或者最前
	public:
		template<class T, class Alloc>
		friend bool operator==(const vector<T, Alloc>& v1, const vector<T, Alloc>& v2);
		template<class T, class Alloc>
		friend bool operator!=(const vector<T, Alloc>& v1, const vector<T, Alloc>& v2);
	};
}
#include "Details\Vector.impl.h"
#endif 