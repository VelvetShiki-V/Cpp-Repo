//#include"func.h"
//
//template<class cont>
//void eraseFunc(cont& d) {
//	typename cont::iterator iter, tempIt;
//	for (iter = d.begin(); iter != d.end();)
//	{
//		cout << *iter << endl;
//		tempIt = iter;
//		//++iter;						// ����Ҫ������ͨ��erase����ֵ�����Ƶ���
//		iter = d.erase(tempIt);			// ����iter��ֵ����ȷָ����������һ����ַ
//		//d.erase(tempIt);
//	}
//}
//
//int main()
//{
//	//vector<int> v{ 1,2,3,4,5 };		// ʧЧ
//	//list<int> v{ 1,2,3,4,5 };			// ��ʧЧ
//	deque<int> v{ 1,2,3,4,5 };			// ʧЧ
//	eraseFunc(v);
//}

//#include<iostream>
//#include<vector>
//#include<algorithm>
//using namespace std;

//int main() {
//    int groups = 0;
//    int a, b, c;
//    cin >> groups;
//    vector<int> all;
//    int tmp = groups;
//    while (tmp) {
//        cin >> a >> b >> c;
//            all.push_back(a);
//            all.push_back(b);
//            all.push_back(c);
//            tmp--;
//    }
//    vector<vector<int>> p;
//    int i = 0;
//    p.resize(groups);
//    int flag = 1;
//    for (auto e : all) {
//        if (flag % 4 == 0) {
//            ++i;
//        } 
//        p[i].push_back(e);
//        ++flag;
//    }
//    for (auto& e : p) {
//        sort(e.begin(), e.end());
//    }
//    int sum = 0;
//    for (auto e : p) {
//        sum += e.operator[](1);
//    }
//    cout << sum;
//    return 0;
//}

#include"func.h"
//int main() {
//    int num, get;
//    cin >> num;
//    vector<int> arr;
//    while (num) {
//        cin >> get;
//        arr.push_back(get);
//        --num;
//    }
//    int cnt = 1, prev = arr[0];
//    vector<int>::iterator it = arr.begin();
//    for (it; it != arr.end();) {
//        if (*it == prev) {
//            ++it;
//            continue;
//        }
//        while (*it >= prev) {
//            prev = *it;
//            ++it;
//            if (it == arr.end()) break;
//            if (*it == prev) {
//                continue;
//            }
//            if (*it < prev) {
//                cnt++;
//                break;
//            }
//        }
//        if (it == arr.end()) break;
//        while (*it <= prev) {
//            prev = *it;
//            ++it;
//            if (it == arr.end()) break;
//            if (*it == prev) {
//                continue;
//            }
//            if (*it > prev) {
//                cnt++;
//                break;
//            }
//        }
//        if (it == arr.end()) break;
//    }
//    cout << cnt;
//    return 0;
//}


//int main() {
//	vector<string> v;
//	v.resize(100);
//	string s;
//	getline(cin, s);
//	size_t index = 0;
//	for (auto e : s) {
//		if (e == ' ') {
//			index++;
//			continue;
//		}
//		v[index].push_back(e);
//	}
//	v.resize(index + 1);
//	reverse(v.begin(), v.end());
//	for (auto e : v) {
//		cout << e << " ";
//	}
//}

// ţ���㷨������ת����
//int main()
//{
//	string s1, s2;
//	cin >> s2;
//	while (cin >> s1)
//		s2 = s1 + " " + s2;
//	cout << s2 << endl;
//	return 0;
//}

// ������ִ�
//int main() {
//	vector<int> v{ 1,2,3,2,2,2,5,4,2 };
//	MTH(v);
//	return 0;
//}