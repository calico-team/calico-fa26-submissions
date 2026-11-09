#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <cstring>
#include <queue>
#include <set>
#include <unordered_set>
using namespace std;
typedef pair<int, int> pi;
typedef pair<string, string> ps;
typedef pair<pi, char> pic;
typedef pair<char, char> pc;
#define endl "\n"
#define int long long
const int MOD = 1e9 + 7;
const int HASH = 197;
const int MM = 3e5 + 5;
const int MV = 1e6 + 5;
bool arr[MM];
signed main() {
    ios_base::sync_with_stdio(false); cin.tie();
    int qwr; cin >> qwr;
    for (int diu = 1; diu <= qwr; diu++) {
        memset(arr, false, sizeof(bool) * MM);
        int N, R; cin >> N >> R;
        for (int i = 1; i <= N; i++) {
            int x; cin >> x; arr[x] = true;
        }
        int s = 2; int t = 0, lastR = 0, cnt = 0;
        while (s >= 0 && t < MM) {
            if (s != 2 && t - lastR >= R) {s++; lastR = t;}
            t++;
            if (arr[t] && t < MM){ s--; cnt++;}
        }
        if (cnt != N || s < 0) cout<<"NO"<<endl;
        else cout<<"YES"<<endl;
    }
}