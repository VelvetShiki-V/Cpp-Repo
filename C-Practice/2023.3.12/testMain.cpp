#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <atomic>
#include <condition_variable>

//void print(int n, int& cnt, std::mutex& mtx) {
//	mtx.lock();
//	for (int i = 0; i < n; ++i) {
//		std::cout << std::this_thread::get_id() << ": " << i << std::endl;
//		std::this_thread::sleep_for(std::chrono::milliseconds(100));
//		++cnt;
//	}
//	mtx.unlock();
//}
//template<class Lock>
//class lockGuard {
//public:
//	lockGuard(Lock& mtx)
//		:m_mtx(mtx)
//	{
//		m_mtx.lock();
//		std::cout << std::this_thread::get_id() << "已加锁" << std::endl;
//	}
//	~lockGuard() {
//		m_mtx.unlock();
//		std::cout << "已解锁" << std::endl;
//	}
//private:
//	Lock& m_mtx;
//};
//
//
//int main() {
//	int loop = 10, cap = 0;
//	//int cnt = 0;
//	std::atomic<int> cnt = 0;
//	std::cin >> cap;
//	std::mutex mtx;
//	//std::thread t1(print, loop, std::ref(cnt));
//	//std::thread t2(print, loop, std::ref(cnt));
//	//std::thread t1(print, loop, cnt, std::ref(mtx));
//	//std::thread t2(print, loop, cnt, std::ref(mtx));
//	//std::thread t1(print, loop, std::ref(cnt), std::ref(mtx));
//	//std::thread t2(print, loop, std::ref(cnt), std::ref(mtx));
//	std::vector<std::thread> v(cap);
//	//v.resize(cap);
//	for (int i = 0; i < cap; ++i) {
//		v[i] = std::thread([&]() {			// lambda表达式传引用所有参数
//			//mtx.lock();
//			lockGuard<std::mutex> lk(mtx);		// RAII智能锁（自定义类型）
//			//std::lock_guard<std::mutex> lk(mtx);	// 标准库提供的智能锁
//			for (int i = 0; i < loop; ++i) {
//				std::cout << std::this_thread::get_id() << ": " << i << std::endl;
//				std::this_thread::sleep_for(std::chrono::milliseconds(100));
//				++cnt;
//			}
//			//mtx.unlock();
//		});
//	};
//	for (auto& it : v) {
//		it.join();
//	}
//	std::cout << std::endl;
//	std::cout << "cnt累加值为: " << cnt << std::endl;
//	//t1.join();
//	//t2.join();
//	
//
//	return 0;
//}

// 两个线程交替打印（一奇一偶）
// 方法一：循环条件
//int main() {
//	int i = 0, j = 1, max = 100;
//	std::thread t1([&]() {
//		while (j <= max) {
//			std::cout << std::this_thread::get_id() << ": " << j << std::endl;
//			std::this_thread::sleep_for(std::chrono::milliseconds(100));
//			j += 2;
//		}
//		});
//	std::thread t2([&]() {
//		while (i <= max) {
//			std::cout << std::this_thread::get_id() << ": " << i << std::endl;
//			std::this_thread::sleep_for(std::chrono::milliseconds(100));
//			i += 2;
//		}
//		});
//	t1.join();
//	t2.join();
//	return 0;
//}

// 方法二：yield
//int main() {
//	int max = 100;
//	std::atomic<int> i = 0;		// 保证i是线程安全的，如果不用atomic则不安全
//	std::thread t1([&]() {
//		while (i < max) {
//			while (i % 2 == 0) std::this_thread::yield();		// 将任务让出，交错执行，本质是自旋锁
//			std::cout << std::this_thread::get_id() << ": " << i << std::endl;
//			std::this_thread::sleep_for(std::chrono::milliseconds(10));
//			i++;
//		}
//		});
//	std::thread t2([&]() {
//		while (i <= max) {
//			while(i % 2 != 0) std::this_thread::yield();
//			std::cout << std::this_thread::get_id() << ": " << i << std::endl;
//			std::this_thread::sleep_for(std::chrono::milliseconds(10));
//			i++;
//		}
//		});
//	t1.join();
//	t2.join();
//	return 0;
//}

// 方法三：条件变量（配合互斥锁）
int main() {
	int max = 100;
	std::atomic<int> i = 0;			// 保证i是线程安全的，如果不用atomic则不安全
	std::condition_variable cv;
	std::mutex mtx;
	bool ready = true;
	std::thread t1([&]() {
		while (i < max) {
			std::unique_lock<std::mutex> u_mtx(mtx);
			cv.wait(u_mtx, [&ready]() {return !ready;});		// 重要！！使线程交替执行的阻塞和唤醒条件
			std::cout << std::this_thread::get_id() << ": " << i << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			i++;
			ready = true;		// 使线程自己阻塞，唤醒另一线程交替执行
			cv.notify_one();
		}
	});

	std::thread t2([&]() {
		while (i <= max) {
			std::unique_lock<std::mutex> u_mtx(mtx);
			cv.wait(u_mtx, [&ready]() {return ready;});
			std::cout << std::this_thread::get_id() << ": " << i << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			i++;
			ready = false;
			cv.notify_one();
		}
	});
	t1.join();		// 回收线程
	t2.join();
	return 0;
}