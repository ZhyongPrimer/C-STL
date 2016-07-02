#include"VectorTest.h"	
namespace MySTL{
	namespace VectorTest{
		void testCase1(){
			stdVec<int> v1(10, 2);
			tsVec<int> v2(10, 2);
			for (auto i : v2)
				std::cout << v1[i] << ' ';
			std::cout << std::endl;
			assert(MySTL::Test::container_equal(v1,v2));
		}
		void testCase2(){
			stdVec < std::string> v1(2, "hello");
			std::cout << v1.size();
			
				std::cout << v1[1][0];
			tsVec<std::string> v2(2, "hello");
			std::cout << v2.size();
			
			std::cout << v2[1][0];

			assert(MySTL::Test::container_equal(v1, v2));
			v2.push_back("world");
			std::cout << v2[2][0];

			std::cout << std::endl;
		
		}
		void testCase3(){
			tsVec<int> v1(3,4);
			std::cout<<v1.capacity();
			std::cout << std::endl;

			tsVec<int> v2;
			v2.push_back(1);
			std::cout << v2[0] << std::endl;
			v2.push_back(2);
			std::cout << v2[1] << std::endl;
			v2.push_back(3);
			std::cout << v2[2] << std::endl;
			v2.push_back(4);
			std::cout << v2[3] << std::endl;
			for (auto i : v2)
				std::cout << v2[i] << ' ';
			std::cout << v2.size() << std::endl;
			v1.insert(v1.begin(),100);
			std::cout << v1.capacity() << std::endl;
			v1.insert(v1.begin()+3, v2.begin(), v2.end());
			std::cout << v1.capacity() << std::endl;
			for (auto i : v1)
				std::cout << v1[i] << ' ';
			std::cout << std::endl;
			v2.erase(v2.begin(),v2.end());
			std::cout << v2.size() << std::endl;
			for (auto i : v2)
				std::cout << v2[i] << ' ';
			std::cout << std::endl;
		}
		void testAllCase(){
			testCase1();
			testCase2();
			testCase3();
	}
 }
}