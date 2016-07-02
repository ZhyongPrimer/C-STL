#include<iostream>
#include"Test\VectorTest.h"
#include"Vector.h"
#include<string>
using namespace std;

int main(){
	MySTL::VectorTest::testAllCase();
	
	
	string str("hello"),str1,str2;
	char* s = "hello";
	char c = 'a';
	str2 = c;
	str1 = s;
	str = str1 + str2;
	for (auto i : str)
		cout << str[i];
	system("pause");
}
