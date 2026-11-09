#include <bits/stdc++.h>
using namespace std;
 
static char buf[1 << 16];
static size_t bl = 0, bp = 0;
 
static inline int gc() {
    if (bp == bl) {
        bl = fread(buf, 1, sizeof(buf), stdin);
        bp = 0;
        if (bl == 0) return -1;
    }
    return buf[bp++];
}
 
static long long readInt() {
    int ch = gc();
    while (ch != -1 && (ch < '0' || ch > '9')) ch = gc();
    long long x = 0;
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + (ch - '0');
        ch = gc();
    }
    return x;
}
 
int main() {
    int T = (int)readInt();
    while (T--) {
        int N = (int)readInt();
        long long R = readInt();
        int charges = 2;
        long long timer = 0;
        bool ok = true;
        for (int i = 0; i < N; i++) {
            long long a = readInt();
            if (!ok) continue;
            while (charges < 2 && timer <= a) {
                charges++;
                if (charges < 2) timer += R;
            }
            if (charges == 0) {
                ok = false;
                continue;
            }
            if (charges == 2) timer = a + R;
            charges--;
        }
        puts(ok ? "YES" : "NO");
    }
    return 0;
}
 