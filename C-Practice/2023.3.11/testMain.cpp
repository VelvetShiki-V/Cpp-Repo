#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

//void print(int n, int& cnt, std::mutex& mtx) {
//	mtx.lock();
//	for (int i = 0; i < n; ++i) {
//		std::cout << std::this_thread::get_id() << ": " << i << std::endl;
//		std::this_thread::sleep_for(std::chrono::milliseconds(100));
//		++cnt;
//	}
//	mtx.unlock();
//}


int main() {
	int loop = 10, cnt = 0, cap = 0;
	std::cin >> cap;
	std::mutex mtx;
	//std::thread t1(print, loop, std::ref(cnt));
	//std::thread t2(print, loop, std::ref(cnt));
	//std::thread t1(print, loop, cnt, std::ref(mtx));
	//std::thread t2(print, loop, cnt, std::ref(mtx));
	//std::thread t1(print, loop, std::ref(cnt), std::ref(mtx));
	//std::thread t2(print, loop, std::ref(cnt), std::ref(mtx));
	std::vector<std::thread> v;
	v.resize(cap);
	for (int i = 0; i < cap; ++i) {
		v[i] = std::thread([&]() {			// lambda表达式传引用所有参数
			mtx.lock();
			for (int i = 0; i < loop; ++i) {
				std::cout << std::this_thread::get_id() << ": " << i << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				++cnt;
			}
			mtx.unlock();
		});
	};
	for (auto& it : v) {
		it.join();
	}
	std::cout << std::endl;
	std::cout << "cnt累加值为: " << cnt << std::endl;
	//t1.join();
	//t2.join();
	

	return 0;
}