#include<iostream>
#include<algorithm>
#include<string>
#include<cstring>
#include<cmath>
#include<cstdio>
#include<iomanip>
using namespace std;
int T,n,m,k;
struct node{
	int fa;
	int son_n;
	int flg;
	int hasson;
	int llong;
}l1[10086] = {0};



int l1_1[10086][10086] = {0};
struct poin{
	int nod;
	
}l2[10086] = {0};

int asd(int tn){
	int mx = 0;
	for(int i = 1;i<=l1_1[tn][0];i++){
		int t = 0;
		t = asd(l1_1[tn][i]);
		if(t>mx){
			mx = t;
		}
	}
	l1[tn].llong = mx++;
	return l1[tn].llong;
}


bool cmp(poin A,poin B){
	return l1[A.nod].llong>l1[B.nod].llong;
}

void check(int tn){
	cout<<endl;
	for(int i = 1;i<=tn;i++){
		cout<<i<<" "<<l1[i].son_n<<" ";
		for(int j = 1;j<=l1_1[i][0];j++){
			cout<<l1_1[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl; 
}

int main(){
	int tmp;
	cin>>T;
	while(T--){
		cin>>n>>m>>k;
		for(int i = 0;i<=n;i++){
			l1_1[i][0] = 0;
			l1[i].son_n = 0;
			l1[i].llong = 0;
			l1[i].flg = -1;
			l1[i].fa = 0;
			l2[i].nod = 0;
		}
		for(int i = 1;i<=n;i++){
			int t;
			cin>>t;
			if(t == 0){
				l1[i].flg = 0;
				l1[i].fa = t;
				l2[i].nod = i;
			}else{
				
				l1[i].fa = t;
				l1[t].son_n++;
				l2[i].nod = i;
				l1[i].flg = -1;
				l1_1[t][l1_1[t][0]+1] = i;
				l1_1[t][0]++;
			}
				
		}
		
		for(int i = 0;i<n;i++){
			if(l1[i].fa == 0){
				asd(i);
			}
		}
		
		//cout<<endl;
		//check(n);
		sort(l2+1,l2+n+1,cmp);
		int sum = 0;
		for(int j = 1;j<=m;j++){
			int tk = k;
			for(int i = 1;i<=n&&tk>0;i++){
				
				if(l1[l2[i].nod].flg < j&&l1[l2[i].nod].flg!=-1){
					tk--;
					l1[l2[i].nod].flg = -1;
					//cout<<l2[i].nod<<" ";
					sum++;
					for(int idx = 1;idx <= l1_1[l2[i].nod][0];idx++){
						l1[l1_1[l2[i].nod][idx]].flg = j;
					}
				}
			}
			//cout<<endl<<endl;
		}
		cout<<sum<<endl;
		
	}
	
	
	return 0;
}

