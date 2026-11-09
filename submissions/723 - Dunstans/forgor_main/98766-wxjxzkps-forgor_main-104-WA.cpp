#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

int arr2[200005], flag[200005], temp2[200005], arr[200005];
vector<int> vec[200005];
int i, j, x;
int n, l, r, idx;
long long tmp, xx;
string s;

int main() {
  cin >> s;
  cin >> n;
  if (n > 200001)
    n = 200001;

  if (s == "FIRST") {
    for (i = 1; i <= n - 1; i++) {
      int a, b;
      scanf("%d %d", &a, &b);
      vec[a].push_back(b);
      vec[b].push_back(a);
    }

    for (i = 0; i < 200005; i++)
      arr2[i] = 0;
    for (i = 0; i < 200005; i++)
      flag[i] = 0;

    l = 0;
    r = 0;
    temp2[r] = 1;
    r = r + 1;
    flag[1] = 1;
    while (true) {
      if (l == r)
        break;
      tmp = temp2[l];
      l = l + 1;
      for (j = 0; j < vec[tmp].size(); j++) {
        x = vec[tmp][j];
        if (flag[x] == 0) {
          flag[x] = 1;
          arr2[x] = tmp;
          temp2[r] = x;
          r = r + 1;
        } else {
        }
      }
    }
    // cout << "visited " << r << endl;

    if (0) {
      for (i = 1; i <= n; i++) {
        printf("%d ", arr2[i]);
      }
      printf("\n");
    }

    tmp = 0;
    for (i = 2; i <= n; i++) {
      tmp = tmp + arr2[i];
      // xx = xx ^ arr2[i];
    }
    xx = tmp % 1000000000;

    printf("%lld", xx);
    for (i = 2; i <= n; i++) {
      printf(" %d", arr2[i]);
    }
    printf("\n");
  } else {
    for (i = 1; i <= n; i++) {
      scanf("%d", &arr[i]);
    }

    idx = 0;
    for (i = 1; i <= n; i++) {
      if (arr[i] == -1) {
        idx = i;
      }
    }
    // cout << "missing " << idx << endl;

    if (idx >= 2) {
      tmp = 0;
      for (i = 2; i <= n; i++) {
        if (i != idx) {
          tmp = tmp + arr[i];
        }
      }
      tmp = tmp % 1000000000;
      arr[idx] = (arr[1] - tmp + 1000000000) % 1000000000;
    }

    for (i = 2; i <= n; i++) {
      printf("%d %d\n", i, arr[i]);
    }
  }
  
  return 0;
}
