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
            int reD1 = times[0] + r;
            int reD2 = -1;
            for(int i = 1;i < n;i++){
                if(reD1 != -1 && times[i] >= reD1){
                    lives = lives + 1;
                    reD1 = -1;
                }
                if(reD2 != -1 && times[i] >= reD2){
                    lives = lives + 1;
                    reD2 = -1;
                }
                if(lives <= 0){
                    comp = false;
                    break;
                }
                lives = lives - 1;
                if(reD1 = -1){
                    reD1 = max(times[i],reD2) + r;
                }else{
                    reD2 = max(times[i],reD1) + r;
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
	
