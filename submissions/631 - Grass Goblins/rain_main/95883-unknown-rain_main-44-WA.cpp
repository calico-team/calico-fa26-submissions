#include<bits/stdc++.h>

#define ll long long
#define pii pair<int,int>
#define tiii tuple<int,int,int>

using namespace std;

string o; 

bool done = false;

string query(string s){
    cout << s << endl;
    string r;
    cin >> r;
    if(r == "CORRECT") done = true;
    return r;
}

void solve(){
    done = false;
    int n,m;
    cin >> n >> m;
    vector<char> possible(m);
    string ans;
    for(int i = 0; i < n; i++) ans +='#';

    for(int i = 0; i < m; i++) cin >> possible[i];
    for(int i = 0; i < m; i++){
        string q = "";
        for(int j = 0; j < n; j++){
            q += possible[i];
        }
        string res = query(q);
        if(done) return;
        for(int j = 0; j < n; j++){
            if(res[j] != '_') ans[j] = possible[i];
        }
    }
    query(ans);
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }

    //cout << o << endl;
}