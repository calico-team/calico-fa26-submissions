/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
import java.io.*;
import java.util.*;
public class Calico8
{
    static int[] next;
    static int find(int a){
        int r= a;
        while(next[r]!=r){
            r=next[r];
        }
        while(next[a]!=r){
            int t=next[a];
            next[a]=r;
            a= t;
        }
        return r;
    }
    public static void main(String[] args) throws IOException{
        BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st=null;
        String l=br.readLine();
        if(l==null){
        return;
        }
        int T=Integer.parseInt(l.trim());
        StringBuilder comeout=new StringBuilder();
        for(int u=0; u<T; u++){
            while(st==null|| !st.hasMoreTokens()){
                l=br.readLine();
                if(l==null){
                    return;
                }
                st=new StringTokenizer(l);
            }
            int N=Integer.parseInt(st.nextToken());
            while(!st.hasMoreTokens()){
                st=new StringTokenizer(br.readLine());
            }
            int M=Integer.parseInt(st.nextToken());
            while(!st.hasMoreTokens()){
                st=new StringTokenizer(br.readLine());
            }
            int Q=Integer.parseInt(st.nextToken());
            int[] R=new int[Q ];
            int[] C=new int[Q ];
            int[] P=new int[Q ];
            for(int q=0; q<Q;q++){
                int[] v=new int[3];
                for(int i=0; i<3; i++){
                    while(st==null|| !st.hasMoreTokens()){
                        l=br.readLine();
                        if(l==null){
                            return;
                        }
                        st=new StringTokenizer(l);
                    }
                    v[i]=Integer.parseInt(st.nextToken());
                }
                R[q]=v[ 0];
                C[q]=v[1];
                P[q]=v[2];
            }
            int W=M+1;
            next=new int[N*W];
            for(int i=0; i<N*W; i++){
                next[i]=i;
            }
            int[] ans = new int[N*M];
            for(int smolq=Q-1; smolq>=0; smolq--){
                int p=P[smolq];
                for(int dr=-p; dr<=p; dr++){
                    int row=R[smolq]+dr;
                    int rem=p*p-dr*dr;
                    int half=(int)Math.sqrt((double)rem);
                    while(half*half>rem){
                        half--;
                    }
                    while((half+1) * (half+1)<=rem){
                        half++;
                    }
                    int limit=row*W+C[smolq]+half+1;
                    int c=find(row*W+C[smolq]-half);
                    while(c<limit){
                        int col=c - row*W;
                        int dc=col - C[smolq];
                        ans[row*M+col]=rem-dc*dc+1;
                        next[c] = c+1;
                        c = find(c+1);
                    }
                }
            }
            for(int r=0; r<N; r++){
                for(int c=0; c<M; c++){
                    if(c>0){
                    comeout.append(' ');
                    }
                    comeout.append(ans[r*M+c]);
                }
                    comeout.append("\n");
            }
        }
        //last problem im doing, would recommend bloody devastation and creation of Hatred, if you know these you know ball
        System.out.print(comeout);
        /*
        
        67
        
        
        */
    }
}