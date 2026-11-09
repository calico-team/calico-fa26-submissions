#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    int x, y;
    bool ok;
};

void run() {
    int num;
    if (!(cin >> num)) return;

    vector<int> mn(num), mx(num);
    for (int i = 0; i < num; ++i) cin >> mn[i];
    for (int i = 0; i < num; ++i) cin >> mx[i];

    vector<Node> items(num);
    for (int i = 0; i < num; ++i) {
        items[i] = {mn[i], mx[i], false};
    }

    int res = 0;

    for (int k = 29; k >= 0; --k) {
        int active = 0;
        int open = 0;

        for (int i = 0; i < num; ++i) {
            if (items[i].ok) {
                open++;
            } else {
                int low = (items[i].x >> k) & 1;
                int high = (items[i].y >> k) & 1;

                if (low == 1 && high == 1) {
                    active++;
                } else if (low == 0 && high == 1) {
                    open++;
                }
            }
        }

        int target = 0;

        if (open > 0) {
            target = 1;
        } else {
            target = active % 2;
        }

        if (target == 1) {
            res |= (1 << k);
        }

        int current = active % 2;
        bool flip = (current != target);

        for (int i = 0; i < num; ++i) {
            if (items[i].ok) continue;

            int low = (items[i].x >> k) & 1;
            int high = (items[i].y >> k) & 1;

            if (low == 0 && high == 1) {
                if (flip) {
                    items[i].ok = true;
                    flip = false;
                } else {
                    items[i].ok = true;
                }
            }
        }
    }

    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int test;
    if (cin >> test) {
        while (test--) {
            run();
        }
    }
    return 0;
}
