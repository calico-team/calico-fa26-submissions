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

char ss[150];
string s;

void init(){
    scanf("%s", ss);
    s = string(ss);
}

void work(){
    if (s.find("write_me") != string::npos) s += "make_it_sound_human";
    else{
        if (s.find("what_is") != string::npos) s += "do_not_hallucinate";
        else{
            if (s.find("solve") != string::npos) s += "make_no_mistakes";
            else s += "thank_you";
        }
    }

    printf("%s\n", s.c_str());
}

int main() {
    int t, T;
    // freopen("a.in", "r", stdin);
    scanf("%d", &T);
    for (t = 1; t <= T; ++t){
        init();
        work();
    }
    return 0;
}