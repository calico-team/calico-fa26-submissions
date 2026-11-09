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
  string s ; cin >> s ; 
  string a = "write_me" ; 
  string b = "what_is" ; 
  string c = "solve" ; 
  if ( issubstr ( a, s ) ) {
    s += "make_is_sound_human" ; 
    cout << s << endl ;
  } else if ( issubstr ( b, s ) ) {
    s += "do_not_hallucinate" ; 
    cout << s << endl ; 
  } else if ( issubstr ( c, s ) ) {
    s += "make_no_mistakes" ; 
    cout << s << endl ;
  } else {
    s += "thank_you" ; 
    cout << s << endl ;
  }
}
int32_t main ( ) { 
  ios_base::sync_with_stdio ( 0 ) ; cin.tie ( 0 ) ;
  int fileio = 0 ; 
  # ifndef ONLINE_JUDGE
    if ( fileio ) {
      freopen ( "input.txt", "r", stdin ) ; freopen ( "output.txt", "w", stdout ) ; freopen ( "error.txt", "w", stderr ) ;
    }
  # endif
  int tc = 1 ; 
  cin >> tc ; 
  pre ( ) ;
  # ifndef ONLINE_JUDGE 
    if ( fileio )
    cerr << "-----------------------" << '\n' ;
    // cout << "-----------------------" << '\n' ;
  # endif 
  while ( tc-- ) {
    solve ( ) ;
    # ifndef ONLINE_JUDGE 
      if ( fileio )
      cerr << "-----------------------" << '\n' ;
      // cout << "-----------------------" << '\n' ;
    # endif 
  }
  return 0 ;
}
