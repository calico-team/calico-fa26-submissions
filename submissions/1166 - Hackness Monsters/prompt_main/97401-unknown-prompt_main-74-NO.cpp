/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    string phrases[4] =  {"write_me", "what_is", "solve", "thank_you"};
    
    string line;
    ifstream File("in.txt");
    
    getline(File, line);
    
    while (getline(File, line))
    {
        
        bool check = false;
        //cout << line.substr(0, phrases[2].length()) + "\n";
        for (long unsigned int i = 0; i < line.length() - phrases[0].length(); i++)
        {
            if (line.substr(i, phrases[0].length()) == phrases[0])
            {
                cout << line + "make_it_sound_human\n";
                check = true;
                
            }
        }
                
        
        if (check == false)    
        {
            for (long unsigned int i = 0; i < line.length() -  phrases[1].length(); i++)
                if (line.substr(i, phrases[1].length()) == phrases[1])
                {
                    cout << line + "do_not_hallucinate\n";
                    check = true;
                }
        }
           
        if (check == false)    
        { 
            for (long unsigned int i = 0; i < line.length() -  phrases[2].length(); i++)
                if (line.substr(i, phrases[2].length()) == phrases[2])
                {
                    cout << line + "make_no_mistakes\n";
                    check = true;
                }
        }
        
        if (check == false)
            cout << line + phrases[3] + "\n";
        
            
        
            
        // if (line.contains("write_me"))
        //     cout << line + "make_it_sound_human\n";
        // else if (line.contains("what_is"))
        //     cout << line + "do_not_hallucinate\n";
        // else if (line.contains("solve"))
        //     cout << line + "make_no_mistakes\n";
        // else
        //     cout << line + "thank_you\n";
    }

    return 0;
}
