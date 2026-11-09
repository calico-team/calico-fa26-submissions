// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int main() {
	int t;
    cin >> t;
    for(int i =0; i< t; i++){
        int n, r;
        cin >> n >> r;
        int time = 0;
        int charges =2;
        int checker = 1;
        int timeholder = 0;
        
        for(int j =0; j < n; j++){
            
            int k;
            cin >> k;
            
            if(charges >=2){timeholder=k; time =0;}
            else{time = k - timeholder ;}
            
            
            charges = charges - 1 + time/r;
            timeholder += r*(time/r);
            
            if(charges >= 2){timeholder=k;}
            if(charges < 0){
                checker =0; 
               
                }
            

            if(charges > 2){charges = 2;}
            time = time - (t/r)*r;
            
            
            
            
        }
        
        if(checker ==1){cout << "YES\n";}
        else{cout<<"NO\n";}


    }
}
