#pragma once

#include <vector>

using namespace std;

typedef long long int i64;

struct TSparseTable {
    using Type = i64;

    vector<Type> Log;
    vector<vector<Type>> Data;

    Type Combine(Type a, Type b) {
        return min(a, b);
    }

    TSparseTable(const vector<Type>& data) {
        Log.resize(data.size() + 1);
        Log[1] = 0;
        for (i64 i = 2; i <= data.size(); i++) {
            Log[i] = 1 + Log[i / 2];
        }

        Data = vector<vector<Type>>(data.size(), vector<Type>(Log.back() + 1));
        for (i64 i = 0; i < data.size(); i++) {
            Data[i][0] = data[i];
        }

        for (i64 j = 1; j <= Log.back(); j++) {
            for (i64 i = 0; i + (1ll << j) <= data.size(); i++) {
                Data[i][j] = Combine(Data[i][j - 1], Data[i + (1ll << (j - 1))][j - 1]);
            }
        }
    }

    Type Calc(i64 l, i64 r) {
        i64 j = Log[r - l];
        return Combine(Data[l][j], Data[r - (1ll << j)][j]);
    }
};