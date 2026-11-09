#include <bits/stdc++.h>
using namespace std;

int main()
{
    int T;
    cin >> T;
    
    for (int caso = 1; caso <= T; caso++)
    {
        int N, R;
        cin >> N;
        cin >> R;
        long long humo1 = 0;
        long long humo2 = 0;
        
        int posible= 1;
        for (int i = 1; i<= N; i++) {
        long long tiempo;
        cin >> tiempo;
        
        if (humo1 > humo2){
            long long aux = humo1;
            humo1 = humo2;
            humo2 = aux;
        }
        if (tiempo < humo1) {
            posible = 0;
        }
         else { humo1 = max(tiempo,humo2) + R;
        }
        }
        if (posible == 1) {
            cout << "YES" << endl;
            
        }
        else { cout << "NO" << endl;
        }

    }   

    return 0;
}