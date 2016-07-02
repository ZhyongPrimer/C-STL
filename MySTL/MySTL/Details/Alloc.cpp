#include"../Alloc.h"
namespace MySTL{
	//以下是static data member 的定义与初始设定
	char* alloc::start_free = 0;
	char* alloc::end_free = 0;
	size_t alloc::heap_size = 0;

	alloc::obj* alloc::free_list[alloc::ENFreeLists::NFREELIST] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};

	//static member function 的实现
	void* alloc::allocate(size_t bytes){
		if (bytes > EMaxBytes::MAXBYTES){
			return malloc(bytes);
		}
		//size_t index = FREELIST_INDEX(bytes);
		obj** my_free_list, *result;
		//obj* list = free_list[index];
		my_free_list = free_list + FREELIST_INDEX(bytes);
		result = *my_free_list;

		if (0 == result){//此时没有足够空间，需要从内存池中取空间
			return refill(ROUND_UP(bytes));
		}

		//此时result不为空，有空间分配给用户
		*my_free_list = result->next;
		return result;
	}
	void alloc::deallocate(void* ptr, size_t bytes){
		if (bytes > EMaxBytes::MAXBYTES){
			free(ptr);
		}
		else{//把释放的内存归还给free-list
			size_t index = FREELIST_INDEX(bytes);
			//强制转换为obj类型指针
			obj* node = static_cast<obj*>(ptr);
			node->next = free_list[index];
			free_list[index] = node;
		}
	}
	void* alloc::reallocate(void* ptr, size_t old_sz, size_t new_sz){
		deallocate(ptr, old_sz);
		ptr = allocate(new_sz);
		return ptr;
	}
	//返回一个大小为n的对象，并且有时候会为适当的free-list增加几点
	//假设bytes已经上调为8 的倍数
	void* alloc::refill(size_t bytes){
		size_t nobjs = ENFreeLists::NFREELIST;
		//调用chunkalloc（），尝试取得nobjs个区块作为新节点
		//参数是 passby reference  传地址
		char* chunk = chunk_alloc(bytes, nobjs);
		obj** my_free_list;
		obj*  result;
		obj*  current_obj, *next_obj;
		if (nobjs == 1){//只获得一个区块，给调用者
			return chunk;
		}
		// 调整free-list，加入新节点   my_free_list找到n号区块链表地址
		my_free_list = free_list + FREELIST_INDEX(bytes);
		//以下在chunk空间内建立free-list
		result = (obj*)chunk;//这个区块返回给client
		//头指针 指向第二个区块首地址
		*my_free_list = next_obj = (obj*)(chunk + bytes);
		//下面区块在free-list中，各节点连接
		for (int i = 1;; ++i){
			current_obj = next_obj;
			next_obj = (obj*)((char*)next_obj + bytes);
			if (nobjs - 1 == i){//链表尾节点
				current_obj->next = 0;
				break;
			}
			else
				current_obj->next = next_obj;
			
		}
		return result;
	}
	//bytes已经上调8的倍数
	char* alloc::chunk_alloc(size_t bytes, size_t& nobjs){
		char* result = 0;
		size_t total_bytes = bytes*nobjs;
		size_t bytes_left = end_free - start_free;//内存池剩余空间

		if (bytes_left >= total_bytes){
			result = start_free;
			start_free += total_bytes;
			return result;
		}
		//内存池满足1<=n<20 个区块
		else if (bytes_left >= bytes){
			nobjs = bytes_left / bytes;
			total_bytes = bytes*nobjs;
			result = start_free;
			start_free += total_bytes;
			return result;
		}
		//内存剩余空间不足一个区块
		else{
			//heap_size右移4位  附加量
			size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);
			if (bytes_left > 0){//合理运用剩余内存，将其加在合适free-list
				obj** my_free_list = free_list + FREELIST_INDEX(bytes_left);
				((obj*)start_free)->next = *my_free_list;
				*my_free_list = (obj*)start_free;
			}
			//配置heap空间，用来补充内存池
			start_free = (char*)malloc(bytes_to_get);
			if (0 == start_free){
				//heap空间不足，malloc失败
				obj** my_free_list = 0, *p = 0;
				//在比bytes大的区块，寻找free-list可用的，给heap
				for (int i = bytes; i <= EMaxBytes::MAXBYTES; i += EAlign::ALIGN){
					my_free_list = free_list + FREELIST_INDEX(i);
					p = *my_free_list;
					if (0 != p){//free-list还有未用区块
						*my_free_list = p->next;
						start_free = (char*)p;
						end_free = start_free + i;
						return chunk_alloc(bytes, nobjs);
					}
				}
				end_free = 0;//此时山穷水尽，到处都没有内存了,可以考虑第一级oom机制
			}
			heap_size += bytes_to_get;
			end_free = start_free + bytes_to_get;
			return chunk_alloc(bytes, nobjs);
		}
	}
}