#define _CRT_SECURE_NO_WARNINGS 1
//#include "memoy_pool.hpp"
//#include "tree_node.hpp"
#include "concurrent_alloc.hpp"
#include "performance.hpp"

// test2: ���̲߳���TLS������ȡthread_cache�ٽ���Դ
void callback1() {
	for (int i = 5; i <= 10; ++i) {
		void* p = concurrent_alloc(i);
		//concurrent_dealloc(p, i);
	}
}

void callback2() {
	for (int i = 15; i <= 20; ++i) {
		void* p = concurrent_alloc(i);
		//concurrent_dealloc(p, i);
	}
}

void test3() {
	concurrent_alloc(6);
	concurrent_alloc(8);
	concurrent_alloc(1);
	concurrent_alloc(7);
	concurrent_alloc(8);
	concurrent_alloc(8);
}

void test4() {
	for (int i = 0; i < 1024; ++i) {
		std::cout << i + 1 << std::endl;
		void* p = concurrent_alloc(1);
	}
	void* p2 = concurrent_alloc(1);
	void* p3 = concurrent_alloc(1);
}

void test5() {
	std::vector<void*> v;
	for (int i = 1; i <= 10; ++i) {
		std::cout << i << std::endl;
		void* p = concurrent_alloc(i);
		v.push_back(p);
	}
	std::cout << "\n-------��ʼ�ͷ�--------\n" << std::endl;
	for (int i = 1; i <= 10; ++i) {
		concurrent_dealloc(v[i - 1]);
	}
	std::cout << "\n-------�ͷųɹ�--------\n" << std::endl;
}

void test6() {
	// ��������ֽ�����
	void* p = concurrent_alloc(257 * 1024);		// ������7kb����Ƭ
	concurrent_dealloc(p);
	std::cout << "\n-------------------\n" << std::endl;
	// �������ҳ����
	void* p2 = concurrent_alloc(129 * 1024 * 8);
	concurrent_dealloc(p2);
}

void test_performance() {
	// �����ڴ�����1000�β��� ��
	//std::cout << "----------------�����ڴ�����1000�β���----------------" << std::endl;
	//benchmark_concurrent(1000, 1000, 10);
	//benchmark_malloc(1000, 1000, 10);
	//std::cout << "----------------end----------------" << std::endl;

	// �����ڴ�����10000�β��� ��
	//std::cout << "----------------�����ڴ�����10000�β���----------------";
	//benchmark_concurrent(10000, 100, 8);
	//benchmark_malloc(10000, 100, 8);
	//std::cout << "----------------end----------------" << std::endl;

	// �����ڴ����MAX_BYTES�����㻺�弰���ڴ�PAGE_CACHEֱ��������Я��Ч���൱��
	//std::cout << "----------------���������MAX_BYTES----------------" << std::endl;
	//benchmark_concurrent(280 * 1024, 10, 3);
	//benchmark_malloc(280 * 1024, 10, 3);
	//std::cout << "----------------end----------------" << std::endl;

	// �����ڴ����MAX_PAGES�����㻺�弰���ڴ�system_allocֱ��������Я ��
	std::cout << "----------------���������MAX_PAGES----------------" << std::endl;
	benchmark_concurrent(1030 * 1024, 10, 2);
	benchmark_malloc(1030 * 1024, 10, 2);
	std::cout << "----------------end----------------" << std::endl;
}

int main() {
	//std::thread td1(callback1);
	//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	//td1.join();
	//std::cout << std::endl;
	//std::thread td2(callback2);
	//td2.join();
	// test5();
	test_performance();
	return 0;
}



// test1: �����ڴ�ز���
//int main() {
//	int times = 10, counts = 100000;
//	std::vector<TreeNode<int>*> v1;
//	v1.reserve(counts);
//	std::vector<TreeNode<int>*> v2;
//	v1.reserve(counts);
//
//	// malloc����
//	size_t begin1 = clock();
//	for (int i = 0; i < times; ++i) {
//		for (int i = 0; i < counts; ++i) {
//			v1.push_back(new TreeNode<int>);
//		}
//		for (int i = 0; i < times; ++i) {
//			delete v1[i];
//		}
//	}
//	size_t begin2 = clock();
//
//	// memorypool����
//	size_t begin3 = clock();
//	for (int i = 0; i < times; ++i) {
//		MemoryPool<TreeNode<int>> mp;
//		for (int i = 0; i < counts; ++i) {
//			v2.push_back(mp.acquire());
//		}
//		for (int i = 0; i < counts; ++i) {
//			mp.restore(v2[i]);
//		}
//		v2.clear();
//	}
//	size_t begin4 = clock();
//
//	cout << "malloc&delete: " << begin2 - begin1 << endl;
//	cout << "pool acquire&restore: " << begin4 - begin3 << endl;
//	return 0;
//}