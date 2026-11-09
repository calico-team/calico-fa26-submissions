#include <iostream>
#include <vector>
#include<queue>

using namespace std;

void solve(){
    int n;
    long long r;
    cin >> n >> r;
    
    queue<long long> q;
    bool ok =true;
    for (int i = 0 ; i < n; i++){
        long long t;
        cin >> t;
        while (!q.empty () && q.front() <=t){
            q.pop();
        }
    if (q.size () < 2){
        long long finish_time;
        if (q.empty()){
            finish_time = t + r;
        }else{
            finish_time = q.back() + r;
            }
            q.push (finish_time);
    }else{
        ok =false;
    }
}
if (ok){
    cout <<  "YES\n";
}else{
    cout << "NO\n";
    }
}
int main (){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t --){
        solve();
    }
    return 0;
}
            
            
    