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

// 三个哈希函数--三个映射位--可以减少误判率
template<size_t N, class K = string, class Hash1 = HashBKDR, class Hash2 = HashAP, class Hash3 = HashDJB>
class BloomFilter {
public:
	void set(const string& s) {
		b.set(Hash1()(s) % (ratio * N));
		b.set(Hash2()(s) % (ratio * N));
		b.set(Hash3()(s) % (ratio * N));
	}
	bool test(const string& s) {
		return b.test(Hash1()(s) % (ratio * N)) &&		// 只要某一个映射位不存在，则该数值不存在（准确）
			b.test(Hash2()(s) % (ratio * N)) &&			// 如果三个位映射都存在，则该数值也不一定真的存在（误判）
			b.test(Hash3()(s) % (ratio * N));
	}
private:
	const static size_t ratio = 5;		// 每存储一个值开辟5个位。最好不低于4.3，否则误判率增高
	bitset<ratio * N> b;
};