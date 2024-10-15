#include "memoy_pool.hpp"
#include "tree_node.hpp"

int main() {
	int times = 10, counts = 100000;
	std::vector<TreeNode<int>*> v1;
	v1.reserve(counts);
	std::vector<TreeNode<int>*> v2;
	v1.reserve(counts);

	// malloc方案
	size_t begin1 = clock();
	for (int i = 0; i < times; ++i) {
		for (int i = 0; i < counts; ++i) {
			v1.push_back(new TreeNode<int>);
		}
		for (int i = 0; i < times; ++i) {
			delete v1[i];
		}
	}
	size_t begin2 = clock();

	// memorypool方案
	size_t begin3 = clock();
	for (int i = 0; i < times; ++i) {
		MemoryPool<TreeNode<int>> mp;
		for (int i = 0; i < counts; ++i) {
			v2.push_back(mp.acquire());
		}
		for (int i = 0; i < counts; ++i) {
			mp.restore(v2[i]);
		}
		v2.clear();
	}
	size_t begin4 = clock();

	cout << "malloc&delete: " << begin2 - begin1 << endl;
	cout << "pool acquire&restore: " << begin4 - begin3 << endl;
	return 0;
}