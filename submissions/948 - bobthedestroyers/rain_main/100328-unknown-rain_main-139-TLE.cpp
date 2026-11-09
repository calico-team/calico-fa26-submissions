#include <iostream>
#include <unordered_map>
#include <utility>
#include <set>
#include <vector>

using namespace std;

int main(){
    int n;
    cin>>n;
    
    for(int i=0; i<n; i++){
        int dr,k;
        cin>>dr>>k;
        vector<vector<int>> drone(dr+1, vector<int>(3));
        vector<char> dir(dr+1);
        int x,y,z;
        char d;
        int water=0;
        for(int p=1;p<=dr; p++){
            cin>>x>>y>>z>>d;
                drone[p]={x,y,z};
                dir[p]=d;

            }
        for(int j=1; j<=k; j++){
            set<pair<int,int>>s;
             for(int t=1;t<=dr; t++){
                s.insert({drone[t][0], drone[t][1]});
                if (dir[t]=='E'){
                    drone[t][0]++;
                }
                else{
                    drone[t][1]++;
                }

            }
            water+=s.size();
            



        }
        cout<<water<<endl;

    }

   
    
}