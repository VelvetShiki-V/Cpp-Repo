//#include "memoy_pool.hpp"
//#include "tree_node.hpp"
#include "thread_cache.hpp"
#include "concurrent_alloc.hpp"
#include <cstdlib>

// test2: 多线程并发TLS无锁获取thread_cache临界资源
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

int main() {
	std::thread td1(callback1);
	//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	td1.join();
	std::cout << std::endl;
	std::thread td2(callback2);
	td2.join();
	return 0;
}



// test1: 定长内存池测试
//int main() {
//	int times = 10, counts = 100000;
//	std::vector<TreeNode<int>*> v1;
//	v1.reserve(counts);
//	std::vector<TreeNode<int>*> v2;
//	v1.reserve(counts);
//
//	// malloc方案
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
//	// memorypool方案
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