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

bool issubstr(string s1, string s2)
{
    int M = s1.length();
    int N = s2.length();
    for (int i = 0; i <= N - M; i++) 
    {
        int j;
        for (j = 0; j < M; j++)
            if (s2[i + j] != s1[j])
                break;
        if (j == M)
            return 1;
    }
    return 0 ;
}

void pre ( ) {
  
}
void solve ( ) {
  int n, r ; cin >> n >> r ; 
  queue < int > q ; 
  bool ok = 1 ; 
  for ( int i = 0 ; i < n ; i ++ ) {
    int a ; cin >> a ;
    while ( sz ( q ) && q.front ( ) <= a )
      q.pop ( ) ; 
    if ( sz ( q ) == 2 ){ 
      ok = 0 ; 
    } else {
      int nxt = a + r ; 
      if ( sz ( q ) ) {
        nxt = q.back ( ) + r ; 
      } q.push ( nxt ) ; 
    }
  }
  if ( ok ) {
    cout << "YES" << endl ; 
  } else {
    cout << "NO" << endl ;
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
