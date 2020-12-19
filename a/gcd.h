#pragma once

#include <algorithm>
#include <vector>

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

i64 cnk(i64 n, i64 k, i64 m) {
    if (n < k) {
        return 0;
    }

    i64 fn = 0;
    i64 fk = 0;
    i64 fnk = 0;

    i64 f = 1;
    for (i64 i = 1; i <= n; i++) {
        f *= i;
        f %= m;
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
    R %= m;
    R *= rev(fk, m);
    R %= m;
    R *= rev(fnk, m);
    R %= m;
    return R;
}

i64 cnk(i64 n, i64 k, vector<i64>& f, i64 m) {
    if (n < k) {
        return 0;
    }

    i64 fn = f[n];
    i64 fk = f[k];
    i64 fnk = f[n - k];

    i64 R = fn;
    R %= m;
    R *= rev(fk, m);
    R %= m;
    R *= rev(fnk, m);
    R %= m;
    return R;
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