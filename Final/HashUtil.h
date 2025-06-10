#pragma once
#define ll long long
#include <string>

using namespace std;

class HashUtil {
public:
    static string generarHash(const string& input) {
        const int base = 37;
        const int mod = 1e9 + 7;
        ll hash = 0;

        for (char c : input) {
            hash = (hash * base + c) % mod;
        }

        return to_string(hash);
    }
};