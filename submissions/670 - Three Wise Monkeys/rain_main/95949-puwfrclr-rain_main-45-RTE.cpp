#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef long long ll;
typedef long double ld;
typedef vector<double> vd;
typedef pair<int, int> pii;
typedef pair<pii, int> ppi;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pdd;

template <class T1, class T2>
istream& operator>>(istream& a, pair<T1, T2> &b){
    return (a >> b.first >> b.second);
}

template <class T>
istream& operator>>(istream& a, vector<T> &v){
    for(int i = 0; i < (int)v.size(); i++){
        a >> v[i];
    }
    return a;
}

template <class T1, class T2>
ostream& operator<<(ostream& a, pair<T1, T2> &b){
    return (a << b.first << " " << b.second);
}

template <class T>
ostream& operator<<(ostream& a, vector<T> &v){
    for(int i = 0; i < (int)v.size(); i++){
        a << v[i] << " ";
    }
    return a;
}

struct FT {
    vector<ll> s;
    FT(int n=0) : s(n) {}
    void update(int pos, ll x) { 
        for (; pos < s.size(); pos |= pos + 1) s[pos] += x;
    }
    ll query(int pos) { 
        ll res = 0;
        for (; pos > 0; pos &= pos - 1) res += s[pos-1];
        return res;
    }
    int lower_bound(ll sum) { // min pos s t sum of [0 , pos ] >= sum
        // Returns n i f no sum i s >= sum, or−1 i f empty sum i s .
        if (sum <= 0) return -1;
        int pos = 0;
        for (int pw = 1 << 25; pw; pw >>= 1) {
            if (pos + pw <= s.size() && s[pos + pw-1] < sum)
            pos += pw, sum -= s[pos-1];
        }
        return pos;
    }
};

FT ft;

ll cross(vector<pair<int, pii>> &H, vector<pair<int, pii>> &V){
    vector<pair<int, pii>> ev;
    for(auto p : V){
        int x = p.first;
        int y1 = p.second.first;
        int y2 = p.second.second;
        ev.emplace_back(y1, make_pair(x, 1));
        ev.emplace_back(y2+1, make_pair(x, -1));
    }
    //cout << "EV: " << ev << endl;
    sort(ev.begin(), ev.end());

    ll ans=0;
    sort(H.begin(), H.end());
    int ind=0;
    for(int i = 0; i < H.size(); i++){
        int y = H[i].first;
        int x1 = H[i].second.first;
        int x2 = H[i].second.second;
        while(ind < ev.size() && ev[ind].first <= y){
            //cout << ev[ind] << endl;
            ft.update(ev[ind].second.first, ev[ind].second.second);
            ind++;
        }
        ans += ft.query(x2+1) - ft.query(x1);
    }
    while(ind < ev.size()){
        ft.update(ev[ind].second.first, ev[ind].second.second);
        ind++;
    }
    return ans;
}

void process(){
    int N, T;
    cin >> N >> T;

    map<int, vector<pair<int, pii>>> H;
    map<int, vector<pair<int, pii>>> V;

    ll ans=(ll)N*T;

    for(int i = 0; i < N; i++){
        int x, y;
        cin >> x >> y;
        int z;
        char c;
        cin >> z >> c;
        int ind = x+y;
        if(c == 'E'){
            pair<int, pii> L{y, pii{x, x+T-1}};
            H[ind].push_back(L);
        }
        else{
            pair<int, pii> L{x, pii{y, y+T-1}};
            V[ind].push_back(L);
        }
    }

    for(auto p : H){
        //cout << "H: " << p.first << "\n";
        if(V.count(p.first)) ans -= cross(p.second, V[p.first]);
    }
    cout << ans << "\n";
}

int main(){
    ft = FT(100005);
    cin.tie(0)->sync_with_stdio(0);
    int T=1;
    cin >> T;
    for(int i = 0; i < T; i++){
        process();
    }
       	 
} 

