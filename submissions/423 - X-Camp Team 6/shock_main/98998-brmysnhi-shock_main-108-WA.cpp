#include <bits/stdc++.h>

using namespace std;

struct eq{
    int x;
    int y;
    int p;
};

int main(){
    cin.tie(nullptr);
    cout.sync_with_stdio(false);

    int cases;
    cin >> cases;

    for (int i = 0 ; i < cases ; i++){
        int N,M,Q;
        cin >> N >> M >> Q;

        vector<eq> eqs;

        for (int j = 0 ; j < Q ; j++){
            eqs.emplace_back();
            auto &bk = eqs.back();
            cin >> bk.x >> bk.y >> bk.p;
        }

        for (int c = 0 ; c < M ; c++){
            for (int r = 0 ; r < N ; r++){
                int meq = 0;
                for (auto &seq : eqs){
                    int fp = seq.p * seq.p - ((r - seq.x) * (r - seq.x) + (c - seq.y) * (c - seq.y)) + 1;
                    if (fp > meq){
                        meq = fp;
                    }
                }

                if (r == N-1)
                    cout << meq << "\n";
                else
                    cout << meq << " ";
            }
        }
    }
}