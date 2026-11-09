/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
import java.io.*;
import java.util.*;
public class Calico5
{
    static int[] parent;
    static int find(int a){
        while(parent[a] != a){
            parent[a]=parent[parent[a]];
            a= parent[a];
        }
        return a;
    }
    static void union(int six, int seven){
        six=find(six);
        seven=find(seven);
        if(six!=seven){
            parent[six]=seven;
        }
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
		for (int u=0; u<T; u++){
		    while(st== null || !st.hasMoreTokens()){
		      l=br.readLine();
		      if(l==null){
		          return;
		      }
		      st= new StringTokenizer(l);
		    }
		    int N=Integer.parseInt(st.nextToken());
		    while(!st.hasMoreTokens()){
		        st= new StringTokenizer(br.readLine());
		    }
		    int M=Integer.parseInt(st.nextToken());
		    while(!st.hasMoreTokens()){
		        st= new StringTokenizer(br.readLine());
		    }
		    int Q=Integer.parseInt(st.nextToken());
		    char[][] g= new char[N][];
		    for(int i=0; i<N; i++){
		        while(st==null || !st.hasMoreTokens()){
		            l=br.readLine();
		            if(l==null){
		                return;
		            }
		            st=new StringTokenizer(l);
		        }
		    g[i]=st.nextToken().toCharArray();
		    }
		    
		    int size= N*M;
		    parent= new int[2*size];
		    for(int i=0; i<2*size; i++){
		        parent[i]=i;
		    }
		    boolean[][][] active=new boolean[2][N][M];
		    for(int r=0; r<N;r++){
		        for(int c=0; c<M; c++){
		            char ch=g[r][c];
		            active[0][r][c]=(ch=='B'||ch=='.');
		             active[1][r][c]=(ch=='R'||ch=='.');
		        }
		    }
		    for (int r=0; r<N;r++){
		        for(int c=0;c<M;c++){
		            if(g[r][c]=='.'){
		                union(r*M+c, size+r*M +c);
		                
		            }
		            for(int m=0;m<2;m++){
		                if(!active[m][r][c]){
		                    continue;
		                }
		                if(c+1<M && active[m][r][c+1]){
		                    union(m*size + r*M+c, m*size +r*M+c+1);
		                }
		                if(r+1<N && active[m][r+1][c]){
		                    union(m*size+r*M+c,m*size+(r+1)*M+c);
		                }
		            }
		        }
		    }
		    for(int q=0; q<Q;q++){
		        int[] v= new int[4];
		        for(int i=0; i<4;i++){
		            while(st==null||!st.hasMoreTokens()){
		               l=br.readLine();
		               if(l==null){
		                   return;
		               }
		               st=new StringTokenizer(l);
		                
		            }
		            v[i]=Integer.parseInt(st.nextToken());
		        }
		        int rs=v[0],cs=v[1],re=v[2],ce=v[3];
		        int startRoot=find(rs*M+cs);
		        boolean ok=false;
		        if (active[0][re][ce] && find(re * M + ce) == startRoot) {
                    ok = true;
                }
                if (active[1][re][ce] && find(size + re * M + ce) == startRoot) {
                    ok = true;
                }
                comeout.append(ok ? "YES" : "NO").append("\n");
		    }
	}
	
	System.out.print(comeout);
	}
}
