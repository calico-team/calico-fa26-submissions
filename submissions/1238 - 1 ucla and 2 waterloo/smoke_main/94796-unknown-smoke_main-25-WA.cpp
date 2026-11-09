#include <bits/stdc++.h>
using namespace std;

enum Type {
	Regen,
	Use,
};

struct Event {
	Type type;
	int time;
	bool operator<(const Event &o) const {
		return !(time < o.time || (time == o.time && type < o.type));
	}
};

int main() {
	cin.tie(0)->sync_with_stdio(0);

	int t;
	cin >> t;
	while (t--) {
		int n, r;
		cin >> n >> r;
		priority_queue<Event> events;

		for (int i = 0; i < n; i++) {
			int x;
			cin >> x;
			events.push({Use, x});
		}

		int smokes = 2;
		int last_regen = 0;
		while (!events.empty()) {
			auto [type, time] = events.top();
			events.pop();
			if (type == Use) {
				if (--smokes < 0)
					goto fail;
				events.push({Regen, time + r});
			} else {
				if (smokes == 0) {
					smokes = 1;
					events.push({Regen, time + r});
					last_regen = time;
				} else if (smokes == 1) {
					if (time >= last_regen + r) {
						smokes = 2;
					} else {
						events.push({Regen, last_regen + r});
					}
				}
			}
		}

		cout << "YES\n";
		continue;
	fail:
		cout << "NO\n";
	}

	return 0;
}
