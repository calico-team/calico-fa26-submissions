/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
import java.io.*;
import java.util.*;
public class Calico3
{
	public static void main(String[] args) throws IOException{
	//hey its me. its Justin li
	BufferedReader br= new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st=null;
    String l=br.readLine();
    if(l==null){
        return;
    }
    int T=Integer.parseInt(l.trim());
    for(int u=0; u<T;u++){
        while(st==null || !st.hasMoreTokens()){
        l= br.readLine();
        if(l==null){
            return;
        }
        st=new StringTokenizer(l);
        
        }
        int N = Integer.parseInt(st.nextToken());
        int K= Integer.parseInt(st.nextToken());
        char[] letters = new char[K];
        for( int i=0; i<K; i++){
            while(st == null || !st.hasMoreTokens()){
            l=br.readLine();
            if(l==null){
                return;
            }
            st=new StringTokenizer(l);
            
            }
            letters[i]=st.nextToken().charAt(0);
        }
        char[] ans= new char[N];
        for(int j=0; j<K; j++){
            char c= letters[j];
            StringBuilder guess= new StringBuilder();
            
            for(int m=0; m<N; m++){
            if(ans[m] != '\0'){
            guess.append(ans[m]);
                
            }else{
                guess.append(c);
            }
                
            }
            
        
         System.out.println(guess.toString());
         System.out.flush();
         
         String respond= br.readLine();
         if(respond==null){
             return;
         }
        respond=respond.trim();
        if (respond.equals("CORRECT")){
            break;
        }
       for (int i = 0; i < N; i++) {
        if (ans[i] == '\0' && respond.charAt(i) != '_') {
        ans[i] = respond.charAt(i);
        } 
    }
    }	    
	}}
}