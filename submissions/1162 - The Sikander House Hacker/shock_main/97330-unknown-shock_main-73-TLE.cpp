#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

char rbuf[1 << 16];
int rit = 0, rlen = 0;
inline char readChar() {
    if (rit >= rlen) {
        rit = 0;
        rlen = fread(rbuf, 1, 1 << 16, stdin);
        if (rlen <= 0) return EOF;
    }
    return rbuf[rit++];
}

inline bool readInt(int &x) {
    char c = readChar();
    while (c <= ' ') {
        if (c == EOF) return false;
        c = readChar();
    }
    x = 0;
    while (c > ' ') {
        x = x * 10 + (c - '0');
        c = readChar();
    }
    return true;
}

const int BUF_SIZE = 1 << 16;
char outbuf[BUF_SIZE];
int outit = 0;

inline void flushOut() {
    if (outit > 0) {
        fwrite(outbuf, 1, outit, stdout);
        outit = 0;
    }
}

inline void writeChar(char c) {
    if (outit >= BUF_SIZE) flushOut();
    outbuf[outit++] = c;
}

inline void writeInt(int x) {
    if (x == 0) {
        writeChar('0');
        return;
    }
    char temp[12];
    int idx = 0;
    while (x > 0) {
        temp[idx++] = (x % 10) + '0';
        x /= 10;
    }
    while (idx > 0) {
        writeChar(temp[--idx]);
    }
}

vector<int> grid;

void solve() {
    int N, M, Q;
    if (!readInt(N) || !readInt(M) || !readInt(Q)) return;
    
    grid.assign(N * M, 0);
    
    for (int i = 0; i < Q; ++i) {
        int r_e, c_e, p_e;
        readInt(r_e);
        readInt(c_e);
        readInt(p_e);
        
        long long p_sq = (long long)p_e * p_e;
        int r_min = max(0, r_e - p_e);
        int r_max = min(N - 1, r_e + p_e);
        int c_min = max(0, c_e - p_e);
        int c_max = min(M - 1, c_e + p_e);
        
        for (int r = r_min; r <= r_max; ++r) {
            long long rd2 = (long long)(r - r_e) * (r - r_e);
            int row_offset = r * M;
            for (int c = c_min; c <= c_max; ++c) {
                long long d2 = rd2 + (long long)(c - c_e) * (c - c_e);
                if (d2 <= p_sq) {
                    grid[row_offset + c] = (int)(p_sq - d2 + 1);
                }
            }
        }
    }
    
    for (int r = 0; r < N; ++r) {
        int row_offset = r * M;
        for (int c = 0; c < M; ++c) {
            writeInt(grid[row_offset + c]);
            if (c + 1 < M) writeChar(' ');
        }
        writeChar('\n');
    }
}

int main() {
    int T;
    if (readInt(T)) {
        while (T--) {
            solve();
        }
    }
    flushOut();
    return 0;
}