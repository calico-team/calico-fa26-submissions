#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct D{
    long long s, x;
    char d;
};

bool cmp(D a, D b){
    if (a.s == b.s) return a.x < b.x;
    return a.s < b.s;
}

int main(){
    int t;
    cin >> t;

    while (t--){
        int n;
        long long k;
        cin >> n >> k;

        vector<D> v(n);

        for (int i = 0; i < n; i++){
            long long x, y, z;
            char d;
            cin >> x >> y >> z >> d;

            v[i] = {x + y, x, d};
        }

        sort(v.begin(), v.end(), cmp);

        long long mal = 0;
        int i = 0;

        while (i < n){
            int j = i;

            while (j < n && v[j].s == v[i].s){
                j++;
            }

            vector<long long> e;

            for (int p = i; p < j; p++){
                if (v[p].d == 'E') {
                    e.push_back(v[p].x);
                }
            }

            for (int p = i; p < j; p++){
                if (v[p].d == 'N') {
                    long long x = v[p].x;

                    auto a = lower_bound(e.begin(), e.end(), x - k + 1);
                    auto b = lower_bound(e.begin(), e.end(), x);

                    mal += b - a;
                }
            }

            i = j;
        }

        cout << 1LL * n * k - mal << '\n';
    }

    return 0;
}