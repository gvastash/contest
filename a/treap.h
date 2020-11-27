#pragma once

#include <vector>
#include <chrono>
#include <random>

using namespace std;

typedef int i32;
typedef long long int i64;

struct TRandom {
    using Type = i64;
    mt19937 Rng;
    uniform_int_distribution<Type> Dist;

    TRandom() : Rng((chrono::steady_clock::now().time_since_epoch().count())), Dist(0ll, std::numeric_limits<Type>::max()) {
    }

    Type GetRandomNumber() {
        return Dist(Rng);
    }
};


struct TTreap {
    using Type = i64;
    const Type Zero = 0;

    Type Data = Zero;
    vector<TTreap*> Kids = { nullptr, nullptr };
    i64 Priority = 0;
    i64 Size = 1;

    static TRandom Rnd;

    explicit TTreap(i64 val) : Data(val), Priority(Rnd.GetRandomNumber()) {
        Recalc();
    }

    void Recalc() {
        Size = 1;
        for (auto kid : Kids) {
            if (!kid) {
                continue;
            }
            Size += kid->Size;
        }
    }

    vector<TTreap*> Split(i64 splitSize) {
        if (splitSize == 0) {
            return{ nullptr, this };
        }
        if (splitSize == Size) {
            return{ this, nullptr };
        }

        i64 leftSize = Kids[0] ? Kids[0]->Size : 0;
        if (leftSize >= splitSize) {
            auto leftRes = Kids[0]->Split(splitSize);
            Kids[0] = leftRes[1];
            Recalc();
            return{ leftRes[0], this };
        }
        else {
            splitSize -= leftSize + 1;
            auto rightRes = Kids[1]->Split(splitSize);
            Kids[1] = rightRes[0];
            Recalc();
            return{ this, rightRes[1] };
        }
        throw 1;
    }

    static TTreap* Merge(TTreap* l, TTreap* r) {
        if (!l) {
            return r;
        }
        if (!r) {
            return l;
        }
        if (l->Priority < r->Priority) {
            l->Kids[1] = Merge(l->Kids[1], r);
            l->Recalc();
            return l;
        }
        else {
            r->Kids[0] = Merge(l, r->Kids[0]);
            r->Recalc();
            return r;
        }
    }
};

TRandom TTreap::Rnd;

void Cut(TTreap*& treap, vector<TTreap*>& q, i64 size) {
    vector<TTreap*> t = { nullptr, nullptr };
    if (treap) {
        t = treap->Split(size);
    }
    q.push_back(t[1]);
    treap = t[0];
}

TTreap* Merge(vector<TTreap*>& q) {
    TTreap* res = nullptr;
    for (auto t : q) {
        res = TTreap::Merge(res, t);
    }
    return res;
}

i64 NthElement(TTreap*& treap, i64 x) {
    vector<TTreap*> q;
    Cut(treap, q, x);
    Cut(treap, q, x - 1);
    q.push_back(treap);

    i64 res = q[1]->Data;

    swap(q[0], q[1]);
    swap(q[2], q[0]);
    q.resize(2);

    treap = Merge(q);

    return res;
}

void Dfs(TTreap* treap, vector<i64>& res) {
    if (!treap) {
        return;
    }
    Dfs(treap->Kids[0], res);
    res.push_back(treap->Data);
    Dfs(treap->Kids[1], res);
}

vector<i64> ft;

vector<i64> Construct(i64 x, i64 n) {
    vector<i64> res(n + 1);

    x %= ft[n];

    TTreap* treap = nullptr;
    for (i64 i = 1; i <= n; i++) {
        treap = TTreap::Merge(treap, new TTreap(i));
    }

    for (i64 i = 1; i <= n; i++) {
        i64 j = x / ft[n - i];
        x %= ft[n - i];

        res[i] = NthElement(treap, j + 1);
    }
}