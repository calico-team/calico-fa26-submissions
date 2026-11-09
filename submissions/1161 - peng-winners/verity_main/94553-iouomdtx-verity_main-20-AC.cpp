#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <queue>
#include <stack>
#include <set>
#include <algorithm>
#include <bitset>
using namespace std;

typedef long long ll;
#define MOD 1000000007
#define INF ll(2100000000)
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pair<int,int>> vpii;
typedef vector<pair<ll,ll>> vpllll;
typedef vector<string> vs;
typedef pair<int,int> pii;
typedef pair<ll,ll> pllll;
typedef vector<vector<int>> vvi;
typedef vector<vector<vector<int>>> vvvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef deque<int> di;
typedef deque<pii> dpii;
typedef deque<vi> dvi;
typedef vector<vll> vvll;
typedef vector<vpii> vvpii;
typedef vector<vvll> vvvll;
typedef priority_queue<int> pqi;
typedef priority_queue<int,vi,greater<>> pqis;
typedef priority_queue<ll> pqll;
typedef priority_queue<vi> pqvi;
typedef priority_queue<vi,vvi,greater<>> pqvis;
typedef priority_queue<pii> pqpii;
typedef priority_queue<pii,vpii,greater<>> pqpiis;
typedef priority_queue<pllll> pqpllll;
typedef priority_queue<pllll,vpllll,greater<>> pqplllls;
typedef unordered_map<int,int> umii;
typedef unordered_map<int,vi> umivi;
typedef unordered_map<int,vvi> umivvi;
typedef unordered_map<ll,ll> umll;
#define forl(a,b) for (int a=0; a<b; a++)



int main() {
    cin.sync_with_stdio(0); cin.tie(0);

    int t; cin >> t;
    forl(gawjoigjwagw,t) {
        int n,k ; cin >> n >> k;
        vector<char> chars(k); forl(i,k) cin >> chars[i];

        vi out(n,0);
        while (1) {
            vector<char> guess;
            forl(i,n) {
                cout << chars[out[i]];
            }
            cout << '\n' << flush;
            
            string feedback; cin >> feedback;
            if (feedback == "CORRECT") break;
            forl(i,n) {
                if (feedback[i] == '_') out[i]++;
            }
        }    


    }



}