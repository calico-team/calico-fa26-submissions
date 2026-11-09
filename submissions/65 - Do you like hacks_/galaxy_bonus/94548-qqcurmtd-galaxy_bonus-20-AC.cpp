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
int n,m,q;
int fa[200009];
char ch[509][509];
inline int get_id(int x,int y){
	return x*m+y;
}
inline int find_dsu(int u){
	return u==fa[u]?u:fa[u]=find_dsu(fa[u]);
}
inline void merge_dsu(int u,int v){
	u=find_dsu(u); v=find_dsu(v);
	if(u==v)
		return;
	fa[v]=u;
	return;
}
int main(){
	T=read();
	while(T--){
		n=read(); m=read(); q=read();
		for(int i=1;i<=n;i++)
			scanf("%s",ch[i]+1);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				fa[get_id(i,j)]=get_id(i,j);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
				if(i!=n)
					if(!(ch[i][j]!=ch[i+1][j]&&ch[i][j]!='.'&&ch[i+1][j]!='.'))
						merge_dsu(get_id(i,j),get_id(i+1,j));
				if(j!=m)
					if(!(ch[i][j]!=ch[i][j+1]&&ch[i][j]!='.'&&ch[i][j+1]!='.'))
						merge_dsu(get_id(i,j),get_id(i,j+1));
			}
		while(q--){
			int x1,y1,x2,y2;
			x1=read(); y1=read(); x2=read(); y2=read();
			x1++; y1++; x2++; y2++;
			printf(find_dsu(get_id(x1,y1))==find_dsu(get_id(x2,y2))?"YES\n":"NO\n");
		}
	}
	return 0;
}