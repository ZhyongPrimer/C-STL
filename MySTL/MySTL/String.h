#ifndef _STRING_H_
#define _STRING_H_

#include "Allocator.h"
#include "ReverseIterator.h"
#include "UninitializedFunctions.h"
#include "Utility.h"

#include <cstring>
#include <type_traits>

namespace MySTL{

	//the class of string
	class string{
	public:
		typedef char			value_type;
		typedef char *			iterator;
		typedef const char *	const_iterator;
		typedef reverse_iterator_t<char*> reverse_iterator;
		typedef reverse_iterator_t<const char*> const_reverse_iterator;
		typedef char&			reference;
		typedef const char&		const_reference;
		typedef size_t			size_type;
		typedef ptrdiff_t		difference_type;
		//npos is a static member constant value with the greatest possible value for an element of type size_t.
		static const size_t npos = -1;
	private:
		char *start_;
		char *finish_;
		char *endOfStorage_;

		typedef MySTL::allocator<char> dataAllocator;
	public:
		string() :start_(0), finish_(0), endOfStorage_(0){}
		string(const string& str);
		string(string&& str);
		string(const string& str, size_t pos, size_t len = npos);
		string(const char* s);
		string(const char* s, size_t n);
		string(size_t n, char c);
		template <class InputIterator>
		string(InputIterator first, InputIterator last);

		string& operator= (const string& str);
		string& operator= (string&& str);
		string& operator= (const char* s);
		string& operator= (char c);

		~string();

		iterator begin(){ return start_; }
		const_iterator begin()const { return start_; }//和cbegin有什么区别呢？
		iterator end(){ return finish_; }
		const_iterator end()const { return finish_; }
		reverse_iterator rbegin(){ return reverse_iterator(finish_); }
		const_reverse_iterator rbegin()const{ return const_reverse_iterator(finish_); }
		reverse_iterator rend(){ return reverse_iterator(start_); }
		const_reverse_iterator rend()const { return const_reverse_iterator(start_); }
		const_iterator cbegin() const{ return start_; }
		const_iterator cend() const{ return finish_; }
		const_reverse_iterator crbegin() const{ return const_reverse_iterator(finish_); }
		const_reverse_iterator crend() const{ return const_reverse_iterator(start_); }

		size_t size()const { return finish_ - start_; }
		size_t length()const { return size(); }
		size_t capacity()const { return endOfStorage_ - start_; }
		void   clear(){
			dataAllocator::deallocate(finish_,endOfStorage_-finish_);
			endOfStorage_ = finish_;
		}

		char& operator[](size_t pos){ return *(start_ + pos); }
		const char& operator[](size_t pos)const{ return *(start_ + pos); }	
		char& back(){ return *(finish_ - 1); }
		const char& back() const{ return *(finish_ - 1); }
		char& front(){ return *start_; }
		const char& front() const{ return *(start_); }

		void push_back(char c){ insert(end(), c); }
		string& insert(size_t pos, const string& str);
	};
}
#endif