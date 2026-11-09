#include<bits/stdc++.h>
//#define int long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
inline int read(){
	int num=0,sign=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')
			sign=-sign;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		num=num*10+(int)ch-48;
		ch=getchar();
	}
	return num*sign;
}
inline void write(int num){
	if(num<0){
		putchar('-');
		num=-num;
	}
	if(num>9)
		write(num/10);
	putchar(num%10+'0');
}
int T;
char ch[209];
string s1="write_me";
string s2="what_is";
string s3="solve";
int main(){
	T=read();
	while(T--){
		scanf("%s",ch+1);
		int n=strlen(ch+1);
		for(int i=1;i<=n;i++)
			cout<<ch[i];
		bool ok1=0;
		int cur=0;
		for(int i=1;i<=n;i++){
			if(ch[i]==s1[cur])
				cur++;
			else
				cur=(ch[i]=='w');
			if(cur==8)
				ok1=1;
		}
		bool ok2=0;
		cur=0;
		for(int i=1;i<=n;i++){
			if(ch[i]==s2[cur])
				cur++;
			else
				cur=(ch[i]=='w');
			if(cur==7)
				ok2=1;
		}
		bool ok3=0;
		cur=0;
		for(int i=1;i<=n;i++){
			if(ch[i]==s3[cur])
				cur++;
			else
				cur=(ch[i]=='s');
			if(cur==5)
				ok3=1;
		}
		if(ok1){
			cout<<"make_it_sound_human"<<endl;
		}
		else if(ok2){
			cout<<"do_not_hallucinate"<<endl;
		}
		else if(ok3){
			cout<<"make_no_mistakes"<<endl;
		}
		else{
			cout<<"thank_you"<<endl;
		}
	}
	return 0;
}