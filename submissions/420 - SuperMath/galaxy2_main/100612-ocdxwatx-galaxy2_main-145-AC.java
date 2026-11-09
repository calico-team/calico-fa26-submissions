/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
import java.io.*;
import java.util.*;
//lets go using my old code just added some stuff :cry
public class Calico9
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
        //yes this was here
    }
    static int N,M,size;
    static char[][] g;
    static boolean[][][] active;
    static int[] rs,cs,re,ce;
    static long[] best;
    static int[] dist;
    static int[] queue;
    static int INF=1000000000;
    static void solve(int low,int hi,int[] qs,int count){
        if(count==0 || low>hi){
            return;
        }
        int mid=(low+hi)/2;
        int[] src=new int[2*N];
        int ns=0;
        for(int r=0; r<N; r++){
            for(int m=0; m<2; m++){
                if(active[m][r][mid]){
                    src[ns++]=m*size+r*M+mid;
                }
            }
        }
        int[] dr={1,-1,0,0};
        int[] dc={0,0,1,-1};
        for(int k=0; k<ns; k++){
            int base=k*2*size;
            for(int c=low;c<=hi; c++){
                for(int r=0; r<N; r++){
                    for(int m=0; m<2; m++){
            dist[base+m*size+r*M+c]=INF;
                    }
                }
            }
            int head=0,tail=0;
            dist[base+src[k]]=0;
            queue[tail++]=src[k];
            while(head<tail){
                int id=queue[head++];
                int m=id/size;
                int rem=id%size;
                int r=rem/M;
                int c=rem%M;
                int d=dist[base+id];
                if(g[r][c]=='.'){
                    int o=(m==0)?id+size:id-size;
                    if(dist[base+o]==INF){
                        dist[base+o]=d+1;
                        queue[tail++]=o;
                    }
                }
                for(int z=0; z<4; z++){
                    int nr= r+dr[z];
                    int nc= c+dc[z];
                    if(nr<0 || nr>=N || nc<low || nc>hi){
                        continue;
                    }
                    if(!active[m][nr][nc]){
                        continue;
                    }
                    int nid=m*size+nr*M+nc;
                    if(dist[base+nid]==INF){
                        dist[base+nid]=d+1;
                        queue[tail++]=nid;
                    }
                }
            }
        }
        int[] left=new int[count];
        int[] right=new int[count];
        int ln=0,rn=0;
        for(int p=0; p<count; p++){
            int q=qs[p];
            int sa=rs[q]*M+cs[q];
            for(int m=0; m<2; m++){
                if(!active[m][re[q]][ce[q]]){
                    continue;
                }
                int sb=m*size+re[q]*M+ce[q];
                for(int k=0; k<ns; k++){
                    long v=(long)dist[k*2*size+sa]+dist[k*2*size+sb];
                    if(v<best[q]){
                        best[q]=v;
                    }
                }
            }
            int a=Math.min(cs[q],ce[q]);
            int b=Math.max(cs[q],ce[q]);
            if(b < mid){
                left[ln++]=q;
            }else if(a > mid){
                right[rn++]=q;
            }
        }
        solve(low, mid-1, left, ln);
        solve(mid+1, hi, right, rn);
    }
//ultrasonic faith is a great song, recommend to listen to it
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
		    N=Integer.parseInt(st.nextToken());
		    while(!st.hasMoreTokens()){
		        st= new StringTokenizer(br.readLine());
		    }
		    M=Integer.parseInt(st.nextToken());
		    while(!st.hasMoreTokens()){
		        st= new StringTokenizer(br.readLine());
		    }
		    int Q=Integer.parseInt(st.nextToken());
		    g= new char[N][];
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
		    size= N*M;
		    parent= new int[2*size];
		    for(int i=0; i<2*size; i++){
		        parent[i]=i;
		    }
		    active=new boolean[2][N][M];
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
		    rs=new int[Q];
		    cs=new int[Q];
		    re=new int[Q];
		    ce=new int[Q];
		    long[] K=new long[Q];
		    best=new long[Q];
		    int[] todo=new int[Q];
		    int tn=0;
		    for(int q=0; q<Q;q++){
		        int[] v= new int[5];
		        for(int i=0; i<5;i++){
		            while(st==null||!st.hasMoreTokens()){
		               l=br.readLine();
		               if(l==null){
		                   return;
		               }
		               st=new StringTokenizer(l);
		            }
		            v[i]=Integer.parseInt(st.nextToken());
		        }
		        rs[q]=v[0];
		        cs[q]=v[1];
		        re[q]=v[2];
		        ce[q]=v[3];
		        K[q]=v[4];
		        best[q]=Long.MAX_VALUE;
		        int startRoot=find(rs[q]*M+cs[q]);
		        boolean ok=false;
		        if (active[0][re[q]][ce[q]] && find(re[q] * M + ce[q]) == startRoot) {
		            ok = true;
		        }
		        if (active[1][re[q]][ce[q]] && find(size + re[q] * M + ce[q]) == startRoot) {
		            ok = true;
		        }
		        if(ok){
		            todo[tn++]=q;
		        }
		    }
		    dist=new int[4*N*size];
		    queue=new int[2*size];
		    solve(0, M-1, todo, tn);
		    for(int q=0; q<Q;q++){
		        comeout.append(best[q]<=K[q] ? "YES" : "NO").append("\n");
		    }
	    }
	    System.out.print(comeout);
	    //also recommend listing to m4 john doe chase theme
	}
}