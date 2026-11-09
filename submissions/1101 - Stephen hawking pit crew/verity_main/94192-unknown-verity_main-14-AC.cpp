#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin>>T;
    while(T--) {
        int N, K;
        cin>>N>>K;
        vector<char> chars;
        vector<int> seen(26);
        for(int i=0; i<K; i++) {
            char c;
            cin>>c;
            if(!seen[c-'A']) {
                seen[c-'A']=1;
                chars.push_back(c);
            }
        }
        string ans(N, '?');
        bool done=false;
        for(int id=0; id+1<(int)chars.size(); id++) {
            string guess(N, chars[id]);
            cout<<guess<<endl;
            string res;
            cin>>res;
            if(res=="CORRECT") {
                done=true;
                break;
            }
            for(int i=0; i<N; i++) {
                if(res[i]!='_') {
                    ans[i]=chars[id];
                }
            }
        }
        if(done) continue;
        char last=chars.back();
        for(int i=0; i<N; i++) {
            if(ans[i]=='?') {
                ans[i]=last;
            }
        }
        cout<<ans<<endl;
        string res;
        cin>>res;
        if(res!="CORRECT") {
            return 0;
        }
    }
    return 0;
}