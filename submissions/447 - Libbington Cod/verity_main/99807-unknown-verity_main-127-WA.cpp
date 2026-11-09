#include <iostream>
#include <vector>
using namespace std;

/*
 * Print a sequence of guesses until you guess the answer string.
 * You may use the read_string() and print_guess() helper functions defined below.
 *
 * N: Length of the string
 * K: Number of different -ities
 * A: List containing the different -ities
 */


/*
 * Reads a single string from standard input.
 */
string read_string() {
    string s; cin >> s;
    return s;
}

/*
 * Prints a guess to standard output and flushes the output stream buffer.
 */
string print_guess(string guess) {
    cout << guess << endl;
}

vector<char> outputToVec(){
    string s=read_string();
    vector<char> v(s.length());
    for(int i=0;i<s.length();i++){
        v[i]=s[i];
    }
    return v;
}

string vecToOutput(vector<char> v){
    string s="";
    for(int i=0;i<v.size();i++){
        s+=v[i];
    }
    return print_guess(s);
}

void fillVec(vector<char> &v,char c){
    for(int i=0;i<v.size();i++){
        if(v[i]=='_'){
            v[i]=c;
        }
    }
}


void solve(int N, int K, vector<char>& A) {
    vector<char> v(N,'_');
    for(char c:A){
        fillVec(v,c);
        vecToOutput(v);
        if(read_string()=="CORRECT"){
            break;
        }
        v=outputToVec();
    }
}


int main() {
    int T;
    cin >> T;
    
    for (int i = 0; i < T; i++) {
        int N, K;
        cin >> N >> K;

        vector<char> A(K);
        for (int j = 0; j < K; j++) {
            cin >> A[j];
        }

        solve(N, K, A);
    }

    return 0;
}
