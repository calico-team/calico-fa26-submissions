#include <bits/stdc++.h>

using namespace std;

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    int T;
    cin >> T;
    while(T--){
        int N, K;
        cin >> N >> K;
        string S(N, ' ');
        string G(N, ' ');
        set<char> letters;
        for(int i = 0; i < N; i++){
            char L;
            cin >> L;
            letters.insert(L);
        }
        for(char L : letters){
            G = string(N, L);
            cout << G << endl;
            string feedback;
            cin >> feedback;
            for(int i = 0; i < feedback.size(); i++){
                if(feedback[i] != '_'){
                    S[i] = feedback[i];
                }
            }
        }
        cout << G << endl;
        cin >> G;
    }
}