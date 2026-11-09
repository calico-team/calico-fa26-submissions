#include <cstdio>
using namespace std;

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        int n;
        long long r;
        scanf("%d %lld", &n, &r);

        int charges = 2;
        long long nextRecharge = 0;
        bool possible = true;

        for (int i = 0; i < n; i++) {
            long long time;
            scanf("%lld", &time);

            if (!possible) continue;

            // Restore charges before handling this request.
            while (charges < 2 && nextRecharge <= time) {
                charges++;
                nextRecharge += r;
            }

            if (charges == 0) {
                possible = false;
                continue;
            }

            // Using a charge from full capacity starts a new recharge.
            if (charges == 2) {
                nextRecharge = time + r;
            }
            charges--;
        }

        if (possible) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}
