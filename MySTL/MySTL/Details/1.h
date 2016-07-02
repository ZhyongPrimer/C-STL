#ifndef _VECTOR_IMPL_H_
#define _VECTOR_IMPL_H_

namespace MySTL{
	/**************************拷贝，构造，析构***************************/
	template<class T,class Alloc>
	vector<T, Alloc>::~vector(){
		destroy_and_deallocate_all();
	}
	template<class T, class Alloc>
	vector<T, Alloc>::vector(const size_type n){
		allocate_and_fill_n(n, value_type());	
	}
	template<class T, class Alloc>
	vector<T, Alloc>::vector(const size_type n, const value_type& value){
		allocate_and_fill_n(n, value);
	}
	template<class T, class Alloc>
	template<class InputIterator>
	vector<T, Alloc>::vector(InputIterator first, InputIterator last){//不太懂这个是什么意思
		//处理指针和数字的区别的函数
		//根据是否整形来分派函数，是整形则不是迭代器，否则认为是迭代器
		//两个函数声明不同 怎么区别
		vector_aux(first, last, typename std::is_integral<InputIterator>::type());
	}
	template<class T, class Alloc>
	vector<T, Alloc>::vector(const vector& v){
		allocate_and_copy(v.start, v.finish);
	}
	template<class T, class Alloc>
	vector<T, Alloc>::vector(vector&& v){
		//移动构造，是构造对象和临时对象共用相同内存，偷掉临时对象的内存
		start = v.start;
		finish = v.finish;
		end_of_storage = v.end_of_storage;
		//移动拷贝构造，右值引用在拷贝之后，需要初始化为0
		//如果不赋值为0，会触发析构函数，把偷来的内存析构掉
		v.start = v.finish = v.end_of_storage = 0;
	}
	template<class T, class Alloc>
	vector<T, Alloc>& vector<T, Alloc>::operator=(const vector& v){//返回类型为vector<T, Alloc>
		if (*this != v)
			allocate_and_copy(v.start, v.finish);
		return *this;
	}
	//移动赋值操作符 
	//不懂这个内容
	template<class T,class Alloc>
	vector<T, Alloc>& vector<T, Alloc>::operator=(vector&& v){//右值不需要const修饰
		if (this != &v){//指向的不是同一块内存
			destroy_and_deallocate_all();
			start = v.start;
			finish = v.finish;
			end_of_storage = v.end_of_storage;
			v.start = v.finish = v.end_of_storage = 0;
		}
		return *this;
	}

	/********************和容器容量相关*******************************/
	template<class T, class Alloc>
	//调整容器容量为n，默认初始值
	void vector<T, Alloc>::resize(size_type n, value_type val = value_type()){
		if (n < size()){
			data_allocator::destroy(start + n, finish);
			finish = start + n;
		}
		else if (n>size() && n<capacity()){
			auto lengthOfInsert = n - size();
			finish = MySTL::uninitialized_fill_n(finish, lengthOfInsert, val);
		}
		else if (n>capacity()){
			auto lengthOfInsert = n - size();
			//获得新的容量大小？？？？？？
			T* newStart = data_allocator::allocate(get_new_capacity(lengthOfInsert));
			T* newFinish = MySTL::uninitialized_copy(begin(),end(), newStart);
			newFinish = MySTL::uninitialized_fill_n(newFinish, lengthOfInsert, val);

			destroy_and_deallocate_all();
			start = newStart;
			finish = newFinish;
			end_of_storage = start + n;
		}
	}
	template<class T,class Alloc>
	void vector<T, Alloc>::reserve(size_type n){
		//申请至少可以容纳n个元素的大小
		if (n <= capacity())
			return;
		T* newStart = data_allocator::allocate(n);
		T* newFinish = MySTL::uninitialized_copy(begin(), end(), newStart);
		destroy_and_deallocate_all();

		start = newStart;
		finish = newFinish;
		end_of_storage = start + n;	
	}
	
	/***************************修改容器的相关操作***************************/
	template<class T,class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator position){
		return erase(position, position + 1);
	}

	template<class T,class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator first, iterator last){
		//尾部残留对象数
		difference_type lenOfTail = end() - last;
		//删去的对象数目
		difference_type lenOfRemoved = last - first;
		finish = finish - lenOfRemoved;
		for (; lenOfTail != 0; --lenOfTail){
			auto temp = (last - lenOfRemoved);
			*temp = *(last++);
		}
		return first;
	}
	template<class T,class Alloc>
	template<class InputIterator>
	void vector<T, Alloc>::reallocate_and_copy(iterator position, InputIterator first, InputIterator last){
		difference_type newCapacity =get_new_capacity(last - first);

		T* newStart = data_allocator::allocate(newCapacity);
		T* newEndOfStorage = newStart + newCapacity;
		T* newFinish = MySTL::uninitialized_copy(begin(), position, newStart);
		newFinish = MySTL::uninitialized_copy(first, last, newFinish);
		newFinish = MySTL::uninitialized_copy(position, end(), newFinish);

		destroy_and_deallocate_all();
		start = newStart;
		finish = newFinish;
		end_of_storage = newEndOfStorage;
	}
	template<class T,class Alloc>
	void vector<T, Alloc>::reallocate_and_fill_n(iterator position, const size_type& n, const value_type& value){
		difference_type newCapacity = get_new_capacity(n);


		T* newStart = data_allocator::allocate(newCapacity);
		T* newEndOfStorage = newStart + newCapacity;
		T* newFinish = MySTL::uninitialized_copy(begin(), position, newStart);
		newFinish = MySTL::uninitialized_fill_n(newFinish, n, value);
		newFinish = MySTL::uninitialized_copy(position, end(), newFinish);

		destroy_and_deallocate_all();
		start = newStart;
		finish = newFinish;
		end_of_storage = newEndOfStorage;
	}
	template<class T,class Alloc>
	template<class InputIterator>
	void vector<T, Alloc>::insert_aux(iterator position,InputIterator first,
		InputIterator last,std::false_type){
		difference_type locationLeft = end_of_storage - finish;//剩余容量
		difference_type locationNeed=distance(first,last);// last-first	

		//备用空间>=新增元素
		if (locationLeft >= locationNeed){
			//新增元素<插入点之后现有的元素个数
			if (finish - position > locationNeed){
				MySTL::uninitialized_copy(finish - locationNeed, , finish, finish);
				std::copy_backward(position, finish - locationNeed, finish);
				std::copy(first, last, position);
			}
			else{
				iterator temp = MySTL::uninitialized_copy(first + (finish - position), last, finish);
				MySTL::uninitialized_copy(position, finish, temp);
				std::copy(first, first + (finish - position), position);
			}
			finish += locationNeed;
		}
		else{//为什么不用
			reallocate_and_copy(position, first, last);
		}
	}
	template<class T,class Alloc>
	template<class Integer>
	void vector<T, Alloc>::insert_aux(iterator position, Integer n, const value_type& value, std::true_type){
		assert(n!=0);
		difference_type locationLeft = end_of_storage - finish;
		difference_type locationNeed = n;
		if (locationLeft >= locationNeed){
			auto tempPtr = end() - 1;
			for (; tempPtr - position >= 0; --tempPtr){//move the [position, finish_) back
				construct(tempPtr + locationNeed, *tempPtr);
			}
			MySTL::uninitialized_fill_n(position, n, value);
			finish += locationNeed;
		}
		else{
			reallocate_and_fill_n(position, n, value);
		}
	}
	template<class T,class Alloc>
	template<class InputIterator>
	void vector<T, Alloc>::insert(iterator position, InputIterator first, InputIterator last){
		insert_aux(position, first, last, typename std::is_integral<size_type>::type());
	}
	template<class T,class Alloc>
	void vector<T, Alloc>::insert(iterator position,const size_type n, const value_type& value){
		insert_aux(position, n, value, typename std::_Is_integral<size_type>::type());
	}
	template<class T,class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(iterator position, const value_type& value){
		const auto index = position - begin();
		insert(position, 1, value);
		return begin() + index;
	}
	template<class T,class Alloc>
	void vector<T, Alloc>::push_back(const value_type& value){
		insert(end(), value);
	}
	/************************逻辑比较操作相关****************************/
	template<class T,class Alloc>
	bool vector<T, Alloc>::operator==(const vector& v)const{
		if (size() != v.size())
			return false;
		else{
			auto ptr1 = start;
			auto ptr2 = v.start;
			for (; (ptr1 != finish) && (ptr2 != v.finish); ++ptr1, ++ptr2){
				if (*ptr1 != *ptr2)
					return false;
			}
			return true;
		}
	}
	template<class T,class Alloc>
	bool vector<T, Alloc>::operator!=(const vector& v)const{
		return !(*this == v);
	}
	template<class T,class Alloc>
	bool operator==(const vector<T,Alloc>& v1, const vector<T,Alloc> v2){
		return (v1 == v2);
	}
	template<class T, class Alloc>
	bool operator!=(const vector<T, Alloc>& v1, const vector<T, Alloc> v2){
		return !(v1 == v2);
	}

	/***************************************************************/
	template<class T,class Alloc>
	void vector<T, Alloc>::shrink_to_fit(){
		T* t = (T*)data_allocator::allocate(size());
		finish = MySTL::uninitialized_copy(start, finish, t);
		data_allocator::deallocate(start, capacity());
		start = t;
		end_of_storage = finish;
	}
	//swap()没有实现
	template<class T,class Alloc>
	void vector<T, Alloc>::swap(vector& v){
		if (this != &v){
			MySTL::swap(start, v.start);
			MySTL::swap(finish, v.finish);
			MySTL::swap(end_of_storage,v.end_of_storage);
		}
	}
	template<class T,class Alloc>
	void vector<T, Alloc>::pop_back(){
		--finish;
		data_allocator::destroy(finish);
	}
	template<class T, class Alloc>
	void vector<T, Alloc>::destroy_and_deallocate_all(){
		if (capacity() != 0){
			data_allocator::destroy(start, finish);
			data_allocator::deallocate(start, capacity());
		}
	}
	template<class T,class Alloc>
	void vector<T, Alloc>::allocate_and_fill_n(const size_type n, const value_type& value){
		start = data_allocator::allocate(n);
		MySTL::uninitialized_fill_n(n, value);
		finish = end_of_storage = start + n;
	}
	template<class T, class Alloc>
	template<class InputIterator>
	void vector<T, Alloc>::allocate_and_copy(InputIterator first, InputIterator last){
		start = data_allocator::allocate(last - first);
		finish=MySTL::uninitialized_copy(first, last, start);
		end_of_storage = finish;
	}
	template<class T,class Alloc>
	template<class Integer>
	void vector<T, Alloc>::vector_aux(Integer n, const value_type& value, std::true_type){
		allocate_and_fill_n(n, value);
	}
	template<class T,class Alloc>
	template<class InputIterator>
	void vector<T, Alloc>::vector_aux(InputIterator first, InputIterator last, std::false_type){
		allocate_and_copy(first, last);
	}

	template<class T,class Alloc>
	typename vector<T,Alloc>::size_type 
		vector<T, Alloc>::get_new_capacity(size_type len)const{
			size_type oldCapacity = end_of_storage - start;
			auto res = MySTL::max(oldCapacity, len);
			size_type newCapacity = (oldCapacity != 0 ? (oldCapacity + res) : len);
			return newCapacity;
		}
}

#endif