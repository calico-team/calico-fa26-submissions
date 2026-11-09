#include <iostream>
#include <string>
using namespace std;

int main(){
    int t;
    cin >> t;
    for(int i = 0;i < t;i++){
        int n;
        string guess;
        string judge_in;
        int k;
        bool flag = 0;
        cin >> n >> k;
        char a[26];
        char correct_letters[100];
        for(int j = 0;j < n;j++){
            correct_letters[j] = ' ';
        }
        for(int j = 0;j < k;j++){
            cin >> a[j];
        }
        for(int j = 0;j < k;j++){
            guess = "";
            for(int l = 0;l < n;l++){
                guess.push_back(a[j]);
            }
            cout << guess << endl;
            cin >> judge_in;
            if(judge_in == "CORRECT"){
                flag = 1;
                break;
            }
            for(int l = 0;l < n;l++){
                if(judge_in[l] != '_'){
                    correct_letters[l] = judge_in[l];
                }
            }
        }
        if(flag == 0){
            for(int j = 0;j < n;j++){
                cout << correct_letters[j];
            }
            cin >> judge_in;
        }
    }
    return 0;
}