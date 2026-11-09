#include<bits/stdc++.h>

#define ll long long
#define int long long
#define pii pair<int,int>
#define tiii tuple<int,int,int>

using namespace std;

const int INF = numeric_limits<int>::max()/2; 
struct SegmentTree{
    int len = 1;
    vector<int> S;
    vector<pii> lazy;

    SegmentTree(int n){ 
        while(len < n) len <<= 1;
        S.resize(2*len, 0);
        lazy.resize(2*len, {-1,-1}); 
    } 
    void apply1(int i, int v, int C){   
        if(i >= len){
            int c = i-len;
            int f = v+(2*C*c)-(c*c);
            if(f > 0) S[i] = f;
        }
        lazy[i] = {v,C};
    }
    void push(int i){
        if(lazy[i].first == -1) return;
        apply1(i*2,lazy[i].first,lazy[i].second);
        apply1(i*2+1,lazy[i].first,lazy[i].second);
        lazy[i] = {-1,-1};
    } 
    void update(int ql, int qr, int v, int C, int l = 0, int r = -2, int i = 1){
        if(r == -2) r = len;
        if(ql <= l && r <= qr) {
            apply1(i,v,C);
            return;
        }
        if(r <= ql || qr <= l ) return;
        int mid = (l+r)/2;
        push(i);
        update(ql,qr,v,C,l,mid,i*2);
        update(ql,qr,v,C,mid,r,i*2+1);
        S[i] = max(S[i*2], S[i*2+1]);
    }
    int get(int p, int l = 0, int r = -2, int i = 1){
        if(i >= len) {
            return S[i];
        }
        if(r == -2) r = len;
        int mid = (l+r)/2;
        push(i);
        if(p < mid) return get(p,l,mid,i*2);
        else return get(p,mid,r,i*2+1);
    }
}; 
pii quadratic_solutions(int p, int q){
    int res1 = floor(-p-sqrt((p*p)-q));
    int res2 = ceil(-p+sqrt((p*p)-q));
    return {res1,res2};
}

void solve(){
    int n,m,q;
    cin >> n >> m >> q;

    bool rotated = false;
    if(n > m){
        rotated = true;
        swap(n,m);
    }

    vector<SegmentTree> arr(n, SegmentTree(m));
    
    while(q--){
        int P,C,R;
        cin >>R >> C >> P;
        if(rotated) swap(R,C);
        int base = (P*P)-(R*R)-(C*C)+1;

        pii rangeR = quadratic_solutions(-R,R*R-P*P-1);
        auto eval = [&](int r){
            int res =r*r-2*R*r+(R*R-P*P-1);
            return res;
        };
        while(eval(rangeR.first) < 0) rangeR.first++;
        for(int i = max(0LL,rangeR.first); i <= min(n-1,rangeR.second); i++){
            int adjusted = base-(i*i)+(2*R*i);
            pii range = quadratic_solutions(-C,-adjusted);
            if(range.first >= range.second) continue;
            while(adjusted+(2*C*range.first)-(range.first*range.first) <= 0) {
                range.first++;
            }
            arr[i].update(range.first,range.second,adjusted,C);
        }
    }

    vector<vector<int>> res(n, vector<int>(m));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            res[i][j] = arr[i].get(j);
        }
    }
    if(rotated){
        cout << "\n";
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                cout << res[j][i] << " ";
            }
            cout << "\n";
        }
    } else{
        cout << "\n";
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                cout << res[i][j] << " ";
            }
            cout << "\n";
        }  
    }
    
}
int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        solve();
    }

    //cout << o << endl;
}