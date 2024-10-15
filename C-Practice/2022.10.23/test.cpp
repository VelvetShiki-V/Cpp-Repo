#include "func.h"

//bool isPrime(int n) {
//    bool flag = true;
//    for (int i = 2; i <= sqrt(n); i++) {
//        if (n % i == 0) {
//            flag = false;
//            break;
//        }
//    }
//    return flag;
//}
//
//int main() {
//    int even, mid1, mid2;
//    while (cin >> even) {
//        mid1 = mid2 = even / 2;
//        for (mid1, mid2; mid1 != 1, mid2 != even; mid1--, mid2++) {
//            if (isPrime(mid1) && isPrime(mid2)) break;
//        }
//        cout << mid1 << endl << mid2 << endl;
//    }
//    return 0;
//}

//int main() {
//    string s;
//    getline(cin, s);
//    vector<string> vs;
//    vs.resize(1000);
//    int index = 0;
//    auto it = s.begin();
//    for (it; it != s.end(); ++it) {
//        if (*it == 34) {
//            while (1) {
//                ++it;
//                if (*it == 34) {
//                    //it = s.erase(it);
//                    ++it;
//                    break;
//                }
//                vs[index].push_back(*it);
//            }
//        }
//        if (*it == 32) {
//            index++;
//            continue;
//        }
//        if (it == s.end()) break;
//        vs[index].push_back(*it);
//    }
//    vs.resize(++index);
//    cout << vs.size() << endl;
//    for (auto v : vs) {
//        cout << v << endl;
//    }
//    return 0;
//}

int maxNum(int cur, int aim) {
    int submax, tmp = cur - 1;
    for (tmp; tmp != 1; --tmp) {
        if (cur % tmp == 0 && cur + tmp <= aim) {
            submax = tmp;
            break;
        }
    }
    if (tmp == 1) return -1;
    return submax;
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        int cnt = 0, tmp;
        while (n != m) {
            tmp = maxNum(n, m);
            if (tmp == -1) break;
            n += tmp;
            cnt++;
        }
        if (tmp == -1) cout << tmp << endl;
        cout << cnt << endl;
    }
    return 0;
}