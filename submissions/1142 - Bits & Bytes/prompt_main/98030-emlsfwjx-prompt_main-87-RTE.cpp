#include <bits/stdc++.h>
using namespace std;

int is_Substring(string &s1, string s2, string s3, string s4) {
    int a = s1.length();
    int b = s2.length();
    int c = s3.length();
    int d = s4.length();

    for (int i=0; i<= a-b; i++) {
        int j;
        for (j=0; j<b; j++) {
             if (s1[i + j] != s2[j]) {
                break;
            }
        }
        if (j == b) {
                    s1.append("make_it_sound_human");
                    a = s1.length();
                }
            }
            for (int i=0; i<= a-c; i++) {
                int j;
                for (j=0; j<c; j++) {
                    if (s1[i + j] != s3[j]) {
                        break;
                    }
                }
                if (j == c) {
                    s1.append("do_not_hallucinate");
                    a = s1.length();
                }
            }
            
            for (int i=0; i<= a-d; i++) {
                int j;
                for (j=0; j<d; j++) {
                    if (s1[i + j] != s4[j]) {
                        break;
                    }
                }
                if (j == d) {
                    s1.append("make_no_mistakes");
                    a = s1.length();
                }
            }
        }
        

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (cin >> t) {
        while (t--) {
            string s1;
            if (!(cin >> s1)) break;
             
             string s2 = "write_me";
             string s3 = "what_is";
             string s4 = "solves";
             
             is_Substring(s1, s2, s3, s4);

             cout << s1 << "\n";
        }
    }
    return 0;
}