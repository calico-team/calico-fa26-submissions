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

    // after we remove all the redundant drones, there will only ever be 2 drones on a single tile at once
    // then we need to count the number of times a drone is on the same tile as another drone
    // this will only happen between one n drone and one e drone
    // we can assign a spaceid to every drone: x + y

    // all e drones will die i times where i is the num of n drones with the spaceid of the e drone

    // but how do we account for collisions that will happen later than the first k days

    // 

    int t; cin >> t;
    forl(gawjoigjwagw,t) {
        ll n,k; cin >> n >> k;
        vector<set<int>> east(1e5+1), north(1e5+1);

        // set<pllll> north; 
        forl(i,n) {
            int x,y,z; char d; cin >> x >> y >> z >> d;
            if (d == 'N') {
                north[x].insert(y);
            } else east[x].insert(y);
        }

        vvpii events(1e5+1);
        forl(i,1e5+1) {
            for (auto a: east[i]) {
                events[i].push_back({a+i,1});
                if (i+k <= 1e5) {
                    events[i+k].push_back({a+i,-1});
                }
            }
        }

        vi count(2e5+1,0);

        ll out = n*k;
        forl(i,1e5+1) {
            for (auto[a,b]: events[i]) {
                count[a] += b;
            }

            // if there is a north drone on this x value, see how many east drones it will intersect with
            for (auto a: north[i]) {
                out -= count[i+a];
                // cout << i << '\n';
                // cout << "subtract: " << count[i+a] << '\n';
            }

        }

        cout << out << '\n';


    }



}