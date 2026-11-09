#include <bits/stdc++.h>
using namespace std;
using ll=long long int;
using pii=pair<int,int>;
using pll=pair<ll,ll>;
using pli=pair<ll,int>;
using pil=pair<int,ll>;
using vi=vector<int>;
using vll=vector<ll>;
using vc=vector<char>;
using vvc=vector<vc>;
using vb=vector<bool>;
using vvb=vector<vb>;
using vvi=vector<vi>;
using vvll=vector<vll>;
using vpii=vector<pii>;
using vpll=vector<pll>;
using vvpii=vector<vpii>;
using vvpll=vector<vpll>;

int main() {
    cin.sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n,r;
        cin >> n >> r;
        vi v(n);
        for (auto &item : v) cin >> item;
        int a=0;
        int b=0;
        bool poss=true;
        for (int x : v) {
            if (a+r>x && b+r>x) {
                poss=false;
                break;
            }
            else {
                if (a+r>x) {
                    b=x;
                }
                else if (b+r>x) {
                    a=x;
                }
                else {
                    if (a>b) b=x;
                    else a=x;
                }
            }
        }
        if (poss) {
            cout << "YES" << endl;
        }
        else {
            cout << "NO" << endl;
        }
    }
}