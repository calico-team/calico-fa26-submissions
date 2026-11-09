#include <bits/stdc++.h>
using namespace std;
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);int T;cin>>T;while(T--){int n;cin>>n;vector<unsigned>L(n),R(n);for(auto &x:L)cin>>x;for(auto &x:R)cin>>x;unsigned ans=0;for(int b=29;b>=0;b--){unsigned bit=1u<<b;bool possible=false;for(int mask=0;mask<2;mask++){unsigned x=0;for(int i=0;i<n;i++){unsigned val=(R[i]>=bit?R[i]:L[i]);if(((val>>b)&1)!=mask)val=L[i];x^=val;}if((x&bit)!=0)possible=true;}if(possible)ans|=bit;} // Exact endpoint choices provide a valid lower bound.
unsigned cur=0;for(int i=0;i<n;i++)cur^=R[i];ans=max(ans,cur);cout<<ans<<'\n';}}
