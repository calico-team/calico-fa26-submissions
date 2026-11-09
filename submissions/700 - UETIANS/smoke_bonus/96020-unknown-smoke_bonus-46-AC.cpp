#include <cstdio>
#include <string>
using namespace std;

// Fast positive-integer reader.
static inline long long readInt() {
	int c = getchar_unlocked();
	while (c != '-' && (c < '0' || c > '9')) c = getchar_unlocked();
	bool neg = false;
	if (c == '-') { neg = true; c = getchar_unlocked(); }
	long long x = 0;
	while (c >= '0' && c <= '9') { x = x * 10 + (c - '0'); c = getchar_unlocked(); }
	return neg ? -x : x;
}

int main() {
	const long long NEG = -(long long)4e18;
	int T = (int)readInt();
	string out;
	while (T--) {
		int N = (int)readInt();
		long long R = readInt();
		long long c1 = NEG, c2 = NEG, freeT = NEG;
		bool ok = true;
		for (int i = 0; i < N; ++i) {
			long long t = readInt();
			if (!ok) continue;              // keep consuming the rest of this case
			if (c1 > c2) { long long tmp = c1; c1 = c2; c2 = tmp; }
			if (c1 > t) { ok = false; continue; }
			long long start = (t > freeT) ? t : freeT;
			freeT = start + R;
			c1 = freeT;
		}
		out += ok ? "YES\n" : "NO\n";
	}
	fputs(out.c_str(), stdout);
	return 0;
}
