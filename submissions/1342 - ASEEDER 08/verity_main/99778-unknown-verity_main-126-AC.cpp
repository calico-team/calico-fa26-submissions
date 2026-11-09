#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int N, K;
        cin >> N >> K;
        char a[K+105];
        for (int i=0;i<K;i++) cin >> a[i];
        string ans(N, '_');
        for (int i=0;i<K;i++) {
        	char c=a[i];
            string guess=ans;
            for (int i=0;i<N;i++) {
                if (ans[i]=='_') guess[i]=c;
            }
            cout<<guess<<endl;
            string r;
			cin>>r;
            if (r=="CORRECT") break; 
            for (int i=0;i<N;i++) 
                if (r[i]!='_') 
					ans[i]=r[i];
        }
    }
    return 0;
}
