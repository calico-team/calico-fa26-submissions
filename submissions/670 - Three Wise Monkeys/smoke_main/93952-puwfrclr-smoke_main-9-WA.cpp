#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef long long ll;
typedef long double ld;
typedef vector<double> vd;
typedef pair<int, int> pii;
typedef pair<pii, int> ppi;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pdd;

template <class T1, class T2>
istream& operator>>(istream& a, pair<T1, T2> &b){
    return (a >> b.first >> b.second);
}

template <class T>
istream& operator>>(istream& a, vector<T> &v){
    for(int i = 0; i < (int)v.size(); i++){
        a >> v[i];
    }
    return a;
}

template <class T1, class T2>
ostream& operator<<(ostream& a, pair<T1, T2> &b){
    return (a << b.first << " " << b.second);
}

template <class T>
ostream& operator<<(ostream& a, vector<T> &v){
    for(int i = 0; i < (int)v.size(); i++){
        a << v[i] << " ";
    }
    return a;
}



void process(){
    int N, R;
    cin >> N >> R;
    vi A(N);
    cin >> A;
    int last = 0;
    int wait = 0;
    int wait2 = 0;
    for(int i = 0; i < N; i++){
        int time = A[i] - last;
        last = A[i];
        //cout << i << " " << wait << " " << wait2 << " " << time << "\n";
        int mn = min(time, wait);
        wait -= mn;
        time -= mn;
        if(wait > 0 && wait2 == 1){
            cout << "NO\n";
            return;
        }
        if(wait == 0 && wait2 == 1){
            wait = R;
            wait2 = 0;
        }
        if(wait > 0){
            wait2 = 1;
            continue;
        }
        wait = R;
    }
    cout << "YES\n";
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int T=1;
    cin >> T;
    for(int i = 0; i < T; i++){
        process();
    }
       	 
} 

