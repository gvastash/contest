#pragma once

#include <string>
#include <vector>

using namespace std;

typedef int i32;

vector<i32> compute_z(const string& s) {
    i32 n = s.size();

    vector<i32> z(n);

    i32 l = 0;
    i32 r = 1;

    for (i32 i = 1; i < n; i++) {
        if (i < r) {
            z[i] = min(r - i, z[i - l]);
        }

        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i] += 1;
        }

        if (r < i + z[i]) {
            l = i;
            r = i + z[i];
        }
    }

    return z;
}