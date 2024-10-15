#ifndef __COMMON_HPP
#define __COMMON_HPP
#pragma once
#include <iostream>
#include <string>
#include <cassert>
#include "log.hpp"
#define MAX_BUCKETS 208
#define MAX_BYTES 128 * 1024

void*& next_node(void* node) {
	return *(void**)node;
}

// ���������࣬����ÿ����ϣͰ�ڵ��ڴ����
class FreeList {
public:
	// 1. �ڴ澭ʹ����Ϻ󻹸�thread_cache��ͷ�����ӵ���ӦͰ�ڵ���������ͷ��
	void push(void* obj){
		assert(obj);
		next_node(obj) = m_freelist;
		m_freelist = obj;
		logMessage(DEBUG, "��ǰ��������ͷ����ַΪ: %p", m_freelist);
	}

	// 2. Ͱ���ж�Ӧ���������ڴ���飬�����ڴ���鵯�����û�
	void* pop() {
		m_freelist = next_node(m_freelist);
		assert(m_freelist);
		logMessage(DEBUG, "��ǰ��������ͷ����ַΪ: %p", m_freelist);
		return m_freelist;
	}

	// 3. �ж�ĳ��Ͱ�ڵĽ���ڴ���Ƿ�Ϊ�գ������޷����룬��Ҫ����central_cache����
	bool empty() {
		return m_freelist == nullptr;
	}
private:
	void* m_freelist = nullptr;			// ��ʼ���б�ÿ��Ͱ���Ϊ��ָ��
};

class Alignment {
public:
	// 1. ���ݴ�������뿪�ٿռ��ʵ�ʴ�С������������Ӧ����Ĵ�С
	static size_t round(const size_t& size, const size_t& alignNum) {
		assert(size <= MAX_BYTES);
		if (size % alignNum == 0) return size;		// �������Ĵ�С����������÷����С�ڶ�Ӧ������
		else {
			return (size / alignNum + 1) * alignNum;		// ������Ҫ���룬�����������Ҫ������ڴ�δ�С����
		}
	}
	static size_t space_round_up(const size_t& size) {
		if (size <= 128) {
			return round(size, 8);
		}
		else if (size <= 128 * 8) {
			return round(size, 16);
		}
		else if (size <= 1024) {
			return round(size, 128);
		}
		else if (size <= 1024 * 8) {
			return round(size, 1024);
		}
		else if (size <= 1024 * 64) {
			return round(size, 1024 * 8);
		}
		else assert(false);
		return -1;
	}

	// 2. ��������������ڴ�鴦���ĸ��ڴ�Ͱ��
	static size_t locate(const size_t& size, const size_t& assignNum) {
		if (size % assignNum == 0) return size / assignNum - 1;
		else {
			return size / assignNum;
		}
	}
	static size_t bucket_locate(const size_t& size) {
		assert(size <= MAX_BYTES);
		// static int buckets[] = { 16, 56, 56, 56 };
		if (size <= 128) {
			return locate(size, 8);
		}
		else if (size <= 128 * 8) {
			return locate(size, 16);
		}
		else if (size <= 1024) {
			return locate(size, 128);
		}
		else if (size <= 1024 * 8) {
			return locate(size, 1024);
		}
		else if (size <= 1024 * 64) {
			return locate(size, 1024 * 8);
		}
		else assert(false);
		return -1;
	}
};

#endif