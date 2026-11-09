#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    for(int q = 0;q < t;q++){
        int n,r;
        cin >> n >> r;
        if(n <= 2 or r <= 1){
            cout << "YES";
        }else{
            vector<int> times;
            for(int w = 0;w < n;w++){
                int x;
                cin >> x;
                times.push_back(x);
            }
            int lives = 0;
            int lr = 0;
            if((times[1] - times[0]) >= r){
                lives = lives + ((times[1] - times[0]) / r);
                lr = times[1];
            }
            bool finished = true;
            for(int i = 2;i < n;i++){
                int time = times[i];
                if(i == 2 && lr == 0){
                    if((time - times[1]) < r && (time - times[0]) < r){
                        finished = false;
                        break;
                    }else{
                        lr = time;
                    }
                }else{
                    if(lives > 0){
                        lives = lives - 1;
                        if((time - lr) > r){
                            lives = lives + 1;
                        }
                    }else{
                        if((time - lr) < r){
                            finished = false;
                            break;
                        }else{
                            lr = time;
                        }
                    }
                }
            }
            if(finished){
                cout << "YES" << "\n";
            }else{
                cout << "NO" << "\n";
            }
        }
    }
	
}
