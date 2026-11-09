#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <utility>
using namespace std;

// the xor of values in [0, a] and [0, b] fills [0, result]
int merge_ranges(int a, int b) {
	if (a < 0 || b < 0) return -1;  // empty set
	int result = a | b;
	unsigned int common = (unsigned int)(a & b);
	if (common != 0) {
		int highest = 31 - __builtin_clz(common);
		result |= (1 << highest) - 1;
	}
	return result;
}

/**
 * Return the maximum possible value of X, Big Ben's matcha enjoyment.
 *
 * N: the days in Big Ben's life
 * L: the lower bound of enjoyment from each store
 * R: the upper bound of enjoyment from each store
 */
int solve(int N, vector<int> L, vector<int> R) {
	// group by the highest bit where the ends differ
	// -1 means that group has no reachable values
	array<int, 30> even{};
	array<int, 30> odd;
	odd.fill(-1);
	int base_xor = 0;

	for (int i = 0; i < N; ++i) {
		int left = L[i];
		int right = R[i];
		if (left == right) {
			base_xor ^= left;
			continue;
		}

		int bit = 31 - __builtin_clz((unsigned int)(left ^ right));
		int split_low = left | ((1 << bit) - 1);
		int split_high = split_low + 1;
		base_xor ^= split_low;

		// split at the boundary where this bit changes
		int low_span = split_low - left;
		int high_span = right - split_high;
		int new_even = max(merge_ranges(even[bit], low_span),
			merge_ranges(odd[bit], high_span));
		int new_odd = max(merge_ranges(even[bit], high_span),
			merge_ranges(odd[bit], low_span));
		even[bit] = new_even;
		odd[bit] = new_odd;
	}

	// after fixing the higher bits, reachable values are a prefix and a
	// suffix of the remaining range; keep both while choosing each bit
	int front = 0;
	int back = -1;
	int best = 0;
	for (int bit = 29; bit >= 0; --bit) {
		int half = 1 << bit;
		if (odd[bit] != -1) {
			int next_prefix = max(merge_ranges(front, even[bit]),
				merge_ranges(back, odd[bit]));
			int next_suffix = max(merge_ranges(front, odd[bit]),
				merge_ranges(back, even[bit]));
			front = next_prefix;
			back = next_suffix;
		}

		// keep values with the bit we choose
		auto keep_bit = [&](int bit_value) -> pair<int, int> {
			int first = -1, last = -1;
			if (bit_value == 0) {
				if (front >= 0) first = min(front, half - 1);
				if (back >= half) last = back - half;
			} else {
				if (front >= half) first = front - half;
				if (back >= 0) last = min(back, half - 1);
			}
			return {first, last};
		};

		int target = 1 ^ ((base_xor >> bit) & 1);
		auto kept = keep_bit(target);
		if (kept.first >= 0 || kept.second >= 0) {
			best |= half;
		} else {
			kept = keep_bit(target ^ 1);
		}
		front = kept.first;
		back = kept.second;
	}
	return best;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T; cin >> T;
	while (T--) {
		int N; cin >> N;
		vector<int> L(N), R(N);
		for (int& i : L) cin >> i;
		for (int& i : R) cin >> i;
		cout << solve(N, L, R) << '\n';
	}
	return 0;
}
