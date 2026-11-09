#include <iostream>
#include <string>

using namespace std;

void Prompt_draft_main() {
    int overall_workflow;
    if (!(cin >> overall_workflow)) return;
    
    while (overall_workflow--) {
        string user_input;
        cin >> user_input;
        
        bool has_write_me = (user_input.find("write_me") != string::npos);
        bool has_what_is  = (user_input.find("what_is") != string::npos);
        bool has_solve    = (user_input.find("solve") != string::npos);
        
        if (has_write_me) {
            user_input = user_input + "make_it_sound_human";
        } 
        else {
            if (has_what_is) {
                user_input = user_input + "do_not_hallucinate";
            } 
            else {
                if (has_solve) {
                    user_input = user_input + "make_no_mistakes";
                } 
                else {
                    user_input = user_input + "thank_you";
                }
            }
        }
        
        cout << user_input << "
";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    Prompt_draft_main();
    
    return 0;
}
