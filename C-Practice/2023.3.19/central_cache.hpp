#ifndef __CENTRAL_CACHE_HPP
#define __CENTRAL_CACHE_HPP
#pragma once

#ifdef _WIN64
typedef unsigned long long PAGE_ID;
#elif _WIN32
typedef size_t PAGE_ID;
#endif	// _WIN64

struct Span {
	PAGE_ID pages = 0;
	size_t use_count = 0;
	void* freelist = nullptr;
	Span* next = nullptr;
	Span* prev = nullptr;
};

class SpanList {
public:
	SpanList() {
		head->next = head;
		head->prev = head;
	}
	void insert() {}
	void erase() {}
private:
	Span* head;
};
#endif