#ifndef _CONSTRUCT_H_
#define _CONSTRUCT_H_

#include<new>
#include"TypeTraits.h"

namespace MySTL{
	template<class T1,class T2>
	inline void construct( T1* p, const T2& value){
		//placement new ����pָ��ĵ�ַ����һ��T1����������T2����valueΪ���캯���Ĳ���
		new(p)T1(value);
	}
	//��һ���汾 ����һ��ָ��
	template<class T>
	inline void destory(T* ptr){
		ptr->~T();
	}

	//�ڶ����汾������������������ʹ�õ�����traits���ҵ�������ָ������
	//forwarditerator����������д�����㷨�ڴ�������ж�д����
	template<class ForwardIterator>
	inline void destory(ForwardIterator first, ForwardIterator last){
		//_ǰ׺Ϊϵͳ�����������ɼ�ϸ��
		//traits������ָ����������
		_destory(first, last, value_type(first));
	}
	//traits�Ƿ�ΪPOD����ͬ��������ʽ
	template<class ForwardIterator, class T>
	inline void _destory(ForwardIterator first, ForwardIterator last, T*){
		typedef typename _type_traits<T>::has_trivial_destructor destructor;
		_destory_aux(first, last, destructor());
	}
	//���Զ�������������non-trivial_destructor
	template<class ForwardIterator>
	inline void _destory_aux(ForwardIterator first, ForwardIterator last, _false_type){
		for (; first != last; ++first){
			destory(&*first);
		}
	}
	//Ĭ��ȱʡ��������ִ��
	template<class ForwardIterator>
	inline void _destory_aux(ForwardIterator first, ForwardIterator last, _true_type){}





}
#endif