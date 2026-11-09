#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;
    for(int q = 0;q < t;q++){
        int n,r;
        cin >> n >> r;
        vector<int> times;
        for(int w = 0;w < n;w++){
            int x;
            cin >> x;
            times.push_back(x);
        }
        if(n <= 2 || r <= 1){
            cout << "YES" << "\n";
        }else{
            bool comp = true;
            int lives = 1;
            int reD = times[0] + r;
            for(int i = 1;i < n;i++){
                if(times[i] < reD){
                    lives = lives - 1;
                }else{
                    reD = reD + r;
                }
                if(lives < 0){
                    comp = false;
                    break;
                }
            }
            if(comp){
                cout << "YES" << "\n";
            }else{
                cout << "NO" << "\n";
            }
        }
    }
}
	
