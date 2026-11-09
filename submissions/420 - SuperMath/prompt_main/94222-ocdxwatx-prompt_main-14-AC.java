/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
import java.io.*;
import java.util.*;
public class Calico1 {
    public static void main(String[] args) throws IOException {
        BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
        String line = br.readLine();
        if (line == null) {
            return;
        }
        int T = Integer.parseInt(line.trim());
        StringBuilder output = new StringBuilder();
        for (int i = 0; i < T; i++) {
            line = br.readLine();
            if (line == null) {
                break;}
            String s =line.trim();
            if (s.contains("write_me")) {
                s+="make_it_sound_human";
            } else if(s.contains("what_is")) {
                s+= "do_not_hallucinate";
            }else if(s.contains("solve")) {
                s+="make_no_mistakes";
            }else {
                s+= "thank_you";
            }
            output.append(s).append("\n");
        }
System.out.print(output);
        
    }}
