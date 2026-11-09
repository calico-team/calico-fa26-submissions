#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

void solve(){
    int n, k;
    cin >> n >> k;
    vector<char> useable(k);
    for(int i = 0; i < k; i++) cin >> useable[i];
    vector<char> build(n);

    // for(auto i : useable) cerr << i;

    for(int i = 0; i < k; i++){
        string ns = "";
        for(int j = 0; j < n; j++) ns.push_back(useable[i]);
        cout << ns << endl;
        string inp;
        cin >> inp;
        for(int j = 0; j < n; j++){
            if(inp[j] != '_') build[j] = useable[i];
        }
    }

    for(char i : build) cout << i;
    cout << endl;
    string inp;
    cin >> inp;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) solve();
    return 0;
}