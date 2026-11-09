#include <iostream>
#include <string>
using namespace std;
int main()
{
    int n;
    cin>>n;
    string triggers[3] = {"write_me","what_is","solve"};
    string appends[3] = {"make_it_sound_human","do_not_hallucinate","make_no_mistakes"};
    string milquetoast = "thank_you";
    for(int x=0;x<n;x++){
        bool triggered = false;
        string prompt; cin>> prompt;
        for(int i=0;i<prompt.length()-4;i++){
            if(i<prompt.length()-6 and prompt[i]=='w'){
                if(prompt.substr(i,7)==triggers[1]){
                    prompt += appends[1];
                    triggered = true;
                    break;
                }
                else if(i<prompt.length()-7){
                    if(prompt.substr(i,8)==triggers[0]){
                        prompt += appends[0];
                        triggered = true;
                        break;
                    }
                }
            }
            
            if(prompt[i]=='s'){
                if(prompt.substr(i,5)==triggers[2]){
                    prompt += appends[2];
                    triggered = true;
                    break;
                }
            }
            
        }
        if(triggered == false){
            prompt += milquetoast;
        }
        cout<<prompt<<"\n";
        
    }
}