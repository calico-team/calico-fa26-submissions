// * @impbz * // 

# include <bits/stdc++.h>
using namespace std ;
# pragma region
# ifndef ONLINE_JUDGE 
  // # include "debug.cpp" 
# else
  # define debug(...) void(0)
# endif
# define sep ' '
# define int long long
# define pii pair < int, int >
# define pb push_back
# define all( x ) x.begin( ) , x.end( ) 
# define rall( x ) x.rbegin( ) , x.rend( ) 
# define fi first
# define se second
# define sz( x ) (int)x.size( )
# define endl '\n'
# pragma endregion

/*
 * DSU 
 * author: pbzadeh 
*/
struct DSU {
  vector < int > par; 
  vector < int > s ;
  DSU ( int n ) {
    par.assign ( n + 1, 0 ) ;
    s.assign ( n + 1, 1 ) ;
    for ( int i = 1 ; i <= n ; i ++ )  {
      par [ i ] = i ; 
    }
  } 
  int find ( int v ) {
    if ( par [ v ] != v ) 
      par [ v ] = find ( par [ v ] ) ;
    return par [ v ] ;
  } 
  void merge ( int v, int u ) {
    int Av = find ( v ) ;
    int Au = find ( u ) ;
    if ( Av == Au ) return ;
    if ( s [ Au ] < s [ Av ] ) swap ( Au, Av ) ; 
    par [ Av ] = Au ;
    s [ Au ] += s [ Av ] ; 
  }
} ;
void pre ( ) {
  
}
void solve ( ) {
  int n, m, k ; cin >> n >> m >> k ;
  vector < int > pr ( n + 1 ) ; 
  vector < vector < int > > child ( n + 1 ) ; 
  for ( int i = 1 ; i <= n ; i ++ ) {
    cin >> pr [ i ] ; 
    child [ pr [ i ] ].pb ( i ) ;
  } 
  vector < int > q ;
  q.pb ( 0 ) ; 
  for ( int i = 0 ; i < sz ( q ) ; i ++ ) {
    for ( int c : child [ q [ i ] ] ) {
      q.pb ( c ) ;
    }
  }
  vector < int > h ( n + 1, 1 ) ;
  for ( int i = sz ( q ) - 1 ; i >= 0 ; i -- ) {
    int v = q [ i ] ;
    if ( pr [ v ] != 0 ) 
      h [ pr [ v ] ] = max ( h [ pr [ v ] ], h [ v ] + 1 ) ;   
  } priority_queue < pii > pq ; 
  for ( int c : child [ 0 ] ) {
    pq.push ( { h [ c ], c } ) ;
  } 
  int ans = 0 ; 
  for ( int i = 0 ; i < m && sz ( pq ) ; i ++ ) {
    vector < int > use ; 
    for ( int j = 0 ; j < k && sz ( pq ) ; j ++ ) {
      use.pb ( pq.top ( ).se ) ; 
      pq.pop ( ) ; 
    } ans += sz ( use ) ;
    for ( int u : use ) {
      for ( int c : child [ u ] ) 
        pq.push ( { h [ c ], c } ) ;
    }
  } cout << ans << endl ; 
}
int32_t main ( ) { 
  ios_base::sync_with_stdio ( 0 ) ; cin.tie ( 0 ) ;
  int fileio = 0 ; 
  int tc = 1 ; 
  cin >> tc ; 
  pre ( ) ;
  while ( tc-- ) {
    solve ( ) ;
  }
  return 0 ;
}
