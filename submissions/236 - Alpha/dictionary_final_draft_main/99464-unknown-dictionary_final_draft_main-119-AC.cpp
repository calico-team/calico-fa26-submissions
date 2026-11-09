#include <bits/stdc++.h>
using namespace std;
int ch[6300000][2], cc;
int ins(int p, int x){
    int r = ++cc, cur = r;
    for (int b = 29; b >= 0; b--){
        int bit = x >> b & 1;
        ch[cur][0] = ch[p][0];
        ch[cur][1] = ch[p][1];
        int nn = ++cc;
        ch[cur][bit] = nn;
        cur = nn;
        p = ch[p][bit];}
    ch[cur][0] = ch[cur][1] = 0;
    return r;}
int qry(int r, int x){
    int res = 0;
    for (int b = 29; b >= 0; b--){
        int bit = x >> b & 1;
        if (ch[r][bit ^ 1]){
            res |= 1 << b;
            r = ch[r][bit ^ 1];
        } else r = ch[r][bit];}
    return res;}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--){
        cc = 0;
        int n;
        cin >> n;
        vector<int> a(n + 1), v(n + 1), d(n + 1, 0);
        for (int i = 1; i <= n; i++){
            cin >> a[i];
            d[a[i]]++;}
        for (int i = 1; i <= n; i++) cin >> v[i];
        vector<int> o;
        for (int i = 1; i <= n; i++) if (!d[i]) o.push_back(i);
        for (int k = 0; k < (int)o.size(); k++){
            int u = o[k];
            if (--d[a[u]] == 0) o.push_back(a[u]);}
        vector<int> rt(n + 1, 0), tv(n + 1, 0), e(n + 1, 0), cid(n + 1, -1), ans(n + 1, 0), cr, cx;
        for (int i = 1; i <= n; i++){
            if (d[i] > 0 && cid[i] < 0){
                vector<int> c;
                int u = i;
                do {
                    c.push_back(u); cid[u] = cr.size(); u = a[u];
                } while (u != i);
                int p = 0, R = 0;
                for (int x : c){
                    e[x] = p; R = ins(R, p); p ^= v[x];}
                int X = p;
                cr.push_back(R); cx.push_back(X);
                for (int x : c) ans[x] = max(qry(R, e[x]), qry(R, e[x] ^ X));}}
        for (int k = (int)o.size() - 1; k >= 0; k--){
            int u = o[k], w = a[u];
            tv[u] = v[u] ^ tv[w]; e[u] = e[w];
            cid[u] = cid[w]; rt[u] = ins(rt[w], tv[w]);
            int x = tv[u] ^ e[u], R = cr[cid[u]], X = cx[cid[u]];
            ans[u] = max({qry(rt[u], tv[u]), qry(R, x), qry(R, x ^ X)});}
        for (int i = 1; i <= n; i++) cout << ans[i] << " \n"[i == n];}}