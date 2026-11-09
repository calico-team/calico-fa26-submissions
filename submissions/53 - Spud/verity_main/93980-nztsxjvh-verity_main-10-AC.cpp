#include <stdio.h>
#include <math.h>
#include <vector>
#include <utility>
#include <queue>
#include <deque>
#include <map>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <stack>
#include <string>
#include <string.h>

using namespace std;

string s;
int n, K;
bool f[26];

void init(){
    int i;
    char c;
    for (i = 0; i < 26; ++i) f[i] = false;
    scanf("%d%d", &n, &K);
    for (i = 1; i <= K; ++i){
        scanf(" %c", &c);
        f[c - 'A'] = true;
    }
}

void work(){
    int i, j;
    char ss[150];
    s = "";
    for (i = 0; i < n; ++i) s += "_";
    for (i = 0; i < 26; ++i)
        if (f[i]){
            for (j = 0; j < n; ++j)
                if (s[j] == '_'){
                    s[j] = (char)('A' + i);
                }
            printf("%s\n", s.c_str());
            fflush(stdout);
            scanf("%s", ss);
            s = string(ss);
            if (s == "CORRECT") break;
        }
}

int main() {
    int t, T;
    // freopen("c.in", "r", stdin);
    scanf("%d", &T);
    for (t = 1; t <= T; ++t){
        init();
        work();
    }
    return 0;
}