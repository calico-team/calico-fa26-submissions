#include <bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        int n,k;
        cin>>n>>k;
        vector<tuple<int,int,int,int>>data;
        for(int i=0;i<n;i++){
            int x,y,z;
            char d;
            cin>>x>>y>>z>>d;
            int endx=x;
            int endy=y;
            if(d=='E'){
                endx=x+k-1;
            }else{
                endy=y+k-1;
            }
            data.emplace_back(x,y,endx,endy);
        }sort(data.begin(),data.end());
        data.erase(unique(data.begin(),data.end()),data.end());
        int overlap=0;
        for(int i=0;i<data.size()-1;i++){
            for(int j=i+1;j<data.size();j++){
                int x1=get<0>(data[i]);
                int y1=get<1>(data[i]);
                int x2=get<2>(data[i]);
                int y2=get<3>(data[i]);
                
                int x3=get<0>(data[j]);
                int y3=get<1>(data[j]);
                int x4=get<2>(data[j]);
                int y4=get<3>(data[j]);
                bool l1horiz=(y1==y2);
                bool l2horiz=(y3==y4);
                if(l1horiz&&l2horiz){
                    if(y1==y3&&x1<=x4&&x3<=x2){
                        overlap++;
                        }    
                }else if(!l1horiz&&!l2horiz){
                        if(x1==x3&&y1<=y4&&y3<=y2){
                            overlap++;
                            }
                    }else if(l1horiz){
                        if(x1<=x3&&x2>=x3&&y3<=y1&&y4>=y1){
                            overlap++;
                            }
                }else{
                    if(x1>=x3&&x4>=x1&&y1<=y3&&y2>=y3){
                            overlap++;
                            }
            }
            }
        }cout<<n*k-overlap<<'\n';
    }
}