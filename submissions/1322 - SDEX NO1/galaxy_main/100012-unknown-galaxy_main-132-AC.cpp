#include<iostream>
#include<string>
#include<queue>
#include<utility>
using namespace std;
int main(){
    int T;
    cin>>T;
    for(int i=0;i<T;i++){
        int N,M,Q;
        cin>>N>>M>>Q;
        string s[205];
        int a[205][205]={0};
        for(int j=0;j<N;j++){
            cin>>s[j];
        }
        int dx[4]={1,-1,0,0};
        int dy[4]={0,0,1,-1};
        int cnt=0;
        for(int j=0;j<N;j++){
            for(int k=0;k<M;k++){
                if(a[j][k]!=0){
                    continue;
                }
                cnt++;
                queue<pair<int,int>> q;
                q.push({j,k});
                a[j][k]=cnt;
                while(!q.empty()){
                    int x=q.front().first;
                    int y=q.front().second;
                    q.pop();
                    for(int l=0;l<4;l++){
                        int nx=x+dx[l];
                        int ny=y+dy[l];
                        if(nx<0||nx>=N||ny<0||ny>=M){
                            continue;
                        }
                        if(a[nx][ny]!=0){
                            continue;
                        }
                        if(s[x][y]=='R'&&s[nx][ny]=='B'){
                            continue;
                        }
                        if(s[x][y]=='B'&&s[nx][ny]=='R'){
                            continue;
                        }
                        a[nx][ny]=cnt;
                        q.push({nx,ny});
                    }
                }
            }
        }
        for(int j=0;j<Q;j++){
            int x1,y1,x2,y2;
            cin>>x1>>y1>>x2>>y2;
            if(a[x1][y1]==a[x2][y2]){
                cout<<"YES"<<endl;
            }else{
                cout<<"NO"<<endl;
            }
        }
    }
    return 0;
}