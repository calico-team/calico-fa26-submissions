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
    string phrases[3] = {"write_me", "what_is", "solve"};
    
    string line;
    ifstream File("in.txt");
    
    getline(File, line);
    
    while (getline(File, line))
    {
        if (line.contains("write_me"))
            cout << line + "make_it_sound_human\n";
        else if (line.contains("what_is"))
            cout << line + "do_not_hallucinate\n";
        else if (line.contains("solve"))
            cout << line + "make_no_mistakes\n";
        else
            cout << line + "thank_you\n";
    }

    return 0;
}
