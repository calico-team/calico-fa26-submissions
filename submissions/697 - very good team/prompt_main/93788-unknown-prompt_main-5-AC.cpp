#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

constexpr int maxN = 1e6 + 1;
int N, T;
string S;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;

    for (int i = 0; i < T; i++)
    {
        cin >> S;
        if (S.find("write_me") != string::npos)
        {
            cout << S << "make_it_sound_human" << "\n";
        } else if (S.find("what_is") != string::npos)
        {
            cout << S << "do_not_hallucinate" << "\n";
        } else if (S.find("solve") != string::npos)
        {
            cout << S << "make_no_mistakes" << "\n";
        } else cout << S << "thank_you" << "\n";
    }
}