#include"func.h"
using namespace std;

void test1()
{
	vector<int> v1;			//��˳���
	vector<int> v2(1);		//����10�����Ϳռ䲢��ʼ��capacity������Ԫ��Ϊ0��sizeͬʱ�仯
	vector<int> v3(10);		
	vector<int> v4(10, 3);	//����10�����Ϳռ䲢��ʼ��capacity������Ԫ��Ϊ3��sizeͬʱ�仯
	vector<int> v5(v4);		//��������

	//β������
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	//����1
	cout << "������������������������test1������������������������" << endl;
	for (size_t i = 0; i < v1.size(); i++)
	{
		cout << ++v1[i] << " ";		//vector��[]����ֵΪ�±�ֵ�����ã�reference operator[] (size_type n);
	}
	cout << endl;
	//����2����������
	cout << "������������������������test2������������������������" << endl;
	vector<int>::iterator it = v1.begin();		//����������vector<int>::const_iterator it
	for (it; it != v1.end(); it++)
	{
		cout << ++(*it)  << " ";
	}
	cout << endl;
	//����3�������������
	cout << "������������������������test3������������������������" << endl;
	vector<int>::reverse_iterator rit = v1.rbegin();	//��дΪauto rit
	for (rit; rit != v1.rend(); rit++)
	{
		cout << ++(*rit) << " ";
	}
	cout << endl;
	//����4����Χfor��
	cout << "������������������������test4������������������������" << endl;
	for (auto e : v1)
	{
		cout << ++e << " ";
	}
	cout << endl;
	//maxsize
	cout << v1.max_size() << endl;		//42�ڳ���4�����޷���-1���Ե���Ԫ�ش�С��
	//vs���ݣ�����һ��capacity��1.5����
	cout << "������������������������test5������������������������" << endl;
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
	//find�㷨��insert����
	cout << "������������������������test6������������������������" << endl;
	vector<int>::iterator pos = find(v1.begin(), v1.end(), 7);
	if (pos != v1.end())		//��Ҫ���λ���Ƿ�Ϸ������findʧ�ܣ���Ĭ�Ϸ���end���൱��β��
	{
		v1.insert(pos, 30);
	}
	for (auto e : v1)
	{
		cout << e << " ";
	}
	//erase����
	cout << "������������������������test7������������������������" << endl;
	auto pos1 = find(v1.begin(), v1.end(), 30);
	if (pos1 != v1.end())		//��Ҫ���λ���Ƿ�Ϸ������findʧ�ܣ���Ĭ�Ϸ���end
	{
		v1.erase(pos1);			//�������λ�ò��Ϸ�(����endʱ��Խ��)���ᱨ�����Ա���if���λ�úϷ���
	}
	for (auto e : v1)
	{
		cout << e << " ";
	}
}

void test2()
{
	//vector����
	cout << "������������������������test1������������������������" << endl;
	vector<int>v1;
	v1.push_back(1);
	v1.push_back(10);
	v1.push_back(5);
	v1.push_back(9);
	v1.push_back(3);
	v1.push_back(0);
	sort(v1.begin(), v1.end());		//Ĭ���㷨������α����less��������Ϊ������������sort��������vector��list��string������
	for (auto e : v1)
	{
		cout << e << " ";
	}
	cout << endl;
	//less<int> ls;		//С����ǰ������
	greater<int> gt;	//�����ǰ������
	sort(v1.begin(), v1.end(), gt);		//�Ž���ʹ��α����greater���˴�������Ҳ���Դ���������greater<int>()
	for (auto e : v1)					
	{
		cout << e << " ";
	}
	cout << endl;
	cout << "������������������������test2������������������������" << endl;
	string s1("edubf8367954gfy8ergf");
	sort(s1.begin(), s1.end(), less<char>());		//string�������򣬰���ascii����
	cout << s1 << endl;
	sort(s1.begin(), s1.end(), greater<char>());
	cout << s1 << endl;								//���ͱ��
	//vector<char>��string������ǰ��û��\0������+=��find�ȷ��治������߿���׷���ַ��������Ӵ���vector<char>�޷����string
	cout << "������������������������test3������������������������" << endl;
	vector<string>v2;
	v2.push_back("123");		//��ʽ����ת������char*�ַ���ת��Ϊstring����Ĭ�Ϲ���
	v2.push_back("456");
	v2.push_back("abc");
	for (const auto& l : v2)	//�����������&���������������ֵ����Χfor����lʱ����Ϊ������string�����Ե��ÿ�������
	{							//������ˣ�����string�ı������õ�����vector�е�string��Ա���Ҳ��ܱ��޸ģ�����const
		cout << l << " ";
	}
}

void test3()
{
	using namespace mysp;
	cout << "������������������������test1β�塪����������������������" << endl;
	myvector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	//v1.push_back(5);
	//for (auto e : v1)			//�ɵ������滻����
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
	//βɾ
	cout << "������������������������test2βɾ������������������������" << endl;
	v1.pop_back();
	v1.pop_back();
	cout << v1.capacity() << " " << v1.size() << endl;
	for (it = v1.begin(); it != v1.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
	cout << "������������������������test3���롪����������������������" << endl;
	//v1.insert(v1.begin(), 10);		//ʹ��insertͷ�壬����begin�Ǵ�ֵ���أ��м�������г���const���޷���insert�����޸�
	//cout << v1.capacity() << " " << v1.size() << endl;
	//for (it = v1.begin(); it != v1.end(); it++)
	//{
	//	cout << *it << " ";
	//}
	//cout << endl;
	myvector<int>::iterator pos = find(v1.begin(), v1.end(), *(v1.begin()));		//ǰ������Ϳ���auto���
	if (pos != v1.end())									//beginģ��ͷ��
	{
		v1.insert(pos, 10);									//posָ��λ�ò��䣬10���Ų��
		//v1.insert(pos, 101);								//��Ҫ�������ʣ����������ʧЧ��posΪҰָ��
		//v1.insert(pos, 102);
		//v1.insert(pos, 103);
		//v1.insert(pos, 104);
	}
	for (it = v1.begin(); it != v1.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
	pos = find(v1.begin(), v1.end(), *(v1.end() - 1));		//ǰ������Ϳ���auto���
	if (pos != v1.end())									//endģ��ĩԪ�ص�ǰһ��λ�ò���
	{
		v1.insert(pos, 99);									//posָ��λ�ò��䣬10���Ų��
	}
	for (it = v1.begin(); it != v1.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
	cout << v1.capacity() << " " << v1.size() << endl;
	cout << "������������������������test4����������������������������" << endl;
	auto p = find(v1.begin(), v1.end(), 2);		//ģ��βɾ���Լ�ʵ�ֵ�erase֧��ͬһ��λ������erase����Ϊ�ռ�û�仯������
	v1.erase(p);								//������������������ݲ��ԣ�����ò�Ҫ��ͬһ��λ������erase
	for (it = v1.begin(); it != v1.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
	cout << v1.capacity() << " " << v1.size() << endl;
	v1.erase(v1.begin());							//ģ��ͷɾ
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
	//������������������������test1����ɾ������������������������������������������������
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
	//for (it; it != v1.end(); it++)		//����for�����������it������������ȷ����Ϊ�������պ��ߵ�end()����itָ��λ�õ���һ��λ�ò�Ϊż�����������������ȷ���
	//{
	//	if (*it % 2 == 0)
	//	{
	//		it = v1.erase(it);				//��ȷ�ĸ���it��ʽ
	//	}
	//}
	//for (auto e : v1)
	//{
	//	cout << e << " ";
	//}
	//cout << endl;
	//cout << v1.size() << " " << v1.capacity() << endl;

	//������������������������test2�����������������������������������������������������
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
	//while (it != v1.end())			//������for����Ϊforÿ��ѭ����ʹ����������
	//{
	//	if ((*it) % 2 == 0)
	//	{
	//		it = v1.erase(it);		//��ȷ�ĸ��µ�������ʽ
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

	//������������������������test3������󡪡�������������������������������������������
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
	while (it != v1.end())			//������for����Ϊforÿ��ѭ����ʹ����������
	{
		if ((*it) % 2 == 0)
		{
			it = v1.erase(it);		//��ȷ�ĸ��µ�������ʽ
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