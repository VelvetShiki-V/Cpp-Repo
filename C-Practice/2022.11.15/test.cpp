#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;

//class Greater {
//public:
//    bool operator()(string s1, string s2) {
//        if(s1.size() > s2.size()) return true;
//        else return false;
//    }
//};
//// abcdefghijklmnop abcsafjklmnopqrstuvw
//int main() {
//    string s1, s2, lng, sht;
//    vector<string> output;
//    cin >> s1 >> s2;
//    if (s1.size() > s1.size()) {
//        lng = s1; sht = s2;
//    }
//    else {
//        lng = s2; sht = s1;
//    }
//    output.resize(sht.size());
//    int j = 0, i = 0, index = 0;
//    for (i; i < sht.size(); i++) {
//        for (j = 0; j < lng.size(); j++) {
//            while (i < sht.size() && lng[j] == sht[i]) {
//                output[index].push_back(lng[j]);
//                i++; j++;
//                if (lng[j] != sht[i]) {
//                    index++;
//                    break;
//                }
//            }
//        }
//    }
//    output.resize(index);
//    sort(output.begin(), output.end(), Greater());
//    cout << output[0] << endl;
//    return 0;
//}

// MP3解析
//int main()
//{
//	int total_music;
//	string cmd;
//	while (cin >> total_music >> cmd)
//	{
//		int cursor = 1, top_of_page = 1;
//		if (total_music <= 4)
//		{
//			for (int i = 0; i < cmd.size(); ++i)
//			{
//				if (cursor == 1 && cmd[i] == 'U')		// 只有4首歌，1--up--4
//					cursor = total_music;
//				else if (cursor == total_music && cmd[i] == 'D')	// 4--down--1
//					cursor = 1;
//				else if (cmd[i] == 'U')		// 其他情况，正常上下
//					cursor--;
//				else
//					cursor++;
//			}
//			for (int i = 1; i <= total_music; ++i)		// 打印
//				cout << i << " ";
//			cout << endl;
//			cout << cursor << endl;
//		}
//		else
//		{
//			for (int i = 0; i < cmd.size(); ++i)
//			{
//
//				if (top_of_page == 1 && cursor == 1 && cmd[i] == 'U')		// 1--up--最底部
//				{
//					top_of_page = total_music - 3;
//					cursor = total_music;
//				}
//				else if (top_of_page == total_music - 3 && cursor == total_music && cmd[i] == 'D')		// 最底部--down--1
//				{
//					top_of_page = cursor = 1;
//				}
//				else if (top_of_page != 1 && cursor == top_of_page && cmd[i] == 'U')		// 非首尾页，光标位于其他页顶
//				{
//					top_of_page--;
//					cursor--;
//				}
//				else if (top_of_page != total_music - 3 && cursor == top_of_page + 3 && cmd[i] == 'D')		// 非首尾页，光标位于其他页底
//				{
//					top_of_page++;
//					cursor++;
//				}
//				else if (cmd[i] == 'U')		// 其他情况，正常上下
//					cursor--;
//				else
//					cursor++;
//			}
//			for (int i = top_of_page; i <= top_of_page + 3; ++i)
//				cout << i << " ";
//			cout << endl;
//			cout << cursor << endl;
//		}
//	}
//	return 0;
//}

// 动态规划
//string maxSub(string& s1, string& s2) {
//    vector<vector<int>> vv(s1.size(), vector<int>(s2.size(), 0));
//    int max = 0, pos = 0;
//    string tmp;
//    for (int i = 0; i < s1.size(); i++) {
//        for (int j = 0; j < s2.size(); j++) {
//            if (s1[i] == s2[j]) {
//                if (i >= 1 && j >= 1) {
//                    vv[i][j] = vv[i - 1][j - 1] + 1;
//                }
//                else {
//                    vv[i][j] = 1;
//                }
//                if (vv[i][j] > max) {
//                    max = vv[i][j];
//                    pos = i;
//                }
//            }
//        }
//    }
//    for (int i = pos - max + 1; i <= pos; ++i) {
//        tmp.push_back(s1[i]);
//    }
//    return tmp;
//}
//
//// abcdefghijklmnop abcsafjklmnopqrstuvw
//// werasdfaswer asdfas
//int main() {
//    string s1, s2, output;
//    cin >> s1 >> s2;
//    output = maxSub(s1, s2);
//    cout << output << endl;
//    return 0;
//}

#include<math.h>
// 最近公共祖先
//int getLCA(int a, int b) {
//	// write code here
//	if (a == 1 || b == 1) return 1;
//	int big, sml;
//	if (a > b) {
//		big = a; sml = b;
//	}
//	else {
//		big = b; sml = a;
//	}
//	while (big > sml) big /= 2;
//	if (big == sml) return sml;
//	int level = log(sml) / log(2);
//	level = pow(2, level);
//	if (big < level) sml /= 2;
//	while (big != 1 && big != sml) {
//		big /= 2; sml /= 2;
//	}
//	return big;
//}

//int main() {
//    //int ret = getLCA(5,8);
//    int ret = getLCA(9,8);
//    //int ret = getLCA(57530,209947);
//    cout << ret << endl;
//    return 0;
//}

int binInsert(int n, int m, int j, int i) {
    // write code here
    m <<= j;
    int ret = (n | m);
    return ret;
}
int main() {
    int ret = binInsert(1024, 19, 6, 2);
    cout << ret << endl;
    return 0;
}