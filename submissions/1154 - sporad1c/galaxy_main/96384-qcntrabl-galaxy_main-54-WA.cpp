#include<bits/stdc++.h>
using namespace std;
int n,m,q; 
char a[10000][10000];
int b[10000000];

int zuzong(int k){
    if(b[k]==k)return k;
    else return b[k] = zuzong(b[k]); 
}

int main(){
    int t; 
    cin >> t; 
    while(t--) {
        cin>>n>>m>>q;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                cin>>a[i][j];
            }
        }
        
        while(q--) {
            int stx,sty,enx,eny;
            cin>>stx>>sty>>enx>>eny;
            stx++; sty++; enx++; eny++;
            for(int i=1;i<=n;i++){
                for(int j=1;j<=m;j++){
                    b[(i-1)*m+j]=(i-1)*m+j;
                }
            }
            
            for(int i=1;i<=n;i++){
                for(int j=1;j<=m;j++){
				    if(i > 1 && (a[i][j]==a[i+1][j]||a[i-1][j]==a[stx][sty])){
                        b[zuzong((i-1)*m+j)]=zuzong((i-2)*m+j);
                    }
                    if(j < m && (a[i][j]==a[i][j+1]||a[i][j+1]==a[stx][sty])){
                        b[zuzong((i-1)*m+j+1)]=zuzong((i-1)*m+j);
                    }
                }
            }
        
            int startnum = (stx - 1) * m + sty;
            int endnum = (enx - 1) * m + eny;
            
            if(zuzong(startnum) == zuzong(endnum)){
                cout << "YES"<<endl;
            } 
            else {
                cout << "NO"<<endl;
            }
        }
    }
    return 0;
}
