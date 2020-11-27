#pragma once

#include <algorithm>

using namespace std;

typedef long long int i64;

struct less_key {
    bool operator() (const pair<i64, i64>& p1, const pair<i64, i64>& p2)  const {
        return p1.first > p2.first || (p1.first == p2.first && p1.second < p2.second);
    }
};

struct pair_hash {
public:
    size_t operator()(const pair<i64, i64> &x) const {
        return hash<i64>()(x.first) ^ hash<i64>()(x.second);
    }
};
