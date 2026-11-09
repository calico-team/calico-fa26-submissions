//  CALICO Fall 26
//  Fatespeaker
//  11/8/26

#include<bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp> //comment out for trie
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

using namespace std;


mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

using str = string;
using ll = long long;
using lls = unsigned long long;
using i128 = __int128;
using vi = vector<int>;
using gi = vector<vector<int>>;
using vll = vector<long long>;
using vs = vector<string>;
using pii = pair<ll, ll>;
using pll = pair<ll,ll>;
using vvi = vector<vector<int>>;
using vvll=vector<vector<ll>>;
using ull=unsigned long long;
using vd = vector<double>;
using dbl = long double;
using vlls = vector<lls>;
using pdd = pair<double, double>;
using pldld = pair<long double, long double>;
#define f first
#define s second
#define iset(T) tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>
#define cont continue
#define br break
#define ret return
#define pb push_back
#define pob pop_back
#define ins insert
#define dec(PRESICION) fixed << setprecision(PRESICION)
#define gcd __gcd
#define lcm(a, b) ((a) * (b) / gcd(a, b))
#define iceil(a, b) (((a) + (b) - 1) / (b))
#define even(x) (((x) & 1) == 0)
#define odd(x) (((x) & 1) == 1)
#define set_bit(x, i) ((x)|(1LL<<(i)))
#define clear_bit(x, i) ((x)&(~(1LL<<(i))))
#define toggle_bit(x, i) ((x)^(1LL<<(i)))
#define bit_val(x, i) (((x) >> (i)) & 1)
#define popcount(x) __builtin_popcountll(x)
#define trailing_zeros(x) __builtin_ctzll(x)
#define leading_zeros(x) __builtin_clzll(x)
#define sp <<' '<<
#define rnd(A, B) uniform_int_distribution<int>(A, B)(rng)
#define tc int TESTCASES; cin >> TESTCASES; while(TESTCASES--)
#define io ios_base::sync_with_stdio(false); cin.tie(nullptr)
#define fio(IN, OUT) ifstream fin(IN); ofstream fout(OUT)
#define forl(LIMIT) for (int i = 0; i < LIMIT; i++)
#define jforl(LIMIT) for (int j = 0; j < LIMIT; j++)
#define rforl(LIMIT) for (int i = LIMIT; i >= 0; i--)
#define yn(YNFLAG) if (YNFLAG) cout << "YES\n"; else cout << "NO\n"
#define int long long

struct ch {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};



int dr[] = {1, 0, -1, 0};
int dc[] = {0, 1, 0, -1};
int dx[] = {1, 1, 1};
int dy[] = {-1, 0, 1};
ll mod = 1000000007;
long double pi = 3.141592653589793238462643383279502884;


signed main() {
    io;
    tc{
        int n, k; cin>>n>>k;
        --k;
        map<int,set<pii>> rtc; //r, c
        map<int, set<pii>> ctr;
        map<int, int> sp1;
        ll r=0;
        vector<pii> q,q2;
        forl(n){
            int a, b, c; char d;
            cin>>a>>b>>c>>d;
            if (d=='E'){
                rtc[b].ins({a, 1});
                rtc[b].ins({a+k, -1});
                sp1[a+b]++;
                q.push_back({a, b});
            }else{
                ctr[a].ins({b, 1});
                ctr[a].ins({b+k, -1});
                q2.push_back({b, a});
            }
        }
        sort(q.begin(), q.end());
        sort(q2.begin(), q2.end());
        r=n*(k+1);
        map<int, vi> po;
        forl(q2.size()){
            if (!po[q2[i].f+q2[i].s].size())po[q2[i].f+q2[i].s].pb(-67676767);
            po[q2[i].f+q2[i].s].pb(q2[i].s);
        }
        for (auto it=po.begin(); it!=po.end(); it++)sort(it->s.begin(), it->s.end());
        forl(q.size()){
            auto lb=lower_bound(po[q[i].f+q[i].s].begin(), po[q[i].f+q[i].s].end(), q[i].f);
            lb--;
            r-=prev(upper_bound(po[q[i].f+q[i].s].begin(), po[q[i].f+q[i].s].end(), q[i].f+k))-lb;
        }
        cout<<r<<'\n';

    }

    ret 0;
}

