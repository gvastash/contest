#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <stdint.h>
#include <string.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include <vector>
#include <list>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <deque>
#include <string>

#include <algorithm>
#include <functional>
#include <bitset>
#include <functional>
#include <chrono>
#include <random>

#define sqr(x) (x) * (x)

typedef long long int i64;

using namespace std;
using namespace std::chrono;

const i64 mod = 1'000'000'000ll + 7;
//const i64 mod = 998'244'353ll;

const i64 inf = 1'000'000'000'000'000'000ll;

const long double eps = 1e-8;



int main(int argc, char* argv[]) {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); cout.precision(15); cout.setf(ios::fixed); cerr.precision(15); cerr.setf(ios::fixed);

    if (sizeof(i64) != sizeof(long long int)) {
        cerr << "i64 != long long int" << endl;
    }

    i64 T = 1;
    cin >> T;
    for (i64 tt = 1; tt <= T; tt++) {
        i64 n;
        cin >> n;

        vector<i64> a(n);
        for (i64 i = 0; i < n; i++) {
            cin >> a[i];
        }

        map<i64, vector<i64>, greater<i64>> q;
        for (i64 i = 0; i < n; i++) {
            q[a[i]].push_back(i);
        }

        TSparseTable st(a);

        if (q.begin()->second.size() > 2) {
            cout << "YES" << endl;
            i64 m = q.begin()->second[1];
            cout << m << " " << 1 << " " << n - m - 1 << endl;
            continue;
        }


        i64 l = q.begin()->second.front();
        i64 r = q.begin()->second.back() + 1;
        i64 vmin = st.Calc(l, r);

        auto it = q.begin();
        it++;

        bool f = false;
        while (it != q.end() && l > 0 && r < n) {
            auto v = it->first;
            auto& d = it->second;

            if (vmin == v) {
                if (d.front() < l && d.back() >= r) {
                    f = true;
                    cout << "YES" << endl;
                    cout << l << " " << r - l << " " << n - r << endl;
                    break;
                }
            } else if (vmin > v) {
                if (a[l - 1] > a[r]) {
                    l -= 1;
                    vmin = st.Calc(l, r);
                    continue;
                }
                else if (a[l - 1] < a[r]) {
                    r += 1;
                    vmin = st.Calc(l, r);
                    continue;
                }
                else if (q[a[r]].size() == 2) {
                    l -= 1;
                    r += 1;
                    vmin = st.Calc(l, r);
                    continue;
                }
                else {
                    if (q[a[r]].front() == l - 1) {
                        r += 1;
                    }
                    else {
                        l -= 1;
                    }
                    vmin = st.Calc(l, r);
                    continue;

                    /*
                    f = true;
                    cout << "YES" << endl;
                    if (q[a[r]].front() == l - 1) {
                        cout << l << " " << r - l + 1 << " " << n - r - 1 << endl;
                    }
                    else {
                        cout << l - 1 << " " << r - l + 1 << " " << n - r << endl;
                    }
                    break;
                    */
                }
            }

            l = min(l, d.front());
            r = max(r, d.back() + 1);
            vmin = st.Calc(l, r);
            it++;
        }

        if (!f) {
            cout << "NO" << endl;
        }
    }

    return 0;
}