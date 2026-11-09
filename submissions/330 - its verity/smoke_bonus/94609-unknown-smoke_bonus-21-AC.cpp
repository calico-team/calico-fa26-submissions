#include <bits/stdc++.h>

using namespace std;
#define sz(x) ((int)x.size())
typedef long long ll;
int n, m, k;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    int num;
    while (n --) {
        int smoke = 2; int time = 0; int time2 = 0; bool fail = false;
        vector<int> a;
        vector<int> dif;
        cin >> m >> k;
        for (int i = 0; i < m; i ++) {
            cin >> num;
            a.push_back(num);
            if (i != 0) dif.push_back(a[i] - a[i - 1]);
        }
        for (int i = 0; i < m; i ++) {
            if (time != 0) {
                time -= dif[i - 1];
                if (time <= 0) {
                    time2 += time;
                    if (time2 <= 0) {
                        smoke = 2;
                        time = 0;
                        time2 = 0;
                    }
                    else {smoke ++; time = time2;}
                }
            }
            smoke --;
            if (time == 0) time += k;
            else time2 += k;
            time = min(time, k); time2 = min(time2, k);
            if (smoke < 0) {cout << "NO\n"; fail = true; break;}
        }
        if (!fail) cout << "YES\n";
    }

    return 0;
}
