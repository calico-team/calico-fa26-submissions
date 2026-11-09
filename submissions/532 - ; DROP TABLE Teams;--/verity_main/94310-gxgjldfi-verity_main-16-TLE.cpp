#include <iostream>
#include <vector>

using namespace std;

int main(){
    int t;
    cin >> t;
    while (t--){
        int n, k;
        cin >> n >> k;
        vector<string> chars(k);
        for (int i = 0; i < k; i++) cin >> chars[i];
        string s;
        for (int i = 0; i < n; i++) s += ' ';
        bool endearly = false;
        for (int i = 0; i < k; i++){
            string guess;
            for (int j = 0; j < n; j++){
                guess += chars[i];
            }
            cout << guess << endl;
            cout.flush();
            string ret;
            cin >> ret;
            if (ret == "CORRECT"){ endearly = true; break;}
            for (int j = 0; j < n; j++){
                if (ret[j] != '_') s[j] = ret[j];
            }
        }
        if (!endearly){
            string aa;
            cin >> aa;
            cout << s << endl;
            cout.flush();
        }
    }
}