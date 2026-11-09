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
        // vector<vector<int>> dronePose(n, vector<int>(3));
        vector<char>dir(n);
        set<vector<int>>set;//x y;
        for(int i = 0; i < n; i++){
            int a, b, c;
            char d;
            cin>>a>>b>>c>>d;
            // dronePose[i][0]=a;
            // dronePose[i][1]=b;
            // dronePose[i][2]=c;
            // dir[i] = d;
            // set.insert({a,b});
            for(int j = 2; j <= k; j++){
                if(d == 'N'){
                    set.insert({a, b+j-1, j});
                    
                }else{//east
                    set.insert({a+j-1, b, j});
                    // cout<< a+j-1<<' '<<b<<' '<<j<<endl;
                }
            }

        }

        // for(const auto& c : set){
        //     cout<< c[0]<<' '<<c[1]<<' '<<c[2]<<' '<<endl;
        //     // cout<<"woah"<<c.;
        // }
        cout<<set.size()+n<<endl;;
        //check each east one with every north one
        //

        /*
        // 0 3 1
        1 3 2
        2 3 3

        // 2 1 1
        2 2 2
        2 3 3

        // 8 8 1
        9 8 2
        10 8 3
        */

        // for(int i = 0; i < n; i++){
//cout<<dronePose[i][0] << ' ' << dronePose[i][1] << ' ' << dronePose[i][2] << ' ' << dir[i]<<endl;
        // }

        

    }


}
