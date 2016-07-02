#include"../Alloc.h"
namespace MySTL{
	//������static data member �Ķ������ʼ�趨
	char* alloc::start_free = 0;
	char* alloc::end_free = 0;
	size_t alloc::heap_size = 0;

	alloc::obj* alloc::free_list[alloc::ENFreeLists::NFREELIST] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};

	//static member function ��ʵ��
	void* alloc::allocate(size_t bytes){
		if (bytes > EMaxBytes::MAXBYTES){
			return malloc(bytes);
		}
		//size_t index = FREELIST_INDEX(bytes);
		obj** my_free_list, *result;
		//obj* list = free_list[index];
		my_free_list = free_list + FREELIST_INDEX(bytes);
		result = *my_free_list;

		if (0 == result){//��ʱû���㹻�ռ䣬��Ҫ���ڴ����ȡ�ռ�
			return refill(ROUND_UP(bytes));
		}

		//��ʱresult��Ϊ�գ��пռ������û�
		*my_free_list = result->next;
		return result;
	}
	void alloc::deallocate(void* ptr, size_t bytes){
		if (bytes > EMaxBytes::MAXBYTES){
			free(ptr);
		}
		else{//���ͷŵ��ڴ�黹��free-list
			size_t index = FREELIST_INDEX(bytes);
			//ǿ��ת��Ϊobj����ָ��
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
	//����һ����СΪn�Ķ��󣬲�����ʱ���Ϊ�ʵ���free-list���Ӽ���
	//����bytes�Ѿ��ϵ�Ϊ8 �ı���
	void* alloc::refill(size_t bytes){
		size_t nobjs = ENFreeLists::NFREELIST;
		//����chunkalloc����������ȡ��nobjs��������Ϊ�½ڵ�
		//������ passby reference  ����ַ
		char* chunk = chunk_alloc(bytes, nobjs);
		obj** my_free_list;
		obj*  result;
		obj*  current_obj, *next_obj;
		if (nobjs == 1){//ֻ���һ�����飬��������
			return chunk;
		}
		// ����free-list�������½ڵ�   my_free_list�ҵ�n�����������ַ
		my_free_list = free_list + FREELIST_INDEX(bytes);
		//������chunk�ռ��ڽ���free-list
		result = (obj*)chunk;//������鷵�ظ�client
		//ͷָ�� ָ��ڶ��������׵�ַ
		*my_free_list = next_obj = (obj*)(chunk + bytes);
		//����������free-list�У����ڵ�����
		for (int i = 1;; ++i){
			current_obj = next_obj;
			next_obj = (obj*)((char*)next_obj + bytes);
			if (nobjs - 1 == i){//����β�ڵ�
				current_obj->next = 0;
				break;
			}
			else
				current_obj->next = next_obj;
			
		}
		return result;
	}
	//bytes�Ѿ��ϵ�8�ı���
	char* alloc::chunk_alloc(size_t bytes, size_t& nobjs){
		char* result = 0;
		size_t total_bytes = bytes*nobjs;
		size_t bytes_left = end_free - start_free;//�ڴ��ʣ��ռ�

		if (bytes_left >= total_bytes){
			result = start_free;
			start_free += total_bytes;
			return result;
		}
		//�ڴ������1<=n<20 ������
		else if (bytes_left >= bytes){
			nobjs = bytes_left / bytes;
			total_bytes = bytes*nobjs;
			result = start_free;
			start_free += total_bytes;
			return result;
		}
		//�ڴ�ʣ��ռ䲻��һ������
		else{
			//heap_size����4λ  ������
			size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);
			if (bytes_left > 0){//��������ʣ���ڴ棬������ں���free-list
				obj** my_free_list = free_list + FREELIST_INDEX(bytes_left);
				((obj*)start_free)->next = *my_free_list;
				*my_free_list = (obj*)start_free;
			}
			//����heap�ռ䣬���������ڴ��
			start_free = (char*)malloc(bytes_to_get);
			if (0 == start_free){
				//heap�ռ䲻�㣬mallocʧ��
				obj** my_free_list = 0, *p = 0;
				//�ڱ�bytes������飬Ѱ��free-list���õģ���heap
				for (int i = bytes; i <= EMaxBytes::MAXBYTES; i += EAlign::ALIGN){
					my_free_list = free_list + FREELIST_INDEX(i);
					p = *my_free_list;
					if (0 != p){//free-list����δ������
						*my_free_list = p->next;
						start_free = (char*)p;
						end_free = start_free + i;
						return chunk_alloc(bytes, nobjs);
					}
				}
				end_free = 0;//��ʱɽ��ˮ����������û���ڴ���,���Կ��ǵ�һ��oom����
			}
			heap_size += bytes_to_get;
			end_free = start_free + bytes_to_get;
			return chunk_alloc(bytes, nobjs);
		}
	}
}