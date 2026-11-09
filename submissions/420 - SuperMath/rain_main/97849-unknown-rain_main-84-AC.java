/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
import java.io.*;
import java.util.*;
public class Calico4
{
    static int M=100005;
    static long[] bitE=new long[M+2];
    static long[] bitN=new long[M+2];
    static void add(long[] b, int p, int v) {
        for (int i=p+ 1;i<= M;i+= i & -i) {
            b[i] += v;
        }
    }
    static long sum(long[] b, int p) {
        long s = 0;
        for(int i=p+1;i>0;i-= i & -i) {
        s+=b[i];
        }
        return s;
    }
    static long range(long[] b,long l,long r) {
        if (l <0){ 
            l =0;
        }
        if (r >M - 1){ 
            r =M - 1;
        }
        if (l> r) {
        return 0;
    }
        long res = sum(b, (int) r);
        if (l > 0){
        res -=sum(b,(int) l- 1);
        }
        return res;
    }
    public static void main(String[] args) throws IOException {
        BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st=null;
        String l=br.readLine();
        if (l== null) {
            return;
        }
        int T=Integer.parseInt(l.trim());
        for (int u =0;u< T; u++) {
            while (st == null || !st.hasMoreTokens()) {
                l =br.readLine();
                if (l==null) {
                    return;
                }
                st = new StringTokenizer(l);
            }
            int N =Integer.parseInt(st.nextToken());
            long K =Long.parseLong(st.nextToken());
            int[] x =new int[N];
            int[] y =new int[N];
            int[] z =new int[N];
            boolean[] east=new boolean[N];
            Integer[] order= new Integer[N];
            for (int i= 0;i< N; i++) {
                while (st== null|| !st.hasMoreTokens()) {
                    l=br.readLine();
                    if (l== null) {
                        return;
                    }
                    st=new StringTokenizer(l);
                }
                x[i]=Integer.parseInt(st.nextToken());
                while (!st.hasMoreTokens()){
                st=new StringTokenizer(br.readLine());
                }
                y[i]= Integer.parseInt(st.nextToken());
                while(!st.hasMoreTokens()) {
                st = new StringTokenizer(br.readLine());
                }
                z[i]=Integer.parseInt(st.nextToken());
                while (!st.hasMoreTokens()) {
                st =new StringTokenizer(br.readLine());
                }
                east[i]= st.nextToken().charAt(0) =='E';
                order[i] =i;
            }
            Arrays.sort(order, (a, b) -> {
                int sa =x[a] + y[a];
                int sb= x[b]+ y[b];
                if (sa!=sb){
                  return sa - sb; 
                } 
                return z[b] - z[a];
            });
            long total= 0;
            int i =0;
            while (i< N) {
                int j = i;
                int diag= x[order[i]]+ y[order[i]];
                while (j <N &&x[order[j]] + y[order[j]] == diag) {
                    j++;
                }
                int a=i;
                while (a< j) {
                    int b = a;
                    while (b < j && z[order[b]] == z[order[a]]) {
                        b++;
                    }
                    for (int p= a; p < b; p++) {
                        int d =order[p];
                        long blocked;
                        if (east[d]) {
                            blocked = range(bitN, x[d], x[d] + K - 1);
                        } else {
                            blocked=range(bitE, x[d] - K + 1, x[d]);
                        }
                        total += K-blocked;
                    }
                    for (int p = a; p < b; p++) {
                        int d = order[p];
                        if (east[d]){
                          add(bitE, x[d], 1);  
                        } else {
                            add(bitN, x[d], 1);
                        }
                    }
                    a=b;
                }
                for (int p = i; p < j; p++) {
                    int d =order[p];
                    if(east[d]){
                    add(bitE, x[d], -1);    
                    } else{ add(bitN, x[d], -1);}
                }
                i=j;
            }
System.out.println(total);
        }}}