#ifndef __PERFORMANCE_HPP
#define __PERFORMANCE_HPP
#pragma once
#include "concurrent_alloc.hpp"
// #define FORMAT_PRESENT 1

void benchmark_concurrent(const size_t& counts, const size_t& rounds, const size_t& thread_nums) {
	std::atomic<time_t> alloc_spent = 0;
	std::atomic<time_t> dealloc_spent = 0;
	std::vector<std::thread> vThread(thread_nums);
	for (size_t t = 0; t < thread_nums; ++t) {				// 1. 外循环控制线程并发执行的个数
		vThread[t] = std::thread([&]() {
			std::vector<void*> p;
			p.reserve(counts);
			for (size_t i = 0; i < rounds; ++i) {			// 2. 中层循环控制每个线程需要申请和释放的轮次数
#ifdef FORMAT_PRESENT
				printf("第%d轮开始\n", i);
				std::cout << "\n----------开始申请，tid: ----------" << std::this_thread::get_id() << std::endl << std::endl;
#endif
				time_t alloc_begin = clock();
				for (size_t j = 0; j < counts; ++j) {		// 3. 内层循环控制申请的结点次数
					p.push_back(concurrent_alloc(i + 1));
				}
				time_t alloc_end = clock();
				time_t dealloc_begin = clock();
#ifdef FORMAT_PRESENT
				std::cout << "\n----------开始释放，tid: ----------" << std::this_thread::get_id() << std::endl;
#endif
				for (size_t k = 0; k < counts; ++k) {
					concurrent_dealloc(p[k]);
				}
				time_t dealloc_end = clock();
#ifdef FORMAT_PRESENT
				std::cout << "\n----------结束释放，tid: ----------" << std::this_thread::get_id() << std::endl;
#endif
				p.clear();
				alloc_spent += (alloc_end - alloc_begin);
				dealloc_spent += (dealloc_end - dealloc_begin);
#ifdef FORMAT_PRESENT
				std::cout << "该轮alloc cost: " << alloc_spent << "ms" << std::endl;
				std::cout << "该轮dealloc cost: " << dealloc_spent << "ms" << std::endl;
#endif
			}
		});
	}
	for (auto& e : vThread) {
		e.join();
	}
	std::cout << "\n---------------------------------------------------" << std::endl;
	printf("%d个线程进行的concurrent alloc总轮次: %d轮，共申请了%d次\n", thread_nums, rounds, rounds * counts);
	std::cout << "总alloc cost: " << alloc_spent << "ms" << std::endl;
	std::cout << "总dealloc cost: " << dealloc_spent << "ms" << std::endl;
	std::cout << "---------------------------------------------------" << std::endl;
}

void benchmark_malloc(const size_t& counts, const size_t& rounds, const size_t& thread_nums) {
	std::atomic<time_t> malloc_spent = 0;
	std::atomic<time_t> free_spent = 0;
	std::vector<std::thread> vThread(thread_nums);
	for (size_t t = 0; t < thread_nums; ++t) {				// 1. 外循环控制线程并发执行的个数
		vThread[t] = std::thread([&, t]() {
			std::vector<void*> p;
			p.reserve(counts);
			for (size_t i = 0; i < rounds; ++i) {			// 2. 中层循环控制每个线程需要申请和释放的轮次数
#ifdef FORMAT_PRESENT
				printf("第%d轮开始\n", i);
				std::cout << "\n----------开始申请，tid: ----------" << std::this_thread::get_id() << std::endl << std::endl;
#endif
				time_t malloc_begin = clock();
				for (size_t j = 0; j < counts; ++j) {		// 3. 内层循环控制申请的结点次数
					p.push_back(malloc(i + 1));
				}
				time_t malloc_end = clock();
				time_t free_begin = clock();
#ifdef FORMAT_PRESENT
				std::cout << "\n----------开始释放，tid: ----------" << std::this_thread::get_id() << std::endl;
#endif
				for (size_t k = 0; k < counts; ++k) {
					free(p[k]);
				}
				time_t free_end = clock();
#ifdef FORMAT_PRESENT
				std::cout << "\n----------结束释放，tid: ----------" << std::this_thread::get_id() << std::endl;
#endif
				p.clear();
				malloc_spent += (malloc_end - malloc_begin);
				free_spent += (free_end - free_begin);
#ifdef FORMAT_PRESENT
				std::cout << "该轮malloc cost: " << malloc_spent << "ms" << std::endl;
				std::cout << "该轮free cost: " << free_spent << "ms" << std::endl;
#endif
			}
		});
	}
	for (auto& e : vThread) {
		e.join();
	}
	std::cout << "\n---------------------------------------------------" << std::endl;
	printf("%d个线程进行的malloc总轮次: %d轮，共申请了%d次\n", thread_nums, rounds, rounds * counts);
	std::cout << "总malloc cost: " << malloc_spent << "ms" << std::endl;
	std::cout << "总free cost: " << free_spent << "ms" << std::endl;
	std::cout << "---------------------------------------------------" << std::endl;
}

#endif