#include <iostream>
#include <queue>
int main(){
    using namespace std;
    int T;
    cin>>T;
    while(T--){
        int n,m,Q;
        cin>>n>>m>>Q;
        char grid[203][203]={};
        int region[203][203]={};
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                cin>>grid[i][j];
            }
        }
        queue<pair<int,int> > q;
        pair<int,int> pos;
        pair<int,int> moves[4]={make_pair(0,1),make_pair(0,-1),make_pair(1,0),make_pair(-1,0)};
        int regioncnt=1;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(region[i][j]!=0) continue;
                q.push(make_pair(i,j));
                region[i][j]=regioncnt;
                //cout<<regioncnt<<endl;
                while(!q.empty()){
                    pos=q.front();
                    q.pop();
                    for(pair<int,int> move:moves){
                        int x=pos.first+move.first;
                        int y=pos.second+move.second;
                        if(x>=n||x<0 || y>=m || y<0) continue;
                        if((grid[pos.first][pos.second]==grid[x][y]|| grid[pos.first][pos.second]=='.' ||grid[x][y]=='.')&&region[x][y]==0){
                            q.push(make_pair(x,y));
                            region[x][y]=regioncnt;
                            //cout<<regioncnt<<endl;
                        }
                    }
                }
                regioncnt+=1;
            }
        }
        while(Q--){
            int xs,ys,xe,ye;
            cin>>xs>>ys>>xe>>ye;
            if(region[xs][ys]==region[xe][ye]){
                cout<<"YES\n";
            }
            else{
                cout<<"NO\n";
            }
        }
    }
    
}