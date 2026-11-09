#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n, a[200005], v[200005], vis[200005], cyc[200005], ans[200005];
vector <int> adj[200005];

//copied from gfg https://www.geeksforgeeks.org/dsa/maximum-xor-queries-with-an-element-from-array/
class node {
public:
    node *left;
    node *right;
    int cnt = 0;
};

// Trie class to insert numbers and find maximum XOR
class trie {
    node *root;

public:
    // Constructor to initialize the root
    trie() {
        root = new node();
    }

    // Insert a number into the Trie (bit by bit from MSB to LSB)
    void insert(int n) {
        node *temp = root;
        for (int i = 30; i >= 0; i--) {
            int bit = (n >> i) & 1;
            if (bit == 0) {
                if (temp->left == NULL)
                    temp->left = new node();
                temp = temp->left;
                temp->cnt++;
            } else {
                if (temp->right == NULL)
                    temp->right = new node();
                temp = temp->right;
                temp->cnt++;
            }
        }
    }
    
    void rmv (int v) {
		node *temp = root;
		for (int i = 30; i >= 0; i--) {
			int bit = (v >> i) & 1;
            if (bit == 0) {
                if (temp->left == NULL)
                    temp->left = new node();
                temp = temp->left;
                temp->cnt--;
            } else {
                if (temp->right == NULL)
                    temp->right = new node();
                temp = temp->right;
                temp->cnt--;
            }
		}
	}

    // Helper function to find the maximum XOR value with a given number
    int xorHelper(int value) {
        int curr = 0;
        node *temp = root;

        for (int j = 30; j >= 0; j--) {
            int bit = (value >> j) & 1;

            // Prefer the opposite bit for maximizing XOR
            if (bit == 0) {
                if (temp->right != NULL && temp->right->cnt > 0) {
                    temp = temp->right;
                    curr += (1 << j); 
                } else {
                    temp = temp->left;
                }
            } else {
                if (temp->left != NULL && temp->left->cnt > 0) {
                    temp = temp->left;
                    curr += (1 << j); 
                } else {
                    temp = temp->right;
                }
            }
        }

        return curr;
    }
};


trie tree, tree2;

void dfs (int x, int dumdum) {
	vis[x] = 1;
	if (!cyc[x]) dumdum ^= v[x];
	//if (x == 2) cout << dumdum << '\n';
	if (!cyc[x]) ans[x] = tree2.xorHelper(v[x]);
	if (!cyc[x]) ans[x] = max(ans[x], tree.xorHelper(dumdum));
	if (!cyc[x]) tree2.insert(v[x]);
	for (auto i : adj[x]) if (!cyc[i]) dfs(i, dumdum);
	if (!cyc[x]) tree2.rmv(v[x]);
}

int32_t main(){
    ios::sync_with_stdio(0); cin.tie(0);
    int tc; cin >> tc;
    while (tc--) {
        cin >> n;
        for (int i = 1; i <= n; i++) adj[i].clear(), cyc[i] = 0, ans[i] = 0;
        for (int i = 1; i <= n; i++) cin >> a[i], adj[a[i]].push_back(i), vis[i] = 0;
        for (int i = 1; i <= n; i++) cin >> v[i];
        tree2.insert(0);
        for (int i = 1; i <= n; i++) {
			if (!vis[i]) {
				int cur = i;
				while (!vis[cur]) {
					vis[cur] = 1;
					cur = a[cur];
				}
				vector <int> cc;
				int g = 0, t = 0;
				while (!cyc[cur]) {
					cc.push_back(cur);
					cyc[cur] = 1;
					cur = a[cur];
				}
				for (auto j : cc) t ^= v[j];
				for (auto j : cc) {
					g ^= v[j];
					tree.insert(g);
					tree.insert(g ^ t);
				}
				g = 0;
				for (auto j : cc) {
					//cout << j << ' ';
					ans[j] = tree.xorHelper(g);
					dfs(j, g);
					g ^= v[j];
				}
				//cout << '\n';
				g = 0;
				for (auto j : cc) {
					g ^= v[j];
					tree.rmv(g);
					tree.rmv(g ^ t);
				}
			}
		}
		for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
		cout << '\n';
    }
}
