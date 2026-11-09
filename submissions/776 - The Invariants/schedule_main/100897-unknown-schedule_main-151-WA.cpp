#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n;
    cin >> n;
    while(n--){
        long long N, M;
        int K; 
        cin >> N >> M >> K;
        vector<int> P(N);
        long long result = 0;
        vector<int> A(N, 0);
        for (long long i = 0; i < N; i++){
            cin >> P[i];
        }
        for(long long i = 0; i <  M; i++){
            int a = 0;
            vector<int> Ac(N, 0);
            for(long long j = 0; j < N; j++){
                if(A[j] == 1) continue;
                if((P[j] == 0 || A[P[j] - 1] == 1 )&& a < K){
                    result++;
                    a++;
                    Ac[j] = 1;
                }
                
            }
            for(long long j = 0; j < N; j++){
                if(Ac[j] == 1) A[j] = 1;
            }

        }
        cout << result << endl;

    }
    return 0;
}