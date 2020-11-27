#pragma once

#include <algorithm>
#include <vector>

using namespace std;

typedef long long int i64;

struct TDsu {
    vector<i64> Dsu;
    vector<vector<i64>> Elem;

    TDsu(int size) {
        Init(size);
    }

    void Init(i64 size) {
        Dsu.resize(size);
        Elem.resize(size);

        for (i64 i = 0; i < size; i++) {
            Dsu[i] = i;
            Elem[i].push_back(i);
        }
    }

    i64 FindSet(i64 v) {
        if (v == Dsu[v]) {
            return v;
        }
        return Dsu[v] = FindSet(Dsu[v]);
    }

    void UnionSets(i64 a, i64 b) {
        a = FindSet(a);
        b = FindSet(b);
        if (a != b) {
            if (Elem[a].size() < Elem[b].size()) {
                swap(a, b);
            }
            Dsu[b] = a;
            for (auto t : Elem[b]) {
                Elem[a].push_back(t);
            }
        }
    }
};