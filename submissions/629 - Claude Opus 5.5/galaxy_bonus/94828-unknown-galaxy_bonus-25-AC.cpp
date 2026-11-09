using namespace std;
#include <bits/stdc++.h>
 
#define yes cout << "YES" << endl;
#define no cout << "NO" << endl;
 
#define ll long long
#define read(arr) for (auto &x: arr) cin >> x;
#define print_vec(arr) for (auto arr_val: arr) { cout << arr_val << " "; } cout << endl
 
// https://codeforces.com/blog/entry/70327, written 5 years ago
ll mod_pow(ll a, ll b, ll m){
    int ans = 1;
    while(b){
        if (b&1) ans = (ans*a) % m;
        b /= 2;
        a = (a*a) % m;
    }
    return ans;
}

// https://usaco.guide/gold/hashing?lang=cpp
long long rng() {
	static std::mt19937 gen(
	    std::chrono::steady_clock::now().time_since_epoch().count());
	return std::uniform_int_distribution<long long>(0, INT64_MAX)(gen);
}
// https://usaco.guide/gold/dsu?lang=cpp
class DisjointSets {
  private:
	vector<int> parents;
	vector<int> sizes;

  public:
	DisjointSets(int size) : parents(size), sizes(size, 1) {
		for (int i = 0; i < size; i++) { parents[i] = i; }
	}

	/** @return the "representative" node in x's component */
	int find(int x) { return parents[x] == x ? x : (parents[x] = find(parents[x])); }

	/** @return whether the merge changed connectivity */
	bool unite(int x, int y) {
		int x_root = find(x);
		int y_root = find(y);
		if (x_root == y_root) { return false; }

		if (sizes[x_root] < sizes[y_root]) { swap(x_root, y_root); }
		sizes[x_root] += sizes[y_root];
		parents[y_root] = x_root;
		return true;
	}

	/** @return whether x and y are in the same connected component */
	bool connected(int x, int y) { return find(x) == find(y); }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;

    while (t--) {
        int n, m, q;
        cin >> n >> m >> q;

        vector<string> vec(n);
        for (auto &x: vec) cin >> x;
        DisjointSets dsu(n*m);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                //cerr << 'a' << "\n";
                if (i != 0 && (vec[i][j] == '.' || vec[i-1][j] == '.' || vec[i][j] == vec[i-1][j])) dsu.unite(i*m + j, (i-1)*m + j);
                //cerr << 'a' << "\n";
                if (i != n-1 && (vec[i][j] == '.' || vec[i+1][j] == '.' | vec[i][j] == vec[i+1][j])) dsu.unite(i*m + j, (i+1)*m + j);
                //cerr << 'a' << "\n";
                if (j != 0 && (vec[i][j] == '.' || vec[i][j-1] == '.' || vec[i][j] == vec[i][j-1])) dsu.unite(i*m + j, i*m + (j-1));
                if (j != m-1 && (vec[i][j] == '.' || vec[i][j+1] == '.' || vec[i][j] == vec[i][j+1])) dsu.unite(i*m + j, i*m + (j+1));
            }
        }
        while (q--) {
            int x1, y1, x2, y2;
            cin >> y1 >> x1 >> y2 >> x2;

            if (dsu.connected(y1*m+x1, y2*m+x2)) yes
            else no
        }


    }
}
