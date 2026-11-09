#include <iostream>
#include <string>
using namespace std;

int main(){
    int t;
    cin >> t;

    for (int k = 0; k < t; k++){
        int n, m;
        cin >> n >> m;

        string letras = "";

        for (int i = 0; i < m; i++){
            char x;
            cin >> x;
            letras += x;
        }

        string fija(n, '?');

        for (int j = 0; j < m; j++){
            string s = fija;

            for (int i = 0; i < n; i++){
                if (fija[i] == '?'){
                    s[i] = letras[j];
                }
            }

            cout << s << endl;

            string resp;
            cin >> resp;

            if (resp == "CORRECT"){
                break;
            }

            for (int i = 0; i < n; i++){
                if (resp[i] != '_') {
                    fija[i] = resp[i];
                }
            }
        }
    }
    return 0;
}