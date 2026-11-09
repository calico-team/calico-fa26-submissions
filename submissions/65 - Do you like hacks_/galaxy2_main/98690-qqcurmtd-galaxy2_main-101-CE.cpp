#include<bits/stdc++.h>
#define int long long
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
int ans[200009];
int dst[800009];
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
char ch[59][20009];
array<int,5> qq[200009];
inline int get_id(int x,int y,int cur){
	return x*m+y+cur*n*m;
}
inline bool ok(int x,int y,int cur){
	return ch[x][y]=='.'||(ch[x][y]=='B'&&!cur)||(ch[x][y]=='R'&&cur);
}
inline void bfs(int l,int r,int x,int y,int curr){
	for(int i=1;i<=n;i++)
		for(int j=l;j<=r;j++)	
			for(int k=0;k<2;k++)
				dst[get_id(i,j,k)]=(int)1e18;
	queue<array<int,3> > q;
	q.push({x,y,curr});
	dst[get_id(x,y,curr)]=0;
	while(!q.empty()){
		array<int,3> arr=q.front();
		q.pop();
		if(dst[get_id(arr[0],arr[1],arr[2]^1)]==(int)1e18&&ok(arr[0],arr[1],arr[2]^1)){
			dst[get_id(arr[0],arr[1],arr[2]^1)]=dst[get_id(arr[0],arr[1],arr[2])]+1;
			q.push({arr[0],arr[1],arr[2]^1});
		}
		for(int k=0;k<4;k++){
			int nx=arr[0]+dx[k];
			int ny=arr[1]+dy[k];
			if(nx<=0||nx>n||ny<l||ny>r||!ok(nx,ny,arr[2]))
				continue;
			if(dst[get_id(nx,ny,arr[2])]==(int)1e18){
				dst[get_id(nx,ny,arr[2])]=dst[get_id(arr[0],arr[1],arr[2])]+1;
				q.push({nx,ny,arr[2]});
			}
		}
	}
}
vector<int> vec;
inline void divconq(int l,int r,vector<int> cur){
	if(!cur.size()||l>r)
		return;
	int mid=(l+r)>>1;
	vector<int> lp,rp;
	for(int id:cur){
		if(max(qq[id][1],qq[id][3])<mid)
			lp.push_back(id);
		else if(min(qq[id][1],qq[id][3])>=mid+1)
			rp.push_back(id);
	}
	for(int i=1;i<=n;i++)
		for(int k=0;k<2;k++){
			if(!ok(i,mid,k))
				continue;
			bfs(l,r,i,mid,k);
//			cout<<i<<" "<<mid<<" "<<k<<":"<<endl;
//			for(int ii=1;ii<=n;ii++,cout<<endl)
//				for(int jj=1;jj<=m;jj++)
//					for(int kk=0;kk<2;kk++)
//						cout<<dst[get_id(ii,jj,kk)]<<" ";
			for(int id:cur)
				for(int k2=0;k2<2;k2++)
					ans[id]=min(ans[id],dst[get_id(qq[id][0],qq[id][1],0)]+dst[get_id(qq[id][2],qq[id][3],k2)]);
		}
	divconq(l,mid-1,lp);
	divconq(mid+1,r,rp);
}
int main(){
	T=read();
	while(T--){
		n=read(); m=read(); q=read();
		for(int i=1;i<=n;i++)
			scanf("%s",ch[i]+1);
		for(int i=1;i<=q;i++)
			for(int j=0;j<5;j++)
				qq[i][j]=read();
		for(int i=1;i<=q;i++){
			for(int j=0;j<4;j++)
				qq[i][j]++;
			ans[i]=(int)1e18;
			vec.push_back(i);
		}
		divconq(1,m,vec);
//		for(int i=1;i<=q;i++)
//			cout<<ans[i]<<endl;
		for(int i=1;i<=q;i++)
			printf(ans[i]<=qq[i][4]?"YES\n":"NO\n");
	}
	return 0;
}