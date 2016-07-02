#ifndef _VECTORTEST_H_
#define _VECTORTEST_H_

#include"../Vector.h"
#include"TestUtil.h"

#include<vector>
#include<iostream>
#include<iterator>
#include<string>
#include<array>

namespace MySTL{
	namespace VectorTest{
		template<class T>
		using stdVec = std::vector<T>;
		template<class T>
		using tsVec = MySTL::vector<T>;

		void testCase1();
		void testCase2();
		void testCase3();
		void testCase4();
		void testCase5();
		void testAllCase();

		
	}
}
#endif