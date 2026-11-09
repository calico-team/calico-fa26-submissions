
#include <cstdio>
using namespace std;

class FastInput {
    static const int SIZE = 1 << 16;
    char buffer[SIZE];
    int pos = 0, len = 0;

    char getChar() {
        if (pos == len) {
            len = fread(buffer, 1, SIZE, stdin);
            pos = 0;
            if (len == 0) return 0;
        }
        return buffer[pos++];
    }

public:
    int readInt() {
        char c = getChar();
        while (c && c <= ' ') c = getChar();

        int x = 0;
        while (c >= '0' && c <= '9') {
            x = x * 10 + c - '0';
            c = getChar();
        }
        return x;
    }
};

int main() {
    FastInput in;

    int T = in.readInt();

    while (T--) {
        int N = in.readInt();
        int R = in.readInt();

        int charges = 2;
        long long nextRecharge = 0;
        bool possible = true;

        for (int i = 0; i < N; i++) {
            long long t = in.readInt();

            if (!possible) continue;

            // Process completed recharges
            while (charges < 2 && t >= nextRecharge) {
                charges++;

                if (charges < 2)
                    nextRecharge += R;
            }

            // Cannot fulfill this request
            if (charges == 0) {
                possible = false;
                continue;
            }

            // Start recharge when using a full stock
            if (charges == 2)
                nextRecharge = t + R;

            charges--;
        }

        puts(possible ? "YES" : "NO");
    }

    return 0;
}
