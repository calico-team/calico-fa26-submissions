#include<bits/stdc++.h>
using namespace std;

struct Earthquake {
    int r, c, p;
};


int findNext(vector<int>& parent, int x) {
    while (parent[x] != x) {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        int n, m, q;
        scanf("%d %d %d", &n, &m, &q);

        vector<Earthquake> earthquakes(q);
        for (int i = 0; i < q; i++) {
            scanf("%d %d %d", &earthquakes[i].r,
                  &earthquakes[i].c, &earthquakes[i].p);
        }

        vector<int> ans(n * m, 0);

        
        vector<int> parent(n * (m + 1));
        iota(parent.begin(), parent.end(), 0);

        for (int i = q - 1; i >= 0; i--) {
            int r = earthquakes[i].r;
            int c = earthquakes[i].c;
            int p = earthquakes[i].p;

            for (int row = r - p; row <= r + p; row++) {
                int dr = row - r;
                int remaining = p * p - dr * dr;
                int width = (int)sqrt(remaining);


                while ((width + 1) * (width + 1) <= remaining) width++;
                while (width * width > remaining) width--;

                int base = row * (m + 1);
                int right = base + c + width;
                int pos = findNext(parent, base + c - width);

                while (pos <= right) {
                    int col = pos - base;
                    int dc = col - c;
                    ans[row * m + col] = remaining - dc * dc + 1;

                    
                    parent[pos] = findNext(parent, pos + 1);
                    pos = parent[pos];
                }
            }
        }

        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                printf("%d%c", ans[r * m + c], c == m - 1 ? '\n' : ' ');
            }
        }
    }

    return 0;
}
