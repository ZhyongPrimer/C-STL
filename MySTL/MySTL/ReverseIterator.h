#ifndef _REVERSE_ITERATOR_H_
#define _REVERSE_ITERATOR_H_
//迭代器配接器
#include "Iterator.h"
namespace MySTL{
	template<class Iterator>
	class reverse_iterator_t{
	public:
		//逆向迭代器的5种相应型别都和器对象的正向迭代器相同
		typedef Iterator	iterator_type;
		typedef typename	iterator_traits<Iterator>::iterator_category iterator_category;
		typedef typename	iterator_traits<Iterator>::value_type		 value_type;
		typedef typename	iterator_traits<Iterator>::difference_type	 difference_type;
		typedef typename	iterator_traits<Iterator>::pointer			 pointer;
		typedef typename	iterator_traits<Iterator>::reference		 reference;
		typedef const pointer  const_pointer;
		typedef const reference const_reference;
	private:
		//用来做什么的？
		Iterator base_;
		Iterator cur_;//记录对应正向迭代器
	public:
		//构造、拷贝、析构相关
		reverse_iterator_t() :base_(0), cur_(0){}
		explicit reverse_iterator_t(const iterator_type& it) :base_(it){
			auto temp = it;
			cur_ = --temp;
		}
		template <class Iter>
		reverse_iterator_t(const reverse_iterator_t<Iter>& rev_it){
			base_ = (iterator_type)rev_it.base();
			auto temp = base_;
			cur_ = --temp;
		};

		//template<class Iter>
		//reverse_iterator_t(const reverse_iterator<Iter>& rev_it){
		//	base_ = (iterator_type)rev_it.base();
		//	auto temp = base_;
		//	//对你想迭代器取值，就是对应正向迭代器，后退一个后取值
		//	cur_ = --temp;
		//}
		//其他成员函数
		iterator_type base(){ return base_; }
		reference operator*(){ return *(cur_); }
		const_reference operator*()const{ return *(cur_); }
		pointer operator->(){ return &(operator*()); }
		const_pointer operator->()const { return &(operator*()); }

		reverse_iterator_t& operator++(){
			--base_;
			--cur_;
			return *this;
		}
		//后置返回类型不是引用？
		//
		reverse_iterator_t operator++(int){
			reverse_iterator_t temp = *this;
			++(*this);
			return temp;
		}
		reverse_iterator_t& operator--(){
			++base_;
			++cur_;
			return *this;
		}
		reverse_iterator_t  operator--(int){
			reverse_iterator_t temp = *this;
			--(*this);
			return temp;
		}
		//
		reference operator[](difference_type n){
			return base()[-n - 1];
		}
		reverse_iterator_t operator+(difference_type n)const;
		reverse_iterator_t& operator+=(difference_type n);
		reverse_iterator_t operator-(difference_type n)const;
		reverse_iterator_t& operator-=(difference_type n);

	private:
		//用于何处
		Iterator advanceNStep(Iterator it, difference_type n,
			bool right, random_access_iterator_tag){
			if (right)
				it += n;

			else
				it -= n;
			return it;
		}
		//前进或者后退N步
		Iterator advanceNStep(Iterator it, difference_type n,
			bool right, //true -> \ false <-
			bidirectional_iterator_tag){
			difference_type i;
			difference_type absN = n >= 0 ? n : -n;
			if ((right&&n > 0) || (!right&&n < 0)){
				for (i = 0; i != absN; ++i){
					it = it + 1;
				}
			}
			else if ((!right&&n>0) || (right&&n < 0)){
				for (i = 0; i != absN; ++i){
					it = it - 1;
				}
			}
			return it;
		}
	public:
		template<class Iterator>
		friend bool operator==(const reverse_iterator_t<Iterator>& lhs,
							   const reverse_iterator_t<Iterator>& rhs);
		template<class Iterator>
		friend bool operator!=(const reverse_iterator_t<Iterator>& lhs,
			const reverse_iterator_t<Iterator>& rhs);
		template<class Iterator>
		friend bool operator<(const reverse_iterator_t<Iterator>& lhs,
			const reverse_iterator_t<Iterator>& rhs);
		template<class Iterator>
		friend bool operator<=(const reverse_iterator_t<Iterator>& lhs,
			const reverse_iterator_t<Iterator>& rhs);
		template<class Iterator>
		friend bool operator>(const reverse_iterator_t<Iterator>& lhs,
			const reverse_iterator_t<Iterator>& rhs);
		template<class Iterator>
		friend bool operator>=(const reverse_iterator_t<Iterator>& lhs,
			const reverse_iterator_t<Iterator>& rhs);
		
		template<class Iterator>
		friend reverse_iterator_t<Iterator> operator +(
			typename reverse_iterator_t<Iterator>::difference_type n,
			const reverse_iterator_t<Iterator>& rev_it);
		template <class Iterator>
		friend typename reverse_iterator_t<Iterator>::difference_type operator- (
			const reverse_iterator_t<Iterator>& lhs,
			const reverse_iterator_t<Iterator>& rhs);
	};// end of reverse_iterator_t

	template<class Iterator>//true -> \ false <-
	reverse_iterator_t<Iterator>& reverse_iterator_t<Iterator>::operator += (difference_type n){
		base_ = advanceNStep(base_, n, false, iterator_category());
		cur_ = advanceNStep(cur_, n, false, iterator_category());
		return *this;
	}
	template<class Iterator>//true -> \ false <-
	reverse_iterator_t<Iterator>& reverse_iterator_t<Iterator>::operator -= (difference_type n){
		base_ = advanceNStep(base_, n, true, iterator_category());
		cur_ = advanceNStep(cur_, n, true, iterator_category());
		return *this;
	}
	template<class Iterator>
	reverse_iterator_t<Iterator> reverse_iterator_t<Iterator>::operator + (difference_type n)const{
		reverse_iterator_t<Iterator> res = *this;
		res += n;
		return res;
	}
	template<class Iterator>
	reverse_iterator_t<Iterator> reverse_iterator_t<Iterator>::operator - (difference_type n)const{
		reverse_iterator_t<Iterator> res = *this;
		res -= n;
		return res;
	}

	template <class Iterator>
	bool operator == (const reverse_iterator_t<Iterator>& lhs, const reverse_iterator_t<Iterator>& rhs){
		return lhs.cur_ == rhs.cur_;
	}
	template <class Iterator>
	bool operator != (const reverse_iterator_t<Iterator>& lhs, const reverse_iterator_t<Iterator>& rhs){
		return !(lhs == rhs);
	}
	template <class Iterator>
	bool operator < (const reverse_iterator_t<Iterator>& lhs, const reverse_iterator_t<Iterator>& rhs){
		return lhs.cur_ < rhs.cur_;
	}
	template <class Iterator>
	bool operator >(const reverse_iterator_t<Iterator>& lhs, const reverse_iterator_t<Iterator>& rhs){
		return lhs.cur_ > rhs.cur_;
	}
	template <class Iterator>
	bool operator >= (const reverse_iterator_t<Iterator>& lhs, const reverse_iterator_t<Iterator>& rhs){
		return !(lhs < rhs);
	}
	template <class Iterator>
	bool operator <= (const reverse_iterator_t<Iterator>& lhs, const reverse_iterator_t<Iterator>& rhs){
		return !(lhs > rhs);
	}

	template <class Iterator>
	reverse_iterator_t<Iterator> operator + (
		typename reverse_iterator_t<Iterator>::difference_type n,
		const reverse_iterator_t<Iterator>& rev_it){
		return rev_it + n;
	}
	template <class Iterator>
	typename reverse_iterator_t<Iterator>::difference_type operator - (
		const reverse_iterator_t<Iterator>& lhs,
		const reverse_iterator_t<Iterator>& rhs){
		return lhs.cur_ - rhs.cur_;
	}


	
		


	
}

#endif