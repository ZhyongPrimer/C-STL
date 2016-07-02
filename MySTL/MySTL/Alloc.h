#ifndef _ALLOC_H_
#define _ALLOC_H_
#include<cstdlib>


namespace MySTL{


	//���ｫ��һ�ڶ�������������һ��
	//ͨ���ж�bytes��Сѡȡ��һ��

	//�ռ������������ֽ�Ϊ��λ����ռ���ڲ�ʹ��
	class alloc{
	private:
		//ʹ��ö�ٳ����ĺô���
		//1���ڵ��Գ���ʱͨ���������ͼ��ö�ٳ����������ڲ��ò��ֹ����ͷ�ļ��еĳ���ֵʱ��
		//2����enum�ؼ���˵���ĳ����ɱ�������Զ����ɣ��̲���Ҫ���ֹ��Գ���һһ��ֵ

		enum EAlign{ ALIGN = 8 };//С��������ϵ��߽�
		enum EMaxBytes{ MAXBYTES = 128 };//С�����������
		enum ENFreeLists{ NFREELIST = EMaxBytes::MAXBYTES / EAlign::ALIGN };//free-list����
		enum ENObjs{ NOBJS = 20 };//Ĭ��ÿ�����ӽڵ���
	private:
		//ʹ������������ã���Ҫʹ�ö���ָ��ָ����һ���ڵ㣬��һ���ֶο��Ա�ʾָ����һ��
		//�ڵ��ָ�룬�ڶ����ֶα�ʾָ��ʵ������
		union obj{
			obj* next;
			char client[1];   //���ǿ��Կ����������
		};

		//static �ô�
		static obj* free_list[ENFreeLists::NFREELIST];

		//����chunk���ڴ�ز���
	private:
		static char* start_free;//�ڴ����ʼλ��
		static char* end_free;//�ڴ�ؽ���λ��
		static size_t heap_size;//
	//
	private:
		//��bytes�ϵ���8�ı���
		static size_t ROUND_UP(size_t bytes){;
		return (((bytes)+EAlign::ALIGN-1)&~(EAlign::ALIGN- 1));
		}
		//���������С������ʹ�õ�n��free-list��n��0��ʼ
		static size_t  FREELIST_INDEX(size_t bytes){
			return (((bytes)+EAlign::ALIGN - 1) / EAlign::ALIGN - 1);
		}
		//���ش�СΪn�Ķ��󣬲����ܼ����СΪn���������鵽freelist
		static void* refill(size_t n);

		//����һ���ռ䣬������nobjs����СΪ��size��������
		//�������nobjs�������������㡣nobjs���Խ���
		static char* chunk_alloc(size_t size, size_t& nobjs);

	public:
		static void* allocate(size_t bytes);
		static void  deallocate(void* ptr, size_t bytes);
		static void* reallocate(void* ptr, size_t old_sz, size_t new_sz);

	};
}


#endif