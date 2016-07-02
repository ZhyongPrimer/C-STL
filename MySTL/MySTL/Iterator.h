#ifndef _ITERATOR_H_
#define _ITERATOR_H_

#include<crtdefs.h>
namespace MySTL{
	//定义五个空迭代器标记类，traits可以萃取迭代器种类
	//相应型别(tag type)必须是class type，编译器需要遗爱它
	//进行重载决议
	struct input_iterator_tag{};
	struct output_iterator_tag{};
	struct forward_iterator_tag :public input_iterator_tag{};
	struct bidirectional_iterator_tag :public forward_iterator_tag{};
	struct random_access_iterator_tag :public bidirectional_iterator_tag{};

	//其他迭代器应继承与该迭代器
	template<class Category,class T,class Distance=ptrdiff_t,
		class Pionter=T*,class Reference=T&>
	struct Iterator{
		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Distance    difference_type;
		typedef Pionter		pointer;
		typedef Reference	reference;
	};

	//五种迭代器类型
	template<class Distance, class T>
	struct input_iterator{
		typedef	input_iterator_tag		iterator_category;
		typedef T						value_type;
		typedef Distance				difference_type;
		typedef T*						pointer;
		typedef	T&						reference;
	};
	//write only
	struct output_iterator{
		typedef output_iterator_tag		iterator_category;
		typedef void					value_type;
		typedef void					difference_type;
		typedef void					pointer;
		typedef void					reference;
	};
	template<class Distance, class T>
	struct forward_iterator{
		typedef	forward_iterator_tag	iterator_category;
		typedef T						value_type;
		typedef Distance				difference_type;
		typedef T*						pointer;
		typedef	T&						reference;
	};
	template<class Distance, class T>
	struct bidirectional_iterator{
		typedef	bidirectional_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef Distance					difference_type;
		typedef T*							pointer;
		typedef	T&							reference;
	};
	template<class Distance, class T>
	struct random_access_iterator{
		typedef	random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef Distance					difference_type;
		typedef T*							pointer;
		typedef	T&							reference;
	};
	
	//traits  一般具现化
	template<class Iterator>
	struct iterator_traits{
		typedef typename Iterator::iterator_category    iterator_category;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
	};

	//原生指针的偏特化
	template<class T>
	struct iterator_traits<T*>{
		typedef random_access_iterator_tag		iterator_category;
		typedef T								value_type;
		typedef ptrdiff_t						difference_type;
		typedef T*								pointer;
		typedef T&								reference;
	};
	template<class T>
	struct iterator_traits<const T*>{
		typedef random_access_iterator_tag		iterator_category;
		typedef T								value_type;
		typedef ptrdiff_t						difference_type;
		typedef const T*						pointer;
		typedef const T&						reference;
	};

	//一下三个函数如其名
	template<class Iterator>
	inline typename iterator_traits<Iterator>::iterator_category
		itertor_category(const Iterator&){
			typedef typename iterator_traits<Iterator>::iterator_category category;
			return category();
		}
	template<class Iterator>
	inline typename iterator_traits<Iterator>::value_type*
		value_type(const Iterator&){
			return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
		}
	template<class Iterator>
	inline typename iterator_traits<Iterator>::difference_type*
		difference_type(const Iterator&){
			return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
		}
}
#endif