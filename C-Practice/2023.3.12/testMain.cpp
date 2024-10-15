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
//		std::cout << std::this_thread::get_id() << "�Ѽ���" << std::endl;
//	}
//	~lockGuard() {
//		m_mtx.unlock();
//		std::cout << "�ѽ���" << std::endl;
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
//		v[i] = std::thread([&]() {			// lambda���ʽ���������в���
//			//mtx.lock();
//			lockGuard<std::mutex> lk(mtx);		// RAII���������Զ������ͣ�
//			//std::lock_guard<std::mutex> lk(mtx);	// ��׼���ṩ��������
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
//	std::cout << "cnt�ۼ�ֵΪ: " << cnt << std::endl;
//	//t1.join();
//	//t2.join();
//	
//
//	return 0;
//}

// �����߳̽����ӡ��һ��һż��
// ����һ��ѭ������
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

// ��������yield
//int main() {
//	int max = 100;
//	std::atomic<int> i = 0;		// ��֤i���̰߳�ȫ�ģ��������atomic�򲻰�ȫ
//	std::thread t1([&]() {
//		while (i < max) {
//			while (i % 2 == 0) std::this_thread::yield();		// �������ó�������ִ�У�������������
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

// ��������������������ϻ�������
int main() {
	int max = 100;
	std::atomic<int> i = 0;			// ��֤i���̰߳�ȫ�ģ��������atomic�򲻰�ȫ
	std::condition_variable cv;
	std::mutex mtx;
	bool ready = true;
	std::thread t1([&]() {
		while (i < max) {
			std::unique_lock<std::mutex> u_mtx(mtx);
			cv.wait(u_mtx, [&ready]() {return !ready;});		// ��Ҫ����ʹ�߳̽���ִ�е������ͻ�������
			std::cout << std::this_thread::get_id() << ": " << i << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			i++;
			ready = true;		// ʹ�߳��Լ�������������һ�߳̽���ִ��
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
	t1.join();		// �����߳�
	t2.join();
	return 0;
}