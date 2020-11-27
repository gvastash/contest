#pragma once

#include <algorithm>

using namespace std;

typedef long long int i64;

i64 gcd(i64 a, i64 b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

i64 gcdex(i64 a, i64 b, i64 & x, i64 & y) {
    if (a == 0) {
        x = 0; y = 1;
        return b;
    }
    i64 x1, y1;
    i64 d = gcdex(b%a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

i64 rev(i64 a, i64 m) {
    i64 x, y;
    i64 g = gcdex(a, m, x, y);
    return x = (x % m + m) % m;
}

i64 gcdex(i64 a, i64 b, i64 & x, i64 & y) {
    if (a == 0) {
        x = 0; y = 1;
        return b;
    }
    i64 x1, y1;
    i64 d = gcdex(b%a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

i64 rev(i64 a, i64 m) {
    i64 x, y;
    i64 g = gcdex(a, m, x, y);
    return x = (x % m + m) % m;
}




i64 cnk(i64 n, i64 k) {
    i64 fn = 0;
    i64 fk = 0;
    i64 fnk = 0;

    i64 f = 1;
    for (i64 i = 1; i <= n; i++) {
        f *= i;
        f %= mod;
        if (i == n) {
            fn = f;
        }
        if (i == k) {
            fk = f;
        }
        if (i == n - k) {
            fnk = f;
        }
    }

    i64 R = fn;
    R %= mod;
    R *= rev(fk, mod);
    R %= mod;
    R *= rev(fnk, mod);
    R %= mod;
    return R;
}

i64 binpow(i64 a, i64 n) {
    i64 res = 1;
    while (n) {
        if (n & 1) {
            res *= a;
            res %= mod;
        }
        a *= a;
        a %= mod;
        n >>= 1;
    }
    return res % mod;
}