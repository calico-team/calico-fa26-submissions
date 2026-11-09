#include <iostream>
#include <string>
using namespace std;
int main()
{
    //XD
    cin.tie(NULL);
    int T,i;
    string S;
    
    cin>>T;
    
    for (i=0; i<T; i++){
        cin>>S;
        if (S.find("write_me") != -1){
            S=S + "make_it_sound_human";
        }
        else if (S.find("what_is") != -1){
            S=S + "do_not_hallucinate";
        } 
        else if (S.find("solve") != -1){
            S=S + "make_no_mistakes ";
        }
        else{
            S=S + "Thank_you";
        }
        cout<<S<<"\n";
    }

    return 0;
}