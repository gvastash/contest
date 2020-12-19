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

//const i64 mod = 1'000'000'000ll + 7;
//const i64 mod = 998'244'353ll;

const i64 inf = 1'000'000'000'000'000'000ll;

const long double eps = 1e-8;

i64 gcd(i64 a, i64 b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

i64 phi(i64 n) {
    i64 result = n;
    for (i64 i = 2; i * i <= n; ++i)
        if (n % i == 0) {
            while (n % i == 0) {
                n /= i;
            }
            result -= result / i;
        }
    if (n > 1) {
        result -= result / n;
    }
    return result;
}

i64 rem(i64 a, i64 b, i64 m) {
    i64 g = gcd(a, m);

    if (b % g) {
        return -1;
    }

    a /= g;
    b /= g;
    m /= g;

    i64 x = binpow(a, phi(m) - 1, m);
    x *= b;
    x %= m;
    return x;
}

i64 binpow(i64 a, i64 n, i64 m) {
    i64 res = 1;
    while (n) {
        if (n & 1) {
            res *= a;
            res %= m;
        }
        a *= a;
        a %= m;
        n >>= 1;
    }
    return res % m;
}


int main(int argc, char* argv[]) {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); cout.precision(15); cout.setf(ios::fixed); cerr.precision(15); cerr.setf(ios::fixed);

    if (sizeof(i64) != sizeof(long long int)) {
        cerr << "i64 != long long int" << endl;
    }

    i64 T;
    cin >> T;
    for (i64 tt = 1; tt <= T; tt++) {
        i64 n, s, k;
        cin >> n >> s >> k;

        i64 b = n - s;

        i64 x = rem(k, b, n);

        cout << x << endl;
    }

    return 0;
}