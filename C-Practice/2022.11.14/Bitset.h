#pragma once
#include<iostream>
#include<vector>
#include<string>
using namespace std;

namespace mybitset {
	template<size_t N>
	class bitset {
	public:
		bitset() {
			size_t num = N / 8 + 1;
			m_bitset.resize(num, 0);
		}
		void set(size_t n) {
			size_t i = n / 8;
			size_t j = n % 8;
			m_bitset[i] |= (1 << j);
		}
		void reset(size_t n) {
			size_t i = n / 8;
			size_t j = n % 8;
			m_bitset[i] &= ~(1 << j);
		}
		bool test(size_t n) {
			size_t i = n / 8;
			size_t j = n % 8;
			return m_bitset[i] & (1 << j);
		}
	private:
		vector<unsigned char> m_bitset;
	};

	template<size_t N>
	class twobitset {
	public:
		void set(size_t n) {
			if (!b1.test(n) && !b2.test(n)) {		// û���ֹ�->һ��
				b2.set(n);
			}
			else if (!b1.test(n) && b2.test(n)) {		// ��һ��->���
				b1.set(n);
				b2.reset(n);
			}
		}
		void testOnce() {
			for (size_t i = 0; i < N; ++i) {
				if (b2.test(i)) {
					cout << i << " ";
				}
			}
		}
	private:
		bitset<N> b1;
		bitset<N> b2;
	};
}