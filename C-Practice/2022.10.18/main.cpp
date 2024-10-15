#include"func.h"
//template<class cont>
//void eraseFunc(cont& d) {
//	typename cont::iterator iter, tempIt;
//	for (iter = d.begin(); iter != d.end();)
//	{
//		cout << *iter << endl;
//		tempIt = iter;
//		//++iter;						// 不需要自增，通过erase返回值来控制迭代
//		iter = d.erase(tempIt);			// 更新iter的值以正确指向连续的下一个地址
//		//d.erase(tempIt);
//	}
//}
//
//int main()
//{
//	//vector<int> v{ 1,2,3,4,5 };		// 失效
//	//list<int> v{ 1,2,3,4,5 };			// 不失效
//	deque<int> v{ 1,2,3,4,5 };			// 失效
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

// 牛逼算法——反转单词
//int main()
//{
//	string s1, s2;
//	cin >> s2;
//	while (cin >> s1)
//		s2 = s1 + " " + s2;
//	cout << s2 << endl;
//	return 0;
//}

// 最大数字串
//int main() {
//	vector<int> v{ 1,2,3,2,2,2,5,4,2 };
//	MTH(v);
//	return 0;
//}

//int main() {
//	int arr[] = { 1,2,3,4,0,5,6,7,8,9 };
//	int n = sizeof(arr) / sizeof(int);
//	vector<int> v(arr, arr + n);
//	vector<int>::iterator it = v.begin();
//	while (it != v.end())
//	{
//		if (*it != 0)
//			cout << *it;
//		else {
//			v.erase(it);
//			//it = v.erase(it);
//			//continue;
//		}
//		it++;
//	}
//	return 0;
//}

//int main() {
//	//char buf[128];
//	string s;
//	getline(cin, s);
//	if (' ' == '\0') {
//		cout << s;
//	}
//	else {
//		cout << "not equal";
//	}
//	//printf("%s", buf);
//}

// 进制计算
//int main() {
//	int input, trans;
//	bool flag = false;
//	while (cin >> input >> trans) {
//		if (input == 0) {
//			cout << 0;
//			continue;
//		}
//		if (input < 0) {
//			input = -input;
//			flag = true;
//		}
//		if (trans <= 9) {
//			vector<int> v; v.clear();
//			while (input) {
//				v.push_back(input % trans); input /= trans;
//			}
//			reverse(v.begin(), v.end());
//			if(flag) cout << '-';
//			for (auto e : v) {
//				cout << e;
//			}
//		}
//		else {
//			string s; s.clear();
//			while (input) {
//				static char sign[] = { 'A', 'B', 'C', 'D', 'E', 'F' };
//				int tmp = input % trans;
//				if (tmp > 9) {
//					s.push_back(sign[tmp % 10]);
//				}
//				else {
//					tmp += 48;
//					s.push_back(tmp);
//				}
//				input /= trans;
//			}
//			if (flag) cout << '-';
//			reverse(s.begin(), s.end()); for (auto e : s) {
//				cout << e;
//			}
//		}
//	}
//	return 0;
//}

// 二维数组
//int main() {
//	int dim[3][3] = { {1,2,3},{4,5,6},{7,8,9} };
//
//	cout << dim[0][1] << endl;		// 2
//	cout << dim[1][2] << endl;		// 6
//	cout << dim[2][0] << endl;		// 7
//	cout << dim[2][2] << endl;		// 9
//
//	cout << *(*(dim + 1) + 1)  << endl;		// 5
//
//	return 0;
//}

// 回文串——90%通过
//bool is_palindrome(string s) {
//    string t = s;
//    reverse(s.begin(), s.end());
//    if (t == s) return true;
//    else return false;
//}
//
//int main() {
//    string A, B;
//    A.resize(100);
//    B.resize(100);
//    while (cin >> A >> B) {
//        int cnt = 0;
//        string::iterator it = A.begin();
//        for (it; it != A.end();++it) {
//            A.insert(it, B.begin(), B.end());
//            if (is_palindrome(A)) ++cnt;
//            it = A.erase(it, it + B.size());
//        }
//        A.append(B);
//        if (is_palindrome(A)) ++cnt;
//        cout << cnt << endl;
//    }
//    return 0;
//}

// 欧几里得盒子
//int main() {
//    int W, H;
//    while (cin >> W >> H) {         // W是列号，H是行号，都从0开始
//        vector<vector<int>> vv;
//        vv.resize(H);               // 将（二维）行数调整为H
//        for (int i = 0; i < H; i++) {
//            vv[i].resize(W, 0);     // 将（一维）列数调整为W
//        }
//        int cnt = 0;
//        for (int i = 0; i < H; i++) {       // 不能等于，因为题目说明行编号和列编号分别为为W-1, H-1，即比实际输入行数和列数少1
//            for (int j = 0; j < W; j++) {
//                if (vv[i][j] != 1) cnt++;   // 合法欧几里得位置，可以放蛋糕，计数器自增
//                else continue;
//                if (j + 2 < W) {            // 判断是否越界
//                    vv[i][j + 2] = 1;
//                }
//                if (i + 2 < H) {
//                    vv[i + 2][j] = 1;
//                }
//            }
//        }
//        cout << cnt << endl;
//    }
//}

// 字符串转整型
//int main() {
//    string s("+123");
//    cout << StrToInt(s) << endl;
//    return 0;
//}

// 水平值最大
//int main() {
//    int num;
//    cin >> num;
//    num *= 3;
//    vector<int> v;
//    int get;
//    while (num) {
//        cin >> get;
//        v.push_back(get);
//        num--;
//    }
//    sort(v.begin(), v.end());
//    vector<int>::iterator it = v.begin();
//    vector<int>::iterator rit = v.end();
//    int max = 0;
//    while (it != rit) {
//        rit -= 2;
//        max += *(rit);
//        it++;
//    }
//    cout << max << endl;
//}

// 非递增递减序列统计
//int main() {
//    int num, get;
//    while (cin >> num) {
//        int cnt = 0;
//        vector<int> v;
//        v.resize(num + 1);
//        v[num] = 0;
//        for (int i = 0; i < num; i++) {
//            cin >> get;
//            v[i] = get;
//        }
//        vector<int>::iterator it = v.begin();
//        while (it != v.end() - 1) {
//            if (*(it + 1) > *it) {
//                while (it != v.end() - 1 && *(it + 1) >= *it) ++it;
//                cnt++;
//                if (it == v.end() - 1) break;
//            }
//            else if (*(it + 1) == *it) {
//                ++it;
//                if (it == v.end() - 1) break;
//            }
//            else {
//                while (it != v.end() - 1 && *(it + 1) <= *it) ++it;
//                cnt++;
//                if (it == v.end() - 1) break;
//            }
//            ++it;
//        }
//        cout << cnt << endl;
//    }
//    return 0;
//}

// 斐波那契移步数
//int main() {
//    int N, f0 = 0, f1 = 1, cur = 0;
//    while (cin >> N) {
//        while (N >= cur) {
//            cur = f0 + f1;
//            f0 = f1;
//            f1 = cur;
//        }
//        int steps = (cur - N) < (N - f0) ? (cur - N) : (N - f0);
//        cout << steps << endl;
//    }
//    return 0;
//}

// 合法括号序列判断
//int main() {
//	Parenthesis p1;
//	string a = "())";
//	cout << p1.chkParenthesis(a, 3);
//}

// 字典序，长度排序的字符串数组判断
bool lex(vector<string>& v) {
    bool flag = true;
    for (int i = 0; i < v.size(); ++i) {
        if (i + 1 < v.size()) {
            int sz = v[i].size() < v[i + 1].size() ? v[i].size() : v[i + 1].size();
            for (int j = 0; j < sz; j++) {
                if (v[i][j] > v[i + 1][j]) {
                    flag = false;
                    break;
                }
            }
            if (flag == false) break;
        }
    }
    return flag;
}
bool lengths(vector<string>& v) {
    bool flag = true;
    auto it = v.begin();
    for (it; it != v.end(); ++it) {
        if (it + 1 < v.end()) {
            if ((it + 1)->size() < it->size())
                flag = false;
        }
    }
    return flag;
}
int main() {
    int num;
    string tmp;
    while (cin >> num) {
        vector<string> v(num);
        for (auto& e : v) {
            cin >> tmp;
            e = tmp;
        }
        bool lx = lex(v), lt = lengths(v);
        if (lx && lt) cout << "both" << endl;
        else if (lx) cout << "lexicographically" << endl;
        else if (lt) cout << "lengths" << endl;
        else cout << "none" << endl;
    }
    return 0;
}

// 求两数的最小公倍数——辗转相除法
//int main() {
//    int A, B;
//    while (cin >> A >> B) {
//        int multi = A * B, rem = A % B;
//        while (rem) {
//            A = B;
//            B = rem;
//            rem = A % B;
//        }
//        cout << multi / B << endl;
//    }
//    return 0;
//}