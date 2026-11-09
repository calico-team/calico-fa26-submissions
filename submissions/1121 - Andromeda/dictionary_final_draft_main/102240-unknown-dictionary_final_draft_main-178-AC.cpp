#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

vector<int> children[200005];
int a[200005];
int v[200005];
bool visited[200005];

struct bnode
{
    bnode *zero;
    bnode *one;
};

bnode root = {nullptr, nullptr};
int A[200005];

pair<bnode *, bool> add(int node, int dstrick)
{
    bnode *cur = &root;
    pair<bnode *, bool> branch = {nullptr, 0};
    for (int i = 29; i >= 0; i--)
    {
        bool b = ((dstrick >> i) & 1) ^ ((v[node] >> i) & 1);
        if (b == 0)
        {
            if (cur->zero == nullptr)
            {
                cur->zero = new bnode{nullptr, nullptr};
                if (branch.first == nullptr)
                    branch = {cur, 0};
            }
            cur = cur->zero;
        }
        else
        {
            if (cur->one == nullptr)
            {
                cur->one = new bnode{nullptr, nullptr};
                if (branch.first == nullptr)
                    branch = {cur, 1};
            }
            cur = cur->one;
        }
    }
    return branch;
}

void calc_ans(int node, int dstrick)
{
    bnode *cur = &root;
    int ans = 0;
    for (int i = 29; i >= 0; i--)
    {
        bool d = !((dstrick >> i) & 1);
        if (d == 0)
        {
            if (cur->zero == nullptr)
                cur = cur->one;
            else
            {
                cur = cur->zero;
                ans |= (1 << i);
            }
        }
        else
        {
            if (cur->one == nullptr)
                cur = cur->zero;
            else
            {
                cur = cur->one;
                ans |= (1 << i);
            }
        }
    }
    A[node] = ans;
}

void rem(pair<bnode *, bool> branch)
{
    if (branch.first != nullptr)
    {
        if (branch.second == 0)
        {
            branch.first->zero = nullptr;
        }
        else
        {
            branch.first->one = nullptr;
        }
    }
}

void dfs(int node, int dstrick)
{
    if (visited[node])
        return;
    visited[node] = true;
    dstrick ^= v[node];
    auto branch = add(node, dstrick);
    calc_ans(node, dstrick);
    for (int child : children[node])
    {
        dfs(child, dstrick);
    }
    rem(branch);
}

void solve()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        children[i].clear();
        visited[i] = false;
    }
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        a[i]--;
        children[a[i]].push_back(i);
    }
    for (int i = 0; i < n; i++)
        cin >> v[i];

    for (int i = 0; i < n; i++)
    {
        root = {nullptr, nullptr};
        if (visited[i])
            continue;
        set<int> s;
        deque<int> cycle;
        // find cycle
        int j = i;
        while (s.find(j) == s.end())
        {
            s.insert(j);
            cycle.push_back(j);
            j = a[j];
        }
        while (cycle.front() != a[cycle.back()])
        {
            s.erase(s.find(cycle.front()));
            cycle.pop_front();
        }

        int cycleXor = 0;
        for (int p : cycle)
            cycleXor ^= v[p];

        int dstrick = 0;
        for (int j = (int)cycle.size() - 1; j >= 0; j--)
        {
            int p = cycle[j];
            dstrick ^= v[p];

            add(p, dstrick);
            if (cycleXor != 0)
                add(p, dstrick ^ cycleXor);

            visited[p] = true;
        }

        for (int p : cycle)
        {
            calc_ans(p, dstrick);

            for (int child : children[p])
                dfs(child, dstrick);

            dstrick ^= v[p];
        }
    }

    for (int i = 0; i < n; i++)
        cout << A[i] << ' ';
    cout << endl;
}

int32_t main()
{
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
