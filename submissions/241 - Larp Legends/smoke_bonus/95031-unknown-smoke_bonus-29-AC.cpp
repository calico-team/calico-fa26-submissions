#include <bits/stdc++.h>
using namespace std;

static char buf[1 << 25];

int main() {
    // fast custom input
    size_t len;
    size_t cap = 0;
    string all;
    {
        size_t n;
        while ((n = fread(buf, 1, sizeof(buf), stdin)) > 0) all.append(buf, n);
    }
    const char* p = all.c_str();
    auto readInt = [&]() -> long long {
        while (*p && (*p < '0' || *p > '9')) p++;
        long long x = 0;
        while (*p >= '0' && *p <= '9') { x = x * 10 + (*p - '0'); p++; }
        return x;
    };
    (void)len; (void)cap;

    int T = (int)readInt();
    string out;
    while (T--) {
        int n = (int)readInt();
        long long r = readInt();
        int charges = 2;
        long long ready = 0;
        bool ok = true;
        for (int i = 0; i < n; i++) {
            long long t = readInt();  // must keep reading even after failure
            if (!ok) continue;
            while (charges < 2 && ready <= t) {
                charges++;
                if (charges < 2) ready += r;
            }
            if (charges == 0) { ok = false; continue; }
            if (charges == 2) ready = t + r;
            charges--;
        }
        out += ok ? "YES\n" : "NO\n";
    }
    fputs(out.c_str(), stdout);
    return 0;
}
