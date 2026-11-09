#include <iostream> //g++ -std=c++20 Usaco/main.cpp -o Usaco/ryan.out && Usaco/ryan.out
#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include<map>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
using namespace std;
using ll = long long;//woah
//    vector<vector<int>> a(3, vector<int>(3));
#include <tuple>


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream fin("Usaco/temporary.in");//temporary
    ofstream fout("Usaco/temporary.out"); 
    int t;
    cin>>t;
    while(t--){
        int n, k;
        cin>>n>>k;//number of drones(rows) and k - number of nights
        vector<vector<int>> dronePose(n, vector<int>(2));
        vector<char>dir(n);
        int sum = n*k;
        int dummy = 0;
        for(int i = 0; i < n; i++){
            cin>>dronePose[i][0]>> dronePose[i][1]>> dummy>>dir[i];
        }//difference in their x and y components, then see if that differece is same and less than k
        //x point of the going east one must be smaller than the x of the north one
        //y point of the going north must be smalelr than the y of the east one
        // char first = dir[0];
        int count = 0;
        for(int i = 0; i < n; i++){
            for(int j = i + 1;j < n; j++){
                // cout<<"check";
                int eastIndex, northIndex;
                // cout<<dir[i] <<' ' <<dir[j]<<endl;
                if(dir[i] == 'E' && dir[j] == 'N'){
                    eastIndex = i;
                    northIndex = j;
                }else if(dir[j] == 'E' && dir[i] == 'N' ){
                    eastIndex = j;
                    northIndex = i;
                }else{
                    continue;
                }
                // cout<<"check";
                int northX = dronePose[northIndex][0];
                int eastX = dronePose[eastIndex][0];
                int northY = dronePose[northIndex][1];
                int eastY = dronePose[eastIndex][1];

                if(eastX <= northX && northY <= eastY){
                    int timeX = abs(eastX - northX);
                    int timeY = abs(eastY - northY);
                    
                    // cout<<timeX<<' ' <<timeY<<endl;
                    if(timeX == timeY && timeX <= k-1)
                        count++;
                }
                
            }
        }
        cout<<sum-count<<endl;
    }
}