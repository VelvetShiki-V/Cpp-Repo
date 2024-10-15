#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<bitset>
using namespace std;

struct HashBKDR {
	size_t operator()(const string& s) {
		size_t val = 0;
		for (auto ch : s)
		{
			val *= 131;
			val += ch;
		}
		return val;
	}
};

struct HashAP {
	size_t operator()(const string& s) {
		size_t hash = 0;
		for (size_t i = 0; i < s.size(); i++)
		{
			if ((i & 1) == 0)
			{
				hash ^= ((hash << 7) ^ s[i] ^ (hash >> 3));
			}
			else
			{
				hash ^= (~((hash << 11) ^ s[i] ^ (hash >> 5)));
			}
		}
		return hash;
	}
};

struct HashDJB {
	size_t operator()(const string& s) {
		size_t hash = 5381;
		for (auto ch : s)
		{
			hash += (hash << 5) + ch;
		}

		return hash;
	}
};

// ������ϣ����--����ӳ��λ--���Լ���������
template<size_t N, class K = string, class Hash1 = HashBKDR, class Hash2 = HashAP, class Hash3 = HashDJB>
class BloomFilter {
public:
	void set(const string& s) {
		b.set(Hash1()(s) % (ratio * N));
		b.set(Hash2()(s) % (ratio * N));
		b.set(Hash3()(s) % (ratio * N));
	}
	bool test(const string& s) {
		return b.test(Hash1()(s) % (ratio * N)) &&		// ֻҪĳһ��ӳ��λ�����ڣ������ֵ�����ڣ�׼ȷ��
			b.test(Hash2()(s) % (ratio * N)) &&			// �������λӳ�䶼���ڣ������ֵҲ��һ����Ĵ��ڣ����У�
			b.test(Hash3()(s) % (ratio * N));
	}
private:
	const static size_t ratio = 5;		// ÿ�洢һ��ֵ����5��λ����ò�����4.3����������������
	bitset<ratio * N> b;
};