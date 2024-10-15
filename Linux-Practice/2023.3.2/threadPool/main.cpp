#include "threadPool.hpp"

int main() {
    srand((uint64_t)nullptr);
    //ThreadPool<Task>* tp = new ThreadPool<Task>();      // 创建线程池对象
    ThreadPool<Task>* tp = ThreadPool<Task>::getThreadPool();
    tp->run();      // 启动线程
    while(true) {
        // 生产者线程——制作任务
        int x = rand()%100+1;
        usleep(3000);
        int y = rand()%50;
        Task t(x, y, [](int x, int y)->int{return x + y;});     // lambda表达式的数据处理规则
        logMessage(DEBUG, "%s\n", "任务制作完成");      
        tp->taskPush(t);  // 生产者将任务生产完成后推入任务队列，等待消费者线程从任务队列获取并执行相关功能
        // sleep(1);
    }
    tp->end();      // 关闭线程，任务结束后析构并释放每个线程（包括互斥锁和条件变量）
    return 0;
}