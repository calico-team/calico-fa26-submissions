#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define ar array
#define ld long double
#define all(A) A.begin(), A.end()


//const int MOD = 1e9 + 7;
const int MOD = 998244353;
const int N = 1e6 + 50;
const int B = 2;
const int INF = 40;
const int LOG = 20;

void moni();
void vladi();



template<typename T>
void chmin(T &x, T y){x = min(x, y);}

template<typename T>
void chmax(T &x, T y){x = max(x, y);}

template<typename T>
void mm(T &x){
	x %= MOD;
	if(x < 0)x += MOD;
}

signed main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	// vladi();
	int t = 1;
	cin>>t;
	while(t--)moni();
}

void moni(){
	string s;
    cin>>s;
    map<string, string> mp;
    mp["write_me"] = "make_it_sound_human";
    mp["what_is"] = "do_not_hallucinate";
    mp["solve"] = "make_no_mistakes";
    for(int i = 0;i < s.size();i++){
        for(auto [a, b]: mp){
            if(i + a.size() <= s.size() && s.substr(i, a.size()) == a){
                s += b;
                cout<<s<<'\n';
                return;
            }
        }
    }
    cout<<s + "thank_you\n";
}
