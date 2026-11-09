#include <cstdio>
#include <utility>
#include <iostream>
#include <vector>
using namespace std;

/**
 * Output whether all of the requests can be fulfilled.
 *
 * N: Number of smoke requests
 * R: Number of seconds needed for a smoke charge to recharge
 * A: List of timestamps where smokes are requested
 */
string solve(int N, int R, vector<int> A) {
    const long long recharge = R;
    long long work = 0;
    long long previous = 0;
    for (int i = 0; i < N; ++i) {
        const long long elapsed = A[i] - previous;
        const long long pending = ((elapsed <= work) ? (work - elapsed) : 0LL);
        if (!(pending <= recharge)) {
            return "NO";
        }
        work = pending + recharge;
        previous = A[i];
    }
    return "YES";
}

// cvc5 synthesized the digit predicate and accumulator update.
class Input {

    unsigned char buffer[65536];
    std::size_t pos = 0;
    std::size_t end = 0;

    int nextByte() {
        if (pos == end) {
            end = std::fread(buffer, 1, sizeof buffer, stdin);
            pos = 0;
            if (end == 0) {
                return EOF;
            }
        }
        return buffer[pos++];
    }

public:
    bool readInt(int& result) {
        int byte = nextByte();
        while (byte != EOF && byte <= ' ') {
            byte = nextByte();
        }
        if (byte == EOF || !((48LL <= byte) && (byte <= 57LL))) {
            return false;
        }

        long long value = 0;
        do {
            value = ((10LL * value) + byte + -48LL);
            byte = nextByte();
        } while (((48LL <= byte) && (byte <= 57LL)));
        result = static_cast<int>(value);
        return true;
    }
};

int main() {
    Input input;
    int T;
    if (!input.readInt(T)) {
        return 0;
    }
    while (T--) {
        int N, R;
        if (!input.readInt(N) || !input.readInt(R)) {
            return 0;
        }
        vector<int> A(N);
        for (int& timestamp : A) {
            if (!input.readInt(timestamp)) {
                return 0;
            }
        }
        cout << solve(N, R, std::move(A)) << '\n';
    }
}
