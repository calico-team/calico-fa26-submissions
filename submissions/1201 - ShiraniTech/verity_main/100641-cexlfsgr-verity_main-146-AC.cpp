#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
int  main(){
int T;
cin>>T;
while(T--){
int n, k;
cin>>n>>k;
vector<char> a(k);
  for(auto& c: a) cin>>c;
  string known(n, '_');
  for(int t=0;; t++){
  	char c=a[min(t, k-1)];
  	string guess=known;
  	for(char& x: guess)
  	if(x=='_') x=c;
  	cout<<guess<<endl;
  	string reply;
  	cin>>reply;
  	if(reply=="CORRECT") break;
  	for(int i=0; i<n; i++)
  	if(reply[i]!='_') known[i]=reply[i];
  }
}
  return 0;
}