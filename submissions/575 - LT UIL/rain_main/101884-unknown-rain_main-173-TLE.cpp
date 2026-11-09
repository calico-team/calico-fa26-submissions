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
    long long t;
    cin>>t;
    while(t--){
        long long n, k;
        cin>>n>>k;//number of drones(rows) and k - number of nights
        vector<vector<long long>> dronePose(n, vector<long long>(2));
        vector<char>dir(n);
        long long sum = n*k;
        long long dummy = 0;
        for(int i = 0; i < n; i++){
            cin>>dronePose[i][0]>> dronePose[i][1]>> dummy>>dir[i];
        }//difference in their x and y components, then see if that differece is same and less than k
        //x point of the going east one must be smaller than the x of the north one
        //y point of the going north must be smalelr than the y of the east one
        // char first = dir[0];
        long long count = 0;
        for(int i = 0; i < n; i++){
            for(int j = i + 1;j < n; j++){
                // cout<<"check";
                long long eastIndex, northIndex;
                // cout<<dir[i] <<' ' <<dir[j]<<endl;
                if(dir[i] == dir[j]){
                    continue;
                }
                if(dir[i] == 'E' && dir[j] == 'N'){
                    eastIndex = i;
                    northIndex = j;
                }else if(dir[j] == 'E' && dir[i] == 'N' ){
                    eastIndex = j;
                    northIndex = i;
                }
                // cout<<"check";
                long long northX = dronePose[northIndex][0];
                long long eastX = dronePose[eastIndex][0];
                long long northY = dronePose[northIndex][1];
                long long eastY = dronePose[eastIndex][1];

                if(eastX <= northX && northY <= eastY){
                    long long timeX = abs(eastX - northX);
                    long long timeY = abs(eastY - northY);
                    
                    // cout<<timeX<<' ' <<timeY<<endl;
                    if(timeX == timeY && timeX <= k-1)
                        count++;
                }
                
            }
        }
        cout<<sum-count<<endl;
    }
}