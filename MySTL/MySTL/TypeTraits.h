#ifndef _TYPETRAITS_H_
#define _TYPETRAITS_H_
namespace MySTL{
	//定义模板
	namespace{
		template<bool,class Ta,class Tb>
		struct IfThenElse;	
		template<class Ta,class Tb>
		struct IfThenElse<true, Ta, Tb>{
			using retult = Ta;
		};
		template<class Ta,class Tb>
		struct IfThenElse<false, Ta, Tb>{
			using retult = Tb;
		};
	}

	//类型萃取，定义两个空白类，表示真假，因为编译器在进行参数
	//推导时，编译器只有面对class object 形式的参数才会做参数推导
	struct _true_type{};
	struct _false_type{};

	//
	//萃取传入的T类型的类型特性
	//一般具现化
	template<class T>
	struct _type_traits{
		typedef _false_type		has_trivial_default_constructor;
		typedef _false_type		has_trivial_copy_constructor;
		typedef	_false_type		has_trivial_assignment_operator;
		typedef _false_type		has_trivial_destructor;
		typedef _false_type		is_POD_type;
	};

	//特化版本
	template<>
	struct _type_traits<bool>{
		typedef _true_type		has_trivial_default_constructor;
		typedef _true_type		has_trivial_copy_constructot;
		typedef _true_type		has_trivial_assignment_operator;
		typedef _true_type		has_trivial_destructor;
		typedef _true_type		is_POD_type;

	};
	template<>
	struct _type_traits<char>{
		typedef _true_type		has_trivial_default_constructor;
		typedef _true_type		has_trivial_copy_constructot;
		typedef _true_type		has_trivial_assignment_operator;
		typedef _true_type		has_trivial_destructor;
		typedef _true_type		is_POD_type;
	};
	template<>
	struct _type_traits<unsigned char>{
		typedef _true_type		has_trivial_default_constructor;
		typedef _true_type		has_trivial_copy_constructor;
		typedef _true_type		has_trivial_assignment_operator;
		typedef _true_type		has_trivial_destructor;
		typedef _true_type		is_POD_type;
	};
	template<>
	struct _type_traits<signed char>{
		typedef _true_type		has_trivial_default_constructor;
		typedef _true_type		has_trivial_copy_constructor;
		typedef _true_type		has_trivial_assignment_operator;
		typedef _true_type		has_trivial_destructor;
		typedef _true_type		is_POD_type;
	};
	template<>
	struct _type_traits<wchar_t>{
		typedef _true_type		has_trivial_default_constructor;
		typedef _true_type		has_trivial_copy_constructor;
		typedef _true_type		has_trivial_assignment_operator;
		typedef _true_type		has_trivial_destructor;
		typedef _true_type		is_POD_type;
	};
	template<>
	struct _type_traits<short>{
		typedef _true_type		has_trivial_default_constructor;
		typedef _true_type		has_trivial_copy_constructor;
		typedef _true_type		has_trivial_assignment_operator;
		typedef _true_type		has_trivial_destructor;
		typedef _true_type		is_POD_type;
	};
	template<>
	struct _type_traits<unsigned short>{
		typedef _true_type		has_trivial_default_constructor;
		typedef _true_type		has_trivial_copy_constructor;
		typedef _true_type		has_trivial_assignment_operator;
		typedef _true_type		has_trivial_destructor;
		typedef _true_type		is_POD_type;
	};
	template<>
	struct _type_traits<int>{
		typedef _true_type		has_trivial_default_constructor;
		typedef _true_type		has_trivial_copy_constructor;
		typedef _true_type		has_trivial_assignment_operotor;
		typedef _true_type		has_trivial_destructor;
		typedef _true_type		is_POD_type;
	};
	template<>
	struct _type_traits<unsigned int>{
		typedef _true_type		has_trivial_default_constructor;
		typedef _true_type		has_trivial_copy_constructor;
		typedef _true_type		has_trivial_assignment_operotor;
		typedef _true_type		has_trivial_destructor;
		typedef _true_type		is_POD_type;
	};
	template<>
	struct _type_traits<long>{
		typedef _true_type		has_trivial_default_constructor;
		typedef _true_type		has_trivial_copy_constructor;
		typedef _true_type		has_trivial_assignment_operator;
		typedef _true_type		has_trivial_destructor;
		typedef _true_type		is_POD_type;
	};
	template<>
	struct _type_traits<unsigned long>{
		typedef _true_type		has_trivial_default_constructor;
		typedef _true_type		has_trivial_copy_constructor;
		typedef _true_type		has_trivial_assignment_operator;
		typedef _true_type		has_trivial_destructor;
		typedef _true_type		is_POD_type;
	};
	template<>
	struct _type_traits<long long>{
		typedef _true_type		has_trivial_default_constructor;
		typedef _true_type		has_trivial_copy_constructor;
		typedef _true_type		has_trivial_assignment_operator;
		typedef _true_type		has_trivial_destructor;
		typedef _true_type		is_POD_type;
	};
	template<>
	struct _type_traits<unsigned long long>{
		typedef _true_type		has_trivial_default_constructor;
		typedef _true_type		has_trivial_copy_constructor;
		typedef _true_type		has_trivial_assignment_operator;
		typedef _true_type		has_trivial_destructor;
		typedef _true_type		is_POD_type;
	};
	template<>
	struct _type_traits<float>{
		typedef _true_type		has_trivial_default_constructor;
		typedef _true_type		has_trivial_copy_constructor;
		typedef _true_type		has_trivial_assignment_operator;
		typedef _true_type		has_trivial_destructor;
		typedef _true_type		is_POD_type;
	};
	template<>
	struct _type_traits<double>{
		typedef _true_type		has_trivial_default_constructor;
		typedef _true_type		has_trivial_copy_constructor;
		typedef _true_type		has_trivial_assignment_operator;
		typedef _true_type		has_trivial_destructor;
		typedef _true_type		is_POD_type;
	};
	template<>
	struct _type_traits<long double>{
		typedef _true_type		has_trivial_default_constructor;
		typedef _true_type		has_trivial_copy_constructor;
		typedef _true_type		has_trivial_assignment_operator;
		typedef _true_type		has_trivial_destructor;
		typedef _true_type		is_POD_type;
	};

	//偏特化版本
	template<class T>
	struct _type_traits<T*>{
		typedef _true_type		has_trivial_default_constructor;
		typedef _true_type		has_trivial_copy_constructor;
		typedef _true_type		has_trivial_assignment_operator;
		typedef _true_type		has_trivial_destructor;
		typedef _true_type		is_POD_type;
	};
	template<class T>
	struct _type_traits<const T*>{
		typedef _true_type		has_trivial_default_constructor;
		typedef _true_type		has_trivial_copy_constructor;
		typedef _true_type		has_trivial_assignment_operator;
		typedef _true_type		has_trivial_destructor;
		typedef _true_type		is_POD_type;
	};

	//特化版本
	template<>
	struct _type_traits<char*>{
		typedef _true_type		has_trivial_default_constructor;
		typedef _true_type		has_trivial_copy_constructor;
		typedef _true_type		has_trivial_assignment_operator;
		typedef _true_type		has_trivial_destructor;
		typedef _true_type		is_POD_type;
	};
	template<>
	struct _type_traits<unsigned char*>{
		typedef _true_type		has_trivial_default_constructor;
		typedef _true_type		has_trivial_copy_constructor;
		typedef _true_type		has_trivial_assignment_operator;
		typedef _true_type		has_trivial_destructor;
		typedef _true_type		is_POD_type;
	};
	template<>
	struct _type_traits<signed char*>{
		typedef _true_type		has_trivial_default_constructor;
		typedef _true_type		has_trivial_copy_constructor;
		typedef _true_type		has_trivial_assignment_operator;
		typedef _true_type		has_trivial_destructor;
		typedef _true_type		is_POD_type;
	};
	template<>
	struct _type_traits<const char*>{
		typedef _true_type		has_trivial_default_constructor;
		typedef _true_type		has_trivial_copy_constructor;
		typedef _true_type		has_trivial_assignment_operator;
		typedef _true_type		has_trivial_destructor;
		typedef _true_type		is_POD_type;
	};
	template<>
	struct _type_traits<const unsigned char*>{
		typedef _true_type		has_trivial_default_constructor;
		typedef _true_type		has_trivial_copy_constructor;
		typedef _true_type		has_trivial_assignment_operator;
		typedef _true_type		has_trivial_destructor;
		typedef _true_type		is_POD_type;
	};
	template<>
	struct _type_traits<const signed char*>{
		typedef _true_type		has_trivial_default_constructor;
		typedef _true_type		has_trivial_copy_constructor;
		typedef _true_type		has_trivial_assignment_operator;
		typedef _true_type		has_trivial_destructor;
		typedef _true_type		is_POD_type;
	};

}

#endif