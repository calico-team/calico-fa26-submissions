
//  In the name of << Allah >> =D
//  made by -> SAJJAD_LEGEND =)
# pragma region // base 
# include "bits/stdc++.h"
using namespace std ;
# define endl '\n'
# define int int64_t
# define I first
# define II second
# define all( a ) a.begin (), a.end ()
# define rall( a ) a.rbegin (), a.rend ()
# define sz( a ) int( a.size () )
# define pb push_back
template < typename T > void coutf_ ( const T &a ){cout<<a<<' ';}
template <> void coutf_ ( const char &a ){if(a=='\n')cout<<a;else cout<<a<<' ';}
template < typename T > void coutf_ ( const vector < T > &a ){for(auto&i:a)cout<<i<<' ';}
template < typename T, typename U > void coutf_ ( const pair < T, U > &a ){cout<<a.first<<' '<<a.second<<' ';}
template < typename T, typename ... Args > void coutf_ ( const T &a, const Args&... args ){coutf_(a);coutf_(args...);}
template < typename ... Args > void coutf ( const Args&... args ){coutf_(args...);cout<<'\n';}
# pragma endregion

const int N = 2e5 + 10 ;
vector < int > adj [ N ] ;
int p [ N ], c [ N ] ;
void dfs ( int u, int v = 0 ) {
    p [ u ] = v ;
    c [ v ] ++ ;
    for ( auto &i : adj [ u ] )
        if ( i != v )
            dfs ( i, u ) ;
}

void solve () {
    string s ; cin >> s ;
    if ( s == "FIRST" ) {
        int n ; cin >> n ;
        for ( int i = 0 ; i < n - 1 ; i ++ ) {
            int u, v ; cin >> u >> v ;
            adj [ u ].pb ( v ) ;
            adj [ v ].pb ( u ) ;
        }
        dfs ( 1 ) ;
        for ( int i = 1 ; i <= n ; i ++ )
            cout << ( p [ i ] << 1 ) + ( c [ i ] & 1 ) << ' ' ;
        cout << endl ;
    } else {
        int n ; cin >> n ;
        vector < int > a ( n ) ;
        for ( auto &i : a )
            cin >> i ;
        int x = -1 ;
        for ( int i = 0 ; i < n ; i ++ ) {
            if ( a [ i ] != -1 )
                c [ a [ i ] >> 1 ] ++ ;
            else
                x = i ;
        }
        if ( x == 0 ) {
            for ( int i = 1 ; i < n ; i ++ )
                coutf ( i + 1, a [ i ] >> 1 ) ;
            return ;
        }
        for ( int i = 1 ; i <= n ; i ++ )
            if ( ( c [ i ] ^ a [ i - 1 ] ) & 1 )
                a [ x ] = ( i << 1 ) ;
        for ( int i = 2 ; i <= n ; i ++ )
            coutf ( i, a [ i - 1 ] >> 1 ) ;
    }
}
# pragma region // main 
int32_t main () {
    ios_base :: sync_with_stdio ( 0 ) ; cin.tie ( nullptr ) ;
    solve () ;
    return 0 ;
}
// Just a noob Kavi fan
// +31 in time of Dr.Prof.A.S class ~mmm
# pragma endregion
// •‿•
