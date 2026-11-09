#include <bits/stdc++.h>
#include <assert.h>
using namespace std;

#define X 205
char arr[X*X];

int dsu[X*X];
int par(int x) { return (dsu[x]<0) ? x : (dsu[x]=par(dsu[x])); }
void merg(int x, int y)
{
//    printf("Merge requested on %d %d\n", x, y);
    x = par(x);
    y = par(y);
    if (x == y) return;
    if (dsu[x] > dsu[y]) swap(x,y);
    dsu[x] += dsu[y];
    dsu[y] = x;
}

bool connect(int x, int y)
{
    if (arr[x] == '.') return true;
    if (arr[y] == '.') return true;
    if (arr[x] == arr[y]) return true;
    return false;
}

int main()
{
    int t; scanf("%d", &t);
    start:;

    int n, m, q; scanf("%d%d%d", &n, &m, &q);
    for (int i=0; i<n; i++) scanf("%s", arr+m*i);
    fill_n(dsu, n*m, -1);

    for (int i=0; i<n; i++) for (int j=1; j<m; j++)
    {
        int x = m*i+(j-1), y = m*i+j;
        if (connect(x,y)) merg(x,y);
    }
    for (int i=1; i<n; i++) for (int j=0; j<m; j++)
    {
        int x = m*(i-1)+j, y = m*i+j;
        if (connect(x,y)) merg(x,y);
    }

    for (int i=0; i<q; i++)
    {
        int a, b, c, d; scanf("%d%d%d%d", &a, &b, &c, &d);
        int x = m*a+b;
        int y = m*c+d;
        if (par(x) == par(y)) puts("YES");
        else puts("NO");
    }

    if (--t) goto start;
    return 0;
}
