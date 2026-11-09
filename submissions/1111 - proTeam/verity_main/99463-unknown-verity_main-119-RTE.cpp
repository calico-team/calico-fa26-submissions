#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int t;

    cin >>t;

    for (int i = 0; i<t; i++){
        int n, k, x = 0;
        string result;
        bool correct = false;
        cin >>n >>k;

        string a[k], guess[n];

        for (int j = 0; j < k; j++){
            cin >>a[j];
        }


        for (int b = 0; b < n; b++){
            guess[b] = a[0];
        }


        while(!correct){
            x++;
            for (int l = 0; l < n; l++){
                cout << guess[l];
            }
            cout <<endl;
            cin >>result;

            for (int l = 0; l < n; l++){
                if (result[l] == '_'){
                    guess[l] = a[x];
                }

                if (result.compare("CORRECT") == 0){
                    correct = true;

                }
            }

        }


    }
    return 0;
}
