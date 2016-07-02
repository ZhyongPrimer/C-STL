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
		typedef size_t		size_type;  //ʲô���ͣ�

		typedef reverse_iterator_t<T*>			reverse_iterator;
		typedef reverse_iterator_t<const T*>	const_reverse_iterator;
		//���������Ƕ���ͱ���

	protected:
		typedef allocator<T> data_allocator;
	private:
		iterator start;
		iterator finish;    //��ʾĿǰʹ�ÿռ��β
		iterator end_of_storage;  //��ʾĿǰ���ÿռ��β

		//����ָ��vector��Сn�ͳ�ֵvalue ���캯��ʹ��
		//������䲢��ʼ��
		//void fill_uninitialized(size_type n, const T& value);


		//���졢�����������������
	public:
		vector() :start(0), finish(0), end_of_storage(0){}//Ĭ�Ϲ���
		//����n��������value����ʼ��
		vector(size_type n, const T& value);
		vector(int n, const T& value);
		vector(long n, const T& value);
		explicit vector(size_type n);  //��ʾ��ʼ�� 
		//������������֮���ֵ��ʼ��
		template<class InputIterator>
		vector(InputIterator first, InputIterator last);

		vector(const vector& v);//��������
		vector(vector&& v); //�ƶ���������

		vector& operator=(const vector& v);//��ֵ������
		vector& operator=(vector&& v);//��ֵ  �ƶ���ֵ������
		~vector();

		//�Ƚϲ������
		bool operator==(const vector& v)const;
		bool operator!=(const vector& v)const;

		//���������
		iterator begin(){ return start; }
		const_iterator begin()const { return (start); }   //const����
		const_iterator cbegin()const{ return (start); }
		iterator end(){ return finish; }
		const_iterator end()const { return finish; }
		const_iterator cend()const { return finish; }
		reverse_iterator rbegin(){ return reverse_iterator(finish); }
		const_reverse_iterator crbegin()const { return const_reverse_iterator(finish); }
		reverse_iterator rend(){ return reverse_iterator(start); }
		const_reverse_iterator crend()const { return const_reverse_iterator(start); }

		//���������
		difference_type size() const{ return finish - start; }
		difference_type capacity()const	{ return end_of_storage - start; }
		bool empty()const { return start == finish; }
		void resize(size_type n, value_type val = value_type());//����������СΪn����ʼ��ΪĬ��ֵ
		void resize(size_type n){ resize(n, value_type()); }
		void reserve(size_type n);  //�������ٿ�������n��Ԫ�صĴ�С
		void shrink_to_fit();        //���������������������ﵽ���ʵĴ�С

		//����Ԫ�����
		reference operator[](const difference_type i){ return *(begin() + i); }
		const_reference operator[](const difference_type i)const { return *(begin() + i); }
		reference front(){ return *(begin()); }//����vector��һ��Ԫ��
		const_reference front()const { return *(begin()); }
		reference back(){ return *(end() - 1); }
		const_reference back()const { return *(end() - 1); }
		pointer data(){ return start; } //����vector��һ��Ԫ�ص�ָ��
		const_iterator data()const { return start; }

		//�޸�������صĲ���
		//������� �����������е����ж���ʹ������sizeΪ0�����������������еĿռ�
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

		//�����Ŀռ����������
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
		size_type get_new_capacity(size_type len)const;  //���������µ�����

		//��Ԫ���� һ����������������ǰ
	public:
		template<class T, class Alloc>
		friend bool operator==(const vector<T, Alloc>& v1, const vector<T, Alloc>& v2);
		template<class T, class Alloc>
		friend bool operator!=(const vector<T, Alloc>& v1, const vector<T, Alloc>& v2);
	};
}
#include "Details\Vector.impl.h"
#endif 