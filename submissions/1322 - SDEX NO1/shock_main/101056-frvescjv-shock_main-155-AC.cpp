#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
int main(){
    int T;
    cin>>T;
    for(int i=0;i<T;i++){
        int N,M,Q;
        cin>>N>>M>>Q;
        vector<int> R(Q),C(Q),P(Q);
        for(int j=0;j<Q;j++){
            cin>>R[j]>>C[j]>>P[j];
        }
        vector<vector<int>> a(N,vector<int>(M,0));
        vector<vector<int>> fa(N,vector<int>(M+1));

        for(int j=0;j<N;j++){
            for(int k=0;k<=M;k++){
                fa[j][k]=k;
            }
        }
        for(int j=Q-1;j>=0;j--){
            int p=P[j];
            for(int r=R[j]-p;r<=R[j]+p;r++){
                int dr=r-R[j];
                int s=p*p-dr*dr;
                int d=sqrt(s);

                while((d+1)*(d+1)<=s){
                    d++;
                }
                while(d*d>s){
                    d--;
                }

                int c=C[j]-d;
                int right=C[j]+d;

                while(c<=right){
                    int k=c;
                    while(fa[r][k]!=k){
                        k=fa[r][k];
                    }

                    while(c!=k){
                        int temp=fa[r][c];
                        fa[r][c]=k;
                        c=temp;
                    }

                    if(c>right){
                        break;
                    }

                    int dc=c-C[j];
                    a[r][c]=s-dc*dc+1;
                    fa[r][c]=c+1;
                    c++;
                }
            }
        }

        for(int j=0;j<N;j++){
            for(int k=0;k<M;k++){
                if(k>0){
                    cout<<" ";
                }
                cout<<a[j][k];
            }
            cout<<endl;
        }
    }
    return 0;
}