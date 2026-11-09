#include <bits/stdc++.h>
#include <assert.h>
using namespace std;

/*
Communication problem, I love these
So we just need to store each edge as an integer and then have a checksum, right?
Wrong, there is just too much data to encode!

Let's see if we can root the tree and just have every node point to its predecessor except one
*/

#define X 200005
char phase[20];
int arr[X];
int par[X];
vector<int> adj[X];

void dfs(int n, int p=-1)
{
    par[n] = p;
    for (auto z : adj[n]) if (z != p) dfs(z, n);
}

int main()
{
    scanf("%s", phase);
    int n; scanf("%d", &n);
    if (phase[0] == 'F')
    {
        for (int i=0; i<n-1; i++)
        {
            int a, b; scanf("%d%d", &a, &b);
            --a; --b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        dfs(0);
        long long sum = 0;
        for (int i=1; i<n; i++)
        {
            printf("%d ", par[i]);
            sum += par[i];
        }
        sum %= n;
        sum = 3*n - sum;
        printf("%lld\n", sum);
        return 0;
    }
    else
    {
        for (int i=0; i<n; i++) scanf("%d", arr+i);
        if (arr[n-1] != -1) assert(arr[n-1] > n);
        long long sum = 1;
        for (int i=0; i<n; i++) sum += arr[i];
        sum %= n;
        sum = (n-sum)%n;
        for (int i=0; i<n; i++) if (arr[i] == -1) arr[i] = sum;
        for (int i=0; i<n-1; i++) printf("%d %d\n", arr[i]+1, i+2);
        return 0;
    }
}
