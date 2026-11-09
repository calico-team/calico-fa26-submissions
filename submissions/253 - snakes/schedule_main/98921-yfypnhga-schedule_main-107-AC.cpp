#include <bits/stdc++.h>
using namespace std;

int N, M, K;
int P[10005], dep[10005];

// how long the prereq chain is, roots are 1. a course at depth d cant go before semester d
int depth(int i) {
    if (dep[i]) return dep[i];
    if (P[i] == 0) return dep[i] = 1;
    return dep[i] = depth(P[i]) + 1;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d %d", &N, &M, &K);
        for (int i = 1; i <= N; i++) scanf("%d", &P[i]);
        for (int i = 1; i <= N; i++) dep[i] = 0;

        int maxd = 0;
        for (int i = 1; i <= N; i++) maxd = max(maxd, depth(i));

        // cnt[t] = how many courses have depth <= t
        vector<int> cnt(maxd + 1, 0);
        for (int i = 1; i <= N; i++) cnt[dep[i]]++;
        for (int t = 1; t <= maxd; t++) cnt[t] += cnt[t - 1];

        // first t semesters only fit courses of depth <= t, the other M-t fit K each.
        // the min over t is always reachable for a forest so thats the answer.
        // past maxd cnt is just N and it only gets smaller, no point looping further
        long long best = (long long)M * K;
        for (int t = 1; t <= min(M, maxd); t++)
            best = min(best, cnt[t] + (long long)(M - t) * K);
        if (M >= maxd) best = min(best, (long long)N);
        printf("%lld\n", best);
    }
}
