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
int n, m, q ;
vector < string > g ; 
int dx [] = { -1, 1, 0, 0 } ; 
int dy [] = { 0, 0, -1, 1 } ;
int tab ( int r, int c, int md ) {
  return 2 * ( r * m + c ) + md; 
} int ok ( int r, int c, int md ) {
  if ( g [ r ][ c ] == '.' ) return 1 ; 
  if ( g [ r ][ c ] == 'B' ) return md == 0 ; 
  return md == 1 ;
}
void pre ( ) {
  
}
void solve ( ) {
  cin >> n >> m >> q ;
  g.clear ( ) ; 
  g.resize ( n ) ; 
  for ( auto &s : g ) cin >> s ;
  DSU dsu ( 2 * n * m ) ; 
  for ( int i = 0 ; i < n ; i ++ ) {
    for ( int j = 0 ; j < m ; j ++ ) {
      if ( g [ i ][ j ] == '.' ) {
        int id = tab ( i, j, 0 ) ; 
        int idd = tab ( i, j, 1 ) ;
        dsu.merge ( id, idd ) ;
      } for ( int k = 0 ; k < 4 ; k ++ ) {
        int x = i + dx [ k ] ; 
        int y = j + dy [ k ] ; 
        if ( x < 0 || x >= n || y < 0 || y >= m ) continue ;
        for ( int md = 0 ; md <= 1 ; md ++ ){
          if ( ok ( i, j, md ) && ok ( x, y, md ) ) {
            int idd = tab ( i, j, md ) ; 
            int id = tab ( x, y, md ) ; 
            dsu.merge ( id, idd ) ;
          }
        }
      }
    }
  } while ( q -- ) {
    int rr, cc, r, c ; 
    cin >> rr >> cc >> r >> c ; 
    int st = dsu.find ( tab ( rr, cc, 0 ) ) ; 
    int ok = 0 ; 
    if ( g [ r ][ c ] == '.' || g [ r ][ c ] == 'B') 
      ok = ( st == dsu.find ( tab ( r, c, 0 ) ) ) ;
    else 
      ok = ( st == dsu.find ( tab ( r, c, 1 ) ) ) ;
    if ( ok ) {
      cout << "YES" << endl ;
    } else {
      cout << "NO" << endl ;
    }
  }
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
