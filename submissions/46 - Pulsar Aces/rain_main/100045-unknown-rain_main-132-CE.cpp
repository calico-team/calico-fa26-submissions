/*def solve():
    N, K = map(int, input().split())
    NP = []
    EP = []
    # north pos (x,y), east pos (x,y)
    for i in range(N):
        k = input().split()
        if(k[3] == 'N'):
            NP.append([int(k[0]),int(k[1])])
        else:
            EP.append([int(k[0]),int(k[1])])
    ans = N*K
    for i in range(len(NP)):
        for j in range(len(EP)):
            #print(NX[i], NY[i], EX[j], EY[j])
            if EP[j][1] - NP[i][1] == NP[i][0] - EP[j][0] and 0 < NP[i][0] - EP[j][0] < K:
                ans -= 1
    return ans
for i in range(int(input())):
    print(solve())


# (x - t, y) E
# (x, y - t) N*/
#include <vector>
#include <iostream>
#include <utility>
int solve(){
    int n, k; std::cin >> n >> k;
    std::vector<std::pair<int, int>> np;
    std::vector<std::pair<int, int>> ep;
    for (int i = 0; i < n; i++){
        int a, b; char c; std::cin >> a >> b >> c;
        if(c == 'N'){
            np.push_back({a, b});
        } else {
            ep.push_back({a, b});
        }
    }
    int ans = n * k;
    for(int i = 0; i < np.size(); i++){
        for(int j = 0; j < ep.size(); j++){
            if(ep[j][1] - np[i][1] == np[i][0] - ep[j][0] && 0 < np[i][0] - ep[j][0] && np[i][0] - ep[j][0] < k)
                ans--;
        }
    }
    return ans;
}
int main(){
    int x; std::cin >> x;
    for (int i = 0; i < x; i++){
        std::cout << solve();
    }
}