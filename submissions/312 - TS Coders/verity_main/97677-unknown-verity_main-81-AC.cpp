#include <bits/stdc++.h>
using namespace std;
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);int T;if(!(cin>>T))return 0;while(T--){int n,k;cin>>n>>k;vector<char>a(k);for(char &c:a)cin>>c;string s(n,a[0]);for(int tries=0;tries<k;tries++){cout<<s<<endl;string reply;if(!(cin>>reply))return 0;if(reply=="CORRECT")break;for(int i=0;i<n;i++)if(reply[i]!='_')s[i]=reply[i];else s[i]=a[(tries+1)%k];}}}
