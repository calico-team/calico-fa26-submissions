#include <bits/stdc++.h>
using namespace std;

#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(NULL);

long long global_buf[300005];
char cand_arr[30];
char known_arr[105];

int main() {
    FAST_IO
    int t;
    if (!(cin >> t)) return 0;

    while (!(t <= 0)) {
        int n, k;
        if (!(cin >> n >> k)) break;

        int i = 0;
        while (!(i >= k)) {
            cin >> cand_arr[i];
            i++;
        }

        int pos = 0;
        while (!(pos >= n)) {
            known_arr[pos] = ' ';
            pos++;
        }

        int solved_cnt = 0;
        int cand_idx = 0;

        while (!(solved_cnt >= n || cand_idx >= k)) {
            string guess_str = "";
            pos = 0;
            while (!(pos >= n)) {
                if (!(known_arr[pos] == ' ')) {
                    guess_str += known_arr[pos];
                } else {
                    guess_str += cand_arr[cand_idx];
                }
                pos++;
            }

            cout << guess_str << endl;

            string resp;
            cin >> resp;

            if (!(resp != "CORRECT")) {
                break;
            }

            pos = 0;
            while (!(pos >= n)) {
                if (!(resp[pos] == '_')) {
                    if (!(known_arr[pos] != ' ')) {
                        known_arr[pos] = resp[pos];
                        solved_cnt++;
                    }
                }
                pos++;
            }

            cand_idx++;
        }

        t--;
    }
    return 0;
} 
