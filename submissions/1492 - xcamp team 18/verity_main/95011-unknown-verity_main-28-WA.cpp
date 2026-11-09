#include <algorithm>
#include <bits/stdc++.h>
#include <unordered_map>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
using ll = long long;

using ordered_set = tree<
    ll,
    null_type,
    less<ll>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;

#define int ll
int fastPowMod(int base,int exp,int mod) {
    int res=1;
    base%=mod;
    while (exp>0) {
        if (exp&1)res=(res*base)%mod;
        base=(base*base)%mod;
        exp>>=1;
    }
    return res;
}

// --- Dynamic nCr Helper (O(r) execution, no memory) ---
int nCr(int n, int r, int mod = 1e9 + 7) {
    if (r < 0 || r > n) return 0;
    if (r == 0 || r == n) return 1;
    if (r > n - r) r = n - r; // Optimize iteration count

    int num = 1, den = 1;
    for (int i = 0; i < r; i++) {
        num = (num * (n - i)) % mod;
        den = (den * (i + 1)) % mod;
    }
    return (num * fastPowMod(den, mod - 2, mod)) % mod;
}


void printSet(unordered_set<int>&temp){
    for (auto val:temp){
        cout<<val<<" ";
    }
    cout<<endl;

}


void printList(const vector<int>&temp){
    for (int i=0;i<temp.size();i++){
        cout<<temp[i]<<" ";

    }
    cout<<endl;
}



void printArray(vector<vector<int>>&temp){
    for (int i=0;i<temp.size();i++){
        for (int j=0;j<temp[i].size();j++){
            cout<<temp[i][j]<<" ";
        }
        cout<<endl;
    }
}
void printPartial(vector<vector<vector<int>>>&temp){
    for (int i=0;i<temp.size();i++){
        for (int j=0;j<temp[i].size();j++){
            cout<<temp[i][j][0]<<" ";
        }
        cout<<endl;
    }
}

void print3dArray(vector<vector<vector<int>>>&temp){
    for (int i=0;i<temp.size();i++){
        printArray(temp[i]);
        cout<<endl;
    }
}

void printMap(unordered_map<int, int>&temp){
    for (const auto&[first,second]:temp){
        cout<<"key "<<first<<"val "<<second<<endl;
    }
}
void printQueue(const std::deque<int>& q) {
    for (int num : q) {
        std::cout << num << " ";
    }
    std::cout << "\n";
}
string convertNumToBinary(int n){
    string theString;
    while (n>0){
        theString+=(n%2==0)?"0":"1";
        n/=2;
    }
    reverse(theString.begin(),theString.end());

    return theString;

}



#include <vector>
#include <numeric>

class Dsu {
private:
    std::vector<int> par;
    std::vector<int> siz;

public:
    Dsu(int n) {
        par.resize(n);
        // Fill par with 0, 1, ..., n-1
        std::iota(par.begin(), par.end(), 0);
        siz.assign(n, 1);
    }

    int get(int x) {
        if (x == par[x]) {
            return x;
        }
        // Path compression
        return par[x] = get(par[x]);
    }

    bool unite(int x, int y) {
        int rootX = get(x);
        int rootY = get(y);

        if (rootX != rootY) {
            // Union by size
            if (siz[rootX] < siz[rootY]) {
                std::swap(rootX, rootY);
            }
            par[rootY] = rootX;
            siz[rootX] += siz[rootY];
            return true;
        }
        return false;
    }

    int getSize(int x) {
        return siz[get(x)];
    }
};
class Fenwick {
    int n;
    vector<long long> bit;

public:
    Fenwick(int size) : n(size), bit(size + 1, 0) {}

    void add(int i, long long delta) {
        for (; i <= n; i += i & -i)
            bit[i] += delta;
    }

    long long prefixSum(int i) {
        long long sum = 0;
        for (; i > 0; i -= i & -i)
            sum += bit[i];
        return sum;
    }

    long long rangeSum(int l, int r) {
        return prefixSum(r) - prefixSum(l - 1);
    }
};

struct PairHash {
    template <typename T1, typename T2>
    std::size_t operator()(const std::pair<T1, T2>& p) const {
        // Fetch the hash values for both elements in the pair
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        // Combine the hashes (using a bit-shift combination to prevent collisions)
        return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
    }
};
struct CompareFirst {
    bool operator()(const std::vector<int>& a, const std::vector<int>& b) const {
        if (a.empty() && b.empty()) return false;
        if (a.empty()) return true;
        if (b.empty()) return false;
        return a < b;
    }
};




signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
    int t;
    cin>>t;
    while(t--){
        int n,m;
        cin>>n>>m;
        string answerString="";
        vector<char>useLess;
        for (int i=0;i<m;i++){
            char temp;
            cin>>temp;
            useLess.push_back(temp);
        }
        for (int i=0;i<n;i++){
            answerString.push_back('_');
        }
        bool verity=false;
        for (int c=0;c<m;c++){
            string guessString;
            for (int i=0;i<n;i++){
                guessString.push_back(useLess[c]);
            }
            cout<<guessString<<endl;
            string result;
            cin>>result;
            if (result=="CORRECT"){
                cout.flush();
                verity=false;
                break;
            }

            for (int i=0;i<n;i++){
                if (answerString[i]=='_'&&result[i]!='_'){
                    answerString[i]=useLess[c];
                }
            }
        }
        if (verity){
            continue;
        }
        string temp;
        cout<<answerString<<endl;
        cin>>temp;
        cout.flush();
    }

}
