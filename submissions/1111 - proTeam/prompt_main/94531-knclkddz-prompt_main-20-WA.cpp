#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int t;

    cin >>t;

    for (int i = 0; i<t; i++){
        string text;
        cin >>text;

        if (text.find("write_me") < text.length()){
            text.append("make_it_sound_human");
        }
        if (text.find("what_is") < text.length()){
            text.append("do_not_hallucinate");
        }
        if (text.find("solve") < text.length()){
            text.append("make_no_mistakes");
        }

        cout <<text;

    }
    return 0;
}
