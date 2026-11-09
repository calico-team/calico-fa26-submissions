#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
int sachin[32];
ull dravid[32];

void insertVec(int v, ull mask, int& cnt, ull& lastKer){
    while(v){
        int p = 31 - __builtin_clz(v);
        if(!sachin[p]){ sachin[p] = v; dravid[p] = mask; return; }
        v ^= sachin[p];
        mask ^= dravid[p];
    }
    cnt++;
    lastKer = mask;
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int tests;
    cin >> tests;
    while(tests--){
        int n;
        cin >> n;
        vector<int> L(n), R(n), D(n);
        for(int& v : L) cin >> v;
        for(int& v : R) cin >> v;
        int base = 0;
        for(int i = 0; i < n; i++){ base ^= L[i]; D[i] = L[i] ^ R[i]; }
        int dec = 0;
        long long ans = -1;
        for(int b = 29; b >= 0 && ans < 0; b--){
            memset(sachin, 0, sizeof sachin);
            memset(dravid, 0, sizeof dravid);
            int kohli = 0, cnt = 0;
            ull lastKer = 0, dhoni = 0;
            vector<int> yuvraj;
            for(int i = 0; i < n; i++){
                if((D[i] >> b) == 0) continue;
                int h = 31 - __builtin_clz(D[i]);
                if(h > b){
                    int lb = L[i] >> b & 1, rb = R[i] >> b & 1;
                    if(lb == rb){
                        if(yuvraj.size() < 32 && lb == 0) dhoni |= 1ULL << yuvraj.size();
                        yuvraj.push_back(D[i] >> b);
                        continue;
                    }
                    if(lb == 0) kohli++;
                }
                insertVec(D[i] >> b, 0, cnt, lastKer);
            }
            int m = yuvraj.size(), kd = 0;
            ull kvec = 0;
            for(int j = 0; j < m; j++){
                int before = cnt;
                insertVec(yuvraj[j], j < 32 ? 1ULL << j : 0, cnt, lastKer);
                if(cnt > before){ kd++; kvec = lastKer; }
            }
            auto ok = [&](int tau, int k){
                int c = (base >> b) ^ ((dec << 1) | tau);
                ull mask = 0;
                while(c){
                    int p = 31 - __builtin_clz(c);
                    if(!sachin[p]) return false;
                    c ^= sachin[p];
                    mask ^= dravid[p];
                }
                int need = k - kohli;
                if(need <= 0 || m >= 32 || kd >= 2) return true;
                ull y = mask ^ dhoni;
                int w = __builtin_popcountll(y);
                if(kd == 1) w = max(w, (int)__builtin_popcountll(y ^ kvec));
                return w >= need;
            };
            if(ok(0, 1) || ok(1, 2))
                ans = ((long long)dec << (b + 1)) | ((1LL << (b + 1)) - 1);
            else if(ok(1, 0))
                dec = dec << 1 | 1;
            else if(ok(1, 1) || ok(0, 2))
                ans = ((long long)dec << (b + 1)) | ((1LL << b) - 1);
            else
                dec <<= 1;
        }
        if(ans < 0) ans = dec;
        cout << ans << '\n';
    }
}