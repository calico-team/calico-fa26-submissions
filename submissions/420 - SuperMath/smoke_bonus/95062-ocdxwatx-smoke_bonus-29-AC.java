/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
import java.io.*;
import java.util.*;
public class Calico2 {
    public static void main(String[] args) throws IOException {
        BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st= null;
        String l= br.readLine();
        if (l== null){
     return;}
        int T=Integer.parseInt(l.trim());
        StringBuilder comeout=new StringBuilder();
        while (T--> 0){
            while (st == null||!st.hasMoreTokens()) {
            l= br.readLine();
                if (l== null){ break;}
                st= new StringTokenizer(l);
            }
            if (!st.hasMoreTokens()){ break;}
            int N =Integer.parseInt(st.nextToken());
            long R =Long.parseLong(st.nextToken());
            long[] A = new long[N];
            for (int thing= 0; thing< N;thing++) {
                while(!st.hasMoreTokens()) {
                    l=br.readLine();
                    st =new StringTokenizer(l);
                }
                A[thing] = Long.parseLong(st.nextToken());
            }
            int charges = 2; //smokebombsss
            Deque<Long> recharges= new ArrayDeque<>();
            boolean possible = true;
            for (int q= 0;q< N; q++) {
                long time= A[q];
                while (!recharges.isEmpty()&& recharges.peek() <= time) {
                    recharges.poll();
                charges++;
                }
                if (charges> 0) {
                    charges--;
                    long done;
                    if(recharges.isEmpty()) {
                        done=time + R;
                    } else {
                    done= recharges.peekLast() + R;
                    }
                    recharges.addLast(done);
                } else {
                    possible= false;
                    break;
                }
            }
            if (!possible) {
                comeout.append("NO\n");
            } else {
                comeout.append("YES\n");
            }
        }
        System.out.print(comeout);
    }}
