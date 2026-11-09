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

int n,m,k;
vi pre;
vvi matrix;
vi pot;


int dfs(int a, int currdepth) {
    if (currdepth > m) return 0;
    
    for (auto b: matrix[a]) {
        pot[a] += dfs(b, currdepth+1);
    }
    return pot[a]+1;
}


int main() {
    cin.sync_with_stdio(0); cin.tie(0);

    // can you js take any 

    // wait cuz every course has indegree 1 or 0 so
    // but it can have a high outdegree

    // so if you had 2 semesters

    // ok so first step is cut off all classes that are too deep to ever take
    // and it might be optimal to just prioritize the classes with the highest amount of total POTENTIAL

    // cuz if something has positive potential then it will always be replaced by at least 1 node
    // 


    int t; cin >> t;
    forl(gawjoigjwagw,t) {
        cin >> n >> m >> k;
        pre = vi(n+1); pot = vi(n+1,0); matrix = vvi(n+1);
        forl(i,n) {
            cin >> pre[i+1];
            matrix[pre[i+1]].push_back(i+1);
        }

        dfs(0,0); 

        int out = 0;
        set<pii,greater<>> classes;
        for (int i=1; i<=n; i++) {
            // cout << i << ' ' << pot[i] << '\n';
            if (pre[i] == 0) classes.insert({pot[i], i});
        }
        vpii nex;

        // cout << '\n';
        // for (auto[a,b]: classes) cout << a << ' ' << b << '\n';
        // cout << '\n';
            
        forl(i,m) {
            // cout << "sem" << i << '\n';
            // for (auto[a,b]: classes) cout << a << ' ' << b << '\n'; 
            forl(j,k) {
                if (classes.size() > 0) {
                    // cout << "class slot" << j << '\n';
                    out++;
                    int curr = (*classes.begin()).second;
                    classes.erase(classes.begin());
                    // cout << "choose class " << curr << '\n';
                    for (auto b: matrix[curr]) {
                        // cout << b << '\n';
                        nex.push_back({pot[b], b});
                    }
                } else {
                    break;
                }
            }
            for (auto[a,b]: nex) classes.insert({a,b});
            nex.clear();
            if (classes.size() == 0) break;
        }

        cout << out << '\n';


    }



}