#include <bits/stdc++.h>
#include <assert.h>
using namespace std;

/*
Problem 8
Obviously just figure out the circles right? Values don't matter until the end

*/

#define X 20005
array<int,3> arr[X];
int gap;
vector<int> seg[1005];
bool swapped;

void segset(int x, int l, int r, int v)
{
    l += gap;
    r += gap;
    while (l<=r)
    {
        if (l&1) seg[x][l++] = v;
        if (~r&1) seg[x][r--] = v;
        l >>= 1;
        r >>= 1;
    }
}

long long square(int x) { return (long long)x*x; }

int main()
{
    int t; scanf("%d", &t);
    start:;

    int n, m, q; scanf("%d%d%d", &n, &m, &q);
    for (int i=1; i<=q; i++) scanf("%d%d%d", &arr[i][0], &arr[i][1], &arr[i][2]);
    swapped = false;
    if (n > m)
    {
        swap(n,m);
        for (int i=1; i<=q; i++) swap(arr[i][0], arr[i][1]);
        swapped = true;
    }

    // segtree, lazy
    gap = 1<<(1+__lg(m));
    for (int i=0; i<n; i++) seg[i].resize(2*gap+5, 0);
    for (int i=1; i<=q; i++)
    {
        auto [x,y,r] = arr[i];
        for (int j=-r; j<=r; j++)
        {
            if (x-j < 0 || x+j >= n) continue;
            int s = sqrt(r*r-j*j);
            assert(s*s + j*j <= r*r);
            assert((s+1)*(s+1) + j*j > r*r);
            segset(x+j, max(0,y-s), min(m,y+s), i);
        }
    }
    for (int i=0; i<n; i++) for (int j=1; j<gap; j++)
    {
        seg[i][2*j] = max(seg[i][2*j], seg[i][j]);
        seg[i][2*j+1] = max(seg[i][2*j+1], seg[i][j]);
    }

    if (swapped)
    {
        for (int i=0; i<m; i++)
        {
            for (int j=0; j<n; j++)
            {
                int x = seg[j][gap+i];
                long long v = 0;
                if (x) v = square(arr[x][2]) - square(arr[x][0]-j) - square(arr[x][1]-i) + 1;
                assert (v >= 0);
                printf("%lld ", v);
            }
            putchar('\n');
        }
    }
    else
    {
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<m; j++)
            {
                int x = seg[i][gap+j];
                long long v = 0;
                if (x) v = square(arr[x][2]) - square(arr[x][0]-i) - square(arr[x][1]-j) + 1;
                assert (v >= 0);
                printf("%lld ", v);
            }
            putchar('\n');
        }
    }

    for (int i=0; i<n; i++) seg[i].clear();
    if (--t) goto start;
    return 0;
}
