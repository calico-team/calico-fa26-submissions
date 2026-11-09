#include<bits/stdc++.h>
using namespace std;
using std::cout;
#define int long long

void q1() {
    string s; cin>>s;
    for (int i=0; i+8<s.size(); i++) {
        if (s.substr(i, 8)=="write_me") {
            cout<<s<<"make_it_sound_human\n";
            return;
        }
    }
    for (int i=0; i+7<s.size(); i++) {
        if (s.substr(i, 7)=="what_is") {
            cout<<s<<"do_not_hallucinate\n";
            return;
        }
    }
    for (int i=0; i+5<s.size(); i++) {
        if (s.substr(i, 5)=="solve") {
            cout<<s<<"make_no_mistakes\n";
            return;
        }
    }
    cout<<s<<"thank_you\n";
}

void q2() {
    int n,r; cin>>n>>r;
    vector<int> v(n);
    for (int i=0; i<n; i++) cin>>v[i];
    queue<int>q;
    int cnt=2;
    for (int i=0; i<n; i++) {
        if (!q.empty()&&q.front()<=v[i]) {
            cnt++;
            q.pop();
        }
        if (cnt==0) {
            cout<<"NO\n";
            return;
        }
        cnt--;
        if (q.empty()) q.push(v[i]+r);
        else q.push(q.back()+r);
    }
    cout<<"YES\n";
}

signed main() {
    ios::sync_with_stdio(0); 
    cin.tie(0); cout.tie(0);
    int TC=1; cin>>TC;
    while (TC--) q2();
    return 0;
}