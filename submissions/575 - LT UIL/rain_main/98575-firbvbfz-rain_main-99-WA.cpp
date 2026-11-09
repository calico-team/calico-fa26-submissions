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
        set<vector<int>>set;//x y;
        int sum = n*k;
        for(int i = 0; i < n; i++){
            int a, b, c;
            char d;
            cin>>a>>b>>c>>d;
            dronePose[i][0] = a;
            dronePose[i][1] = b;
            dir[i] = d;
        }//difference in their x and y components, then see if that differece is same and less than k
        //x point of the going east one must be smaller than the x of the north one
        //y point of the going north must be smalelr than the y of the east one
        char first = dir[0];
        for(int i = 0; i < n-1; i++){
            if(dir[i] == first){//target one matches the first.  east
                for(int j = i+1; j < n; j++){
                    // cout<< dronePose[i][0]<<' ' <<dronePose[i][1]<<endl;
                    if(dir[j] == first){
                        continue;//same velocity
                    }
                    // cout<< dronePose[i][0]<<' ' <<dronePose[i][1]<<endl;
                    if(first == 'E'){//j == going north, i = east
                        int x_diff = dronePose[j][0] - dronePose[i][0];
                        if(x_diff < 0 ){
                            break;
                        }else{
                            // cout<<x_diff<<endl;//2
                            // cout<<dronePose[i][1] - dronePose[j][1]<<endl;
                            
                            if(x_diff > k-1 || (dronePose[i][1] - dronePose[j][1] != x_diff)){
                                break;
                            }else{
                                // cout<<dronePose[j][0]<<' ' <<dronePose[j][1]<<"--" << dronePose[i][0]<<' ' <<dronePose[i][1]<<endl;
                                sum--;
                            }
                        }
                    }else{//i == going north, j = east
                        int x_diff = dronePose[i][0] - dronePose[j][0];
                        if(x_diff < 0 ){
                            break;
                        }else{
                            if(x_diff > k-1 || (dronePose[j][1] - dronePose[i][1] != x_diff)){
                                break;
                            }else{
                                sum--;
                            }
                        }
                    }
                }
            }else{
                continue;
            }
        }
        // cout<<set.size()+n<<endl;;
        cout<<sum<<endl;
    }


}


//if they intersect, their horizontal and vertical parts must be equal in the beginning
