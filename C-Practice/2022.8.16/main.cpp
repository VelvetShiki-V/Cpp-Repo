#include"func.h"
using namespace std;

void test1()
{
	vector<int> v1;			//空顺序表
	vector<int> v2(1);		//开辟10个整型空间并初始化capacity中所有元素为0，size同时变化
	vector<int> v3(10);		
	vector<int> v4(10, 3);	//开辟10个整型空间并初始化capacity中所有元素为3，size同时变化
	vector<int> v5(v4);		//拷贝构造

	//尾插数据
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	//遍历1
	cout << "————————————test1————————————" << endl;
	for (size_t i = 0; i < v1.size(); i++)
	{
		cout << ++v1[i] << " ";		//vector的[]返回值为下标值的引用：reference operator[] (size_type n);
	}
	cout << endl;
	//遍历2（迭代器）
	cout << "————————————test2————————————" << endl;
	vector<int>::iterator it = v1.begin();		//常量迭代器vector<int>::const_iterator it
	for (it; it != v1.end(); it++)
	{
		cout << ++(*it)  << " ";
	}
	cout << endl;
	//遍历3（反向迭代器）
	cout << "————————————test3————————————" << endl;
	vector<int>::reverse_iterator rit = v1.rbegin();	//或写为auto rit
	for (rit; rit != v1.rend(); rit++)
	{
		cout << ++(*rit) << " ";
	}
	cout << endl;
	//遍历4（范围for）
	cout << "————————————test4————————————" << endl;
	for (auto e : v1)
	{
		cout << ++e << " ";
	}
	cout << endl;
	//maxsize
	cout << v1.max_size() << endl;		//42亿除以4（即无符号-1除以单个元素大小）
	//vs扩容：按上一次capacity的1.5倍扩
	cout << "————————————test5————————————" << endl;
	v1.reserve(100);
	cout << v1.capacity() << endl;
	v1.resize(150, 5);
	for (auto e : v1)
	{
		cout << e << " ";
	}
	cout << endl;
	cout << v1.size() << endl;
	cout << v1.capacity() << endl;
	v1.resize(50);
	for (auto e : v1)
	{
		cout << e << " ";
	}
	cout << endl;
	cout << v1.size() << endl;
	cout << v1.capacity() << endl;
	//find算法和insert操作
	cout << "————————————test6————————————" << endl;
	vector<int>::iterator pos = find(v1.begin(), v1.end(), 7);
	if (pos != v1.end())		//需要检查位置是否合法，如果find失败，则默认返回end，相当于尾插
	{
		v1.insert(pos, 30);
	}
	for (auto e : v1)
	{
		cout << e << " ";
	}
	//erase操作
	cout << "————————————test7————————————" << endl;
	auto pos1 = find(v1.begin(), v1.end(), 30);
	if (pos1 != v1.end())		//需要检查位置是否合法，如果find失败，则默认返回end
	{
		v1.erase(pos1);			//如果擦除位置不合法(比如end时的越界)，会报错，所以必须if检查位置合法性
	}
	for (auto e : v1)
	{
		cout << e << " ";
	}
}

void test2()
{
	//vector排序
	cout << "————————————test1————————————" << endl;
	vector<int>v1;
	v1.push_back(1);
	v1.push_back(10);
	v1.push_back(5);
	v1.push_back(9);
	v1.push_back(3);
	v1.push_back(0);
	sort(v1.begin(), v1.end());		//默认算法排升序（伪函数less），参数为迭代器变量，sort不仅能排vector，list，string都能排
	for (auto e : v1)
	{
		cout << e << " ";
	}
	cout << endl;
	//less<int> ls;		//小的在前，升序
	greater<int> gt;	//大的在前，降序
	sort(v1.begin(), v1.end(), gt);		//排降序，使用伪函数greater，此处传对象；也可以传匿名对象greater<int>()
	for (auto e : v1)					
	{
		cout << e << " ";
	}
	cout << endl;
	cout << "————————————test2————————————" << endl;
	string s1("edubf8367954gfy8ergf");
	sort(s1.begin(), s1.end(), less<char>());		//string类型排序，按照ascii排序
	cout << s1 << endl;
	sort(s1.begin(), s1.end(), greater<char>());
	cout << s1 << endl;								//泛型编程
	//vector<char>和string的区别，前者没有\0，且在+=，find等方面不能像后者可以追加字符串或找子串，vector<char>无法替代string
	cout << "————————————test3————————————" << endl;
	vector<string>v2;
	v2.push_back("123");		//隐式类型转换，将char*字符串转换为string，再默认构造
	v2.push_back("456");
	v2.push_back("abc");
	for (const auto& l : v2)	//如果不加引用&，则迭代器变量赋值给范围for变量l时，因为类型是string，所以调用拷贝构造
	{							//如果加了，就是string的别名，拿到的是vector中的string成员，且不能被修改，加上const
		cout << l << " ";
	}
}

void test3()
{
	using namespace mysp;
	cout << "————————————test1尾插————————————" << endl;
	myvector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	//v1.push_back(5);
	//for (auto e : v1)			//由迭代器替换而来
	//{
	//	cout << e << " ";
	//}
	myvector<int>::iterator it = v1.begin();
	for (it; it != v1.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
	cout << v1.capacity() << " " << v1.size() << endl;
	v1.reserve(10);
	cout << v1.capacity() << " " << v1.size() << endl;
	//尾删
	cout << "————————————test2尾删————————————" << endl;
	v1.pop_back();
	v1.pop_back();
	cout << v1.capacity() << " " << v1.size() << endl;
	for (it = v1.begin(); it != v1.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
	cout << "————————————test3插入————————————" << endl;
	//v1.insert(v1.begin(), 10);		//使用insert头插，但是begin是传值返回，中间变量具有常性const，无法被insert引用修改
	//cout << v1.capacity() << " " << v1.size() << endl;
	//for (it = v1.begin(); it != v1.end(); it++)
	//{
	//	cout << *it << " ";
	//}
	//cout << endl;
	myvector<int>::iterator pos = find(v1.begin(), v1.end(), *(v1.begin()));		//前面的类型可由auto替代
	if (pos != v1.end())									//begin模拟头插
	{
		v1.insert(pos, 10);									//pos指向位置不变，10向后挪走
		//v1.insert(pos, 101);								//不要连续访问，否则迭代器失效，pos为野指针
		//v1.insert(pos, 102);
		//v1.insert(pos, 103);
		//v1.insert(pos, 104);
	}
	for (it = v1.begin(); it != v1.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
	pos = find(v1.begin(), v1.end(), *(v1.end() - 1));		//前面的类型可由auto替代
	if (pos != v1.end())									//end模拟末元素的前一个位置插入
	{
		v1.insert(pos, 99);									//pos指向位置不变，10向后挪走
	}
	for (it = v1.begin(); it != v1.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
	cout << v1.capacity() << " " << v1.size() << endl;
	cout << "————————————test4擦除————————————" << endl;
	auto p = find(v1.begin(), v1.end(), 2);		//模拟尾删，自己实现的erase支持同一个位置连续erase，因为空间没变化，但是
	v1.erase(p);								//如果编译器采用了缩容策略，则最好不要对同一个位置连续erase
	for (it = v1.begin(); it != v1.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
	cout << v1.capacity() << " " << v1.size() << endl;
	v1.erase(v1.begin());							//模拟头删
	for (it = v1.begin(); it != v1.end(); it++)		
	{
		cout << *it << " ";
	}
	cout << endl;
	cout << v1.capacity() << " " << v1.size() << endl;
}

void test4()
{
	using namespace mysp;
	myvector<int> v1;
	//————————————test1正常删除———————————————————————
	//v1.push_back(1);
	//v1.push_back(2);
	//v1.push_back(3);
	//v1.push_back(4);
	//v1.push_back(5);
	//for (auto e : v1)
	//{
	//	cout << e << " ";
	//}
	//cout << endl;
	//cout << v1.size() << " " << v1.capacity() << endl;
	//myvector<int>::iterator it = v1.begin();
	//for (it; it != v1.end(); it++)		//用了for，如果不更新it，且输出结果正确，因为迭代器刚好走到end()，且it指向位置的下一个位置不为偶数，所以碰巧输出正确结果
	//{
	//	if (*it % 2 == 0)
	//	{
	//		it = v1.erase(it);				//正确的更新it方式
	//	}
	//}
	//for (auto e : v1)
	//{
	//	cout << e << " ";
	//}
	//cout << endl;
	//cout << v1.size() << " " << v1.capacity() << endl;

	//————————————test2程序崩溃———————————————————————
	//v1.push_back(1);
	//v1.push_back(2);
	//v1.push_back(3);
	//v1.push_back(4);

	//for (auto e : v1)
	//{
	//	cout << e << " ";
	//}
	//cout << endl;
	//cout << v1.size() << " " << v1.capacity() << endl;
	//myvector<int>::iterator it = v1.begin();
	//while (it != v1.end())			//不能用for，因为for每次循环会使迭代器自增
	//{
	//	if ((*it) % 2 == 0)
	//	{
	//		it = v1.erase(it);		//正确的更新迭代器方式
	//	}
	//	else
	//	{
	//		++it;
	//	}
	//}
	//for (auto e : v1)
	//{
	//	cout << e << " ";
	//}
	//cout << endl;
	//cout << v1.size() << " " << v1.capacity() << endl;

	//————————————test3结果错误———————————————————————
	v1.push_back(4);
	v1.push_back(4);
	v1.push_back(4);
	v1.push_back(4);
	for (auto e : v1)
	{
		cout << e << " ";
	}
	cout << endl;
	cout << v1.size() << " " << v1.capacity() << endl;
	myvector<int>::iterator it = v1.begin();
	while (it != v1.end())			//不能用for，因为for每次循环会使迭代器自增
	{
		if ((*it) % 2 == 0)
		{
			it = v1.erase(it);		//正确的更新迭代器方式
		}
		else
		{
			++it;
		}
	}
	for (auto e : v1)
	{
		cout << e << " ";
	}
	cout << endl;
	cout << v1.size() << " " << v1.capacity() << endl;
}

int main()
{
	//test1();
	//test2();
	//test3();
	test4();
	return 0;
}