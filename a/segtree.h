#pragma once

#include <vector>

using namespace std;

typedef int i32;
typedef long long int i64;

struct TCalcSegTree {
    using Type = i64;
    const Type Zero = 0;

    inline Type Combine(Type a, Type b) {
        return a + b;
    }

    i64 N = 0;
    vector<Type> St;

    TCalcSegTree() {}

    TCalcSegTree(i64 size) {
        Init(size);
    }

    void Init(i64 size) {
        N = 1;
        while (N < size) {
            N *= 2;
        }
        St.assign(N * 2, Zero);
    }

    void Set(i64 i, Type v, i64 x, i64 lx, i64 rx) {
        if (rx - lx == 1) {
            St[x] = v;
            return;
        }

        i64 m = (lx + rx) / 2;
        if (i < m) {
            Set(i, v, x * 2 + 1, lx, m);
        }
        else {
            Set(i, v, x * 2 + 2, m, rx);
        }

        St[x] = Combine(St[x * 2 + 1], St[x * 2 + 2]);
    }

    void Set(i64 i, Type v) {
        Set(i, v, 0, 0, N);
    }

    Type Calc(i64 l, i64 r, i64 x, i64 lx, i64 rx) {
        if (lx >= r || l >= rx) {
            return Zero;
        }

        if (l <= lx && rx <= r) {
            return St[x];
        }

        i64 m = (lx + rx) / 2;
        Type v1 = Calc(l, r, x * 2 + 1, lx, m);
        Type v2 = Calc(l, r, x * 2 + 2, m, rx);
        return Combine(v1, v2);
    }

    Type Calc(i64 l, i64 r) {
        return Calc(l, r, 0, 0, N);
    }
};


struct TModifySegTree {
    using Type = i64;
    const Type Zero = 0;

    inline Type Combine(Type a, Type b) {
        return a + b;
    }

    i64 N = 0;
    vector<Type> St;

    TModifySegTree() {}

    TModifySegTree(i64 size) {
        Init(size);
    }

    void Init(i64 size) {
        N = 1;
        while (N < size) {
            N *= 2;
        }
        St.assign(N * 2, Zero);
    }

    void Modify(i64 l, i64 r, Type v, i64 x, i64 lx, i64 rx) {
        if (r <= lx || rx <= l) {
            return;
        }

        if (l <= lx && rx <= r) {
            St[x] = Combine(St[x], v);
            return;
        }

        i64 mx = (lx + rx) / 2;
        Modify(l, r, v, 2 * x + 1, lx, mx);
        Modify(l, r, v, 2 * x + 2, mx, rx);
    }

    void Modify(i64 l, i64 r, Type v) {
        Modify(l, r, v, 0, 0, N);
    }

    Type Get(i64 i, i64 x, i64 lx, i64 rx) {
        if (rx - lx == 1) {
            return St[x];
        }

        i64 mx = (lx + rx) / 2;
        if (i < mx) {
            return Combine(Get(i, 2 * x + 1, lx, mx), St[x]);
        }
        else {
            return Combine(Get(i, 2 * x + 2, mx, rx), St[x]);
        }
    }

    Type Get(i64 i) {
        return Get(i, 0, 0, N);
    }
};