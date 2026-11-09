/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
import java.io.*;
import java.util.*;
public class Calico6
{
    public static void main(String[] args) throws IOException {
        BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st=null;
        String l=br.readLine();
        if (l == null) {
            return;
        }
        int T = Integer.parseInt(l.trim());
        StringBuilder comeout = new StringBuilder();
        for (int u = 0; u < T; u++) {
            while (st == null || !st.hasMoreTokens()) {
                l = br.readLine();
                if (l == null) {
                    return;
                }
                st=new StringTokenizer(l);
            }
            int N =Integer.parseInt(st.nextToken());
            while(!st.hasMoreTokens()){
                st=new StringTokenizer(br.readLine());
            }
            int M=Integer.parseInt(st.nextToken());
            while(!st.hasMoreTokens()){
                st=new StringTokenizer(br.readLine());
            }
            int K=Integer.parseInt(st.nextToken());
            int[] P=new int[N + 1];
            for (int i=1;i<= N;i++) {
                while (st ==null||!st.hasMoreTokens()) {
                    l=br.readLine();
                    if (l== null) {
                        return;
                    }
                    st=new StringTokenizer(l);
                }
                P[i]=Integer.parseInt(st.nextToken());
            }
            int[] head=new int[N+ 1];
            int[] nxt=new int[N+ 1];
            Arrays.fill(head,-1);
            for (int i =1; i<= N;i++) {
                if (P[i]!= 0) {
                    nxt[i]=head[P[i]];
                    head[P[i]]= i;
                }
            }
            int[] depth=new int[N+ 1];
            int[] s=new int[N+ 1];
            for (int i=1;i<= N;i++) {
                if (depth[i]!= 0){
                continue;    
                } 
                int sp=0;
                int x=i;
                while (x != 0&& depth[x] == 0) {
                    s[sp++]=x;
                    x=P[x];
                }
                int base = (x == 0)?0:depth[x];
                while (sp > 0) {
                    base++;
                    depth[s[--sp]]=base;
                }
            }
            Integer[] order=new Integer[N];
            for (int i=0;i<N;i++) {
                order[i]=i + 1;
            }
            final int[] dep = depth;
            Arrays.sort(order,(a, b) ->  dep[b]-dep[a]);
            int[] h=new int[N+ 1];
            Arrays.fill(h,1);
            for (int i=0;i<N;i++) {
                int c=order[i];
                if (P[c]!=0&&h[c]+ 1 > h[P[c]]) {
                    h[P[c]]= h[c] + 1;
                }
            }
            //Thank gosh i learned this
            PriorityQueue<Long> pq=new PriorityQueue<>(Collections.reverseOrder());
            for (int i=1; i<= N;i++) {
                if (P[i]==0) {
                    pq.add((long)h[i]*20000L+ i);
                }
            }
            long total=0;
            int[] taken=new int[N + 1];
            for (int sa=0; sa <M&&!pq.isEmpty(); sa++) {
                int count=0;
                while (count<K&&!pq.isEmpty()) {
                    long key=pq.poll();
                    taken[count++] = (int)(key % 20000L);
                }
                total +=count;
                for (int i = 0; i < count; i++) {
                    for (int j = head[taken[i]];j!= -1;j= nxt[j]) {
                        pq.add((long) h[j]*20000L+j);
                    }
                }
            }
            comeout.append(total).append("\n");
        }
        System.out.print(comeout);
    }
}
