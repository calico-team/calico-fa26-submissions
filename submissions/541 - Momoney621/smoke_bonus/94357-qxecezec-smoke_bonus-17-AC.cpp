#include <iostream>
#include <string>
#include <vector>
using namespace std;

string solve(int R, const vector<int>& A) {
    int charges = 2, nextCharge = 0;
    for (int a : A) {
        while (charges < 2 && nextCharge <= a) {
            charges++;
            if (charges < 2) nextCharge += R;
        }
        if (charges == 0) return "NO";
        if (charges == 2) nextCharge = a + R;
        charges--;
    }
    return "YES";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int N, R;
        cin >> N >> R;
        vector<int> A(N);
        for (int& a : A){
            cin >> a;
        }
        cout << solve(R, A) << '\n';
    }
}
