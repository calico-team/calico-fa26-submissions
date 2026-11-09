#include <bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        int n,k;
        cin>>n>>k;
        int maxx=0;
        int maxy=0;
        int maxz=0;
        vector<tuple<int,int,int,char>>data;
        for(int i=0;i<n;i++){
            int x,y,z;
            char d;
            cin>>x>>y>>z>>d;
            maxx=max(x,maxx);
            maxy=max(y,maxy);
            maxz=max(z,maxz);
            data.emplace_back(x,y,z,d);
        }vector<vector<int>> grid(maxy+k+5,vector<int>(maxx+k+5,0));
            for(int c=0;c<n;c++){
                for(int b=0;b<k;b++){
                    grid[get<1>(data[c])][get<0>(data[c])]=1;
                    if(get<3>(data[c])=='E'){
                        get<0>(data[c])+=1;
                    }else{
                        get<1>(data[c])+=1;
                    }
                }
            }int total=0;
            for(int p=0;p<maxy+k+5;p++){
                for(int q=0;q<maxx+k+5;q++){
                    if(grid[p][q]==1){
                        total++;
                    }
                }
            }cout<<total<<'\n';
    }
}