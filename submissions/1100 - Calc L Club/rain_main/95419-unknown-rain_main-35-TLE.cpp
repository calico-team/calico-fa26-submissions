
#include <bits/stdc++.h>
using namespace std;
//:p :3 hiii
struct Drone{
    int x, y, z;
    char d;
};
void solve(){
    int n;
    int k;
    cin >> n >> k;
    vector<Drone> ds(n);
    for (int i = 0; i < n; i++){
        cin >> ds[i].x >> ds[i].y >> ds[i].z >> ds[i].d;
    }
    int tot = 0;
    for (int t = 0; t < k; t++){
        set<pair<int, int>> upos;
        for (int i = 0; i < n; i++){
            int cx = ds[i].x;
            int cy = ds[i].y;

            if (ds[i].d == 'N'){
                cy += t;
            }else if (ds[i].d == 'E'){
                cx +=t;
            }
            upos.insert({cx, cy});
        }
        tot += upos.size();
    }
    cout << tot << "\n";
}
int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (cin >> t){
        while(t--){
            solve();
        }
    }
    return 0;
}
