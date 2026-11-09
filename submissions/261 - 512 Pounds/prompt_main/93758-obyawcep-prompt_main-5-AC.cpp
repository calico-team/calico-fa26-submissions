#include <functional>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <fstream>
#include <numeric>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <cctype>
#include <vector>
#include <string>
#include <bitset>
#include <cmath>
#include <queue>
#include <stdio.h>
#include <stack>
#include <ctime>
#include <list>
#include <map>
#include <set>
#include <assert.h>
#define REP(i,n) for(int i=0;i<n;i++)
#define TR(i,x) for(auto i=x.begin();i!=x.end();i++)
#define ALL(x) x.begin(),x.end()
#define SORT(x) sort(ALL(x))
#define CLEAR(x) memset(x,0,sizeof(x))
#define FILL(x,c) memset(x,c,sizeof(x))

using namespace std;

const double eps = 1e-8;

#define PB push_back
#define MP make_pair

typedef map<int,int> MII;
typedef map<string,int> MSI;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<long double> VD;
typedef pair<int,int> PII;
typedef long long int64;
typedef long long ll;
typedef unsigned int UI;
typedef long double LD;
typedef unsigned long long ULL;

void solve(int caseId) {
  string s;
  cin >> s;
  if (s.find("write_me") != string::npos) {
    s += "make_it_sound_human";
  } else if (s.find("what_is") != string::npos) {
    s += "do_not_hallucinate";
  } else if (s.find("solve") != string::npos) {
    s += "make_no_mistakes";
  } else {
    s += "thank_you";
  }
  cout << s << endl;
}

int main() {
  int cases;
  cin >> cases;
  for (int i = 1; i <= cases; ++i) {
    solve(i);
  }
  return 0;
}