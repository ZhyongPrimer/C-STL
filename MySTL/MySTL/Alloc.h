#ifndef _ALLOC_H_
#define _ALLOC_H_
#include<cstdlib>


namespace MySTL{


	//这里将第一第二级配置器合在一起
	//通过判断bytes大小选取哪一级

	//空间配置器，以字节为单位分配空间给内部使用
	class alloc{
	private:
		//使用枚举常量的好处：
		//1、在调试程序时通常可以类型检查枚举常量，尤其在不得不手工检查头文件中的常量值时。
		//2、用enum关键字说明的常量由编译程序自动生成，程不需要用手工对常量一一赋值

		enum EAlign{ ALIGN = 8 };//小型区块的上调边界
		enum EMaxBytes{ MAXBYTES = 128 };//小型区块的上限
		enum ENFreeLists{ NFREELIST = EMaxBytes::MAXBYTES / EAlign::ALIGN };//free-list个数
		enum ENObjs{ NOBJS = 20 };//默认每次增加节点数
	private:
		//使用联合体的作用：需要使用额外指针指向下一个节点，第一个字段可以表示指向下一个
		//节点的指针，第二个字段表示指向实际区块
		union obj{
			obj* next;
			char client[1];   //我们可以看到这个数据
		};

		//static 用处
		static obj* free_list[ENFreeLists::NFREELIST];

		//用于chunk的内存池参数
	private:
		static char* start_free;//内存池起始位置
		static char* end_free;//内存池结束位置
		static size_t heap_size;//
	//
	private:
		//将bytes上调至8的倍数
		static size_t ROUND_UP(size_t bytes){;
		return (((bytes)+EAlign::ALIGN-1)&~(EAlign::ALIGN- 1));
		}
		//根据区块大小，决定使用第n号free-list，n从0开始
		static size_t  FREELIST_INDEX(size_t bytes){
			return (((bytes)+EAlign::ALIGN - 1) / EAlign::ALIGN - 1);
		}
		//返回大小为n的对象，并可能加入大小为n的其他区块到freelist
		static void* refill(size_t n);

		//配置一大块空间，可容纳nobjs个大小为“size”的区块
		//如果配置nobjs个区块有所不便。nobjs可以降低
		static char* chunk_alloc(size_t size, size_t& nobjs);

	public:
		static void* allocate(size_t bytes);
		static void  deallocate(void* ptr, size_t bytes);
		static void* reallocate(void* ptr, size_t old_sz, size_t new_sz);

	};
}


#endif