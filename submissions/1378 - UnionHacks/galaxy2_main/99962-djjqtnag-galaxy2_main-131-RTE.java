import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.Arrays;
import java.util.StringTokenizer;
public class Matcha {
    static class Input {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st =new StringTokenizer("");
        int nextInt() throws IOException {
            while (!st.hasMoreTokens()) {
                st = new StringTokenizer(br.readLine());
            }
            return Integer.parseInt(st.nextToken());
        }
    }
    static int add(int[] basis,int value,int used) {
        while (value!=0) {
            int bit = 31-Integer.numberOfLeadingZeros(value);
            if (basis[bit]==0) {
                basis[bit] = value;
                return used | (1<<bit);
            }
            value ^= basis[bit];
        }
        return used;
    }
    static int maximize(int[] basis,int used,int value) {
        while (used!=0) {
            int bit = 31-Integer.numberOfLeadingZeros(used);
            value = Math.max(value,value^basis[bit]);
            used ^= 1<<bit;
        }
        return value;
    }
    static int score(int[] basis,int used,int value,int bit) {
        int prefix = maximize(basis,used,value);
        return (prefix<<bit) | ((1<<bit)-1);
    }
    static int solve(int[] low,int[] high) {
        int n = low.length;
        if (n==1) {
            return high[0];
        }
        int[] diff = new int[n];
        int[] outside =new int[30];
        int base = 0;
        int changes=0;
        int used = 0;
        for (int i=0;i<n;i++) {
            base ^= low[i];
            diff[i] = low[i]^high[i];
            changes ^= diff[i];
            used = add(outside,diff[i],used);
        }
        if (changes==0) {
            return base;
        }
        int answer = maximize(outside,used,base);
        int top = 31-Integer.numberOfLeadingZeros(changes);
        int freeMask = (1<<(top+1))-1;
        int upper = (base & ~freeMask) | freeMask;
        if (answer==upper) {
            return answer;
        }
        int[] picked = new int[32];
        int[] vector =new int[32];
        int[] moveA = new int[32];
        int[] moveB = new int[32];
        int[] work =new int[30];
        for (int bit=top-1;bit>=0;bit--) {
            int flag = 1<<bit;
            int count=0;
            int cap = top-bit+3;
            for (int i=0;i<n && count<cap;i++) {
                if ((diff[i] >>> (bit+1))==0) {
                    continue;
                }
                boolean left = (low[i]&flag)==0;
                boolean right = (high[i]&flag)!=0;
                if (!left && !right) {
                    continue;
                }
                picked[count] = i;
                vector[count] = diff[i]>>>bit;
                moveA[count] = left ? 1 : -1;
                moveB[count] = right ? vector[count]^1 : -1;
                count++;
            }
            if (count==0) {
                continue;
            }
            Arrays.fill(outside,0);
            used = 0;
            int skip=0;
            int full = (1<<(top-bit+1))-1;
            for (int i=0;i<n;i++) {
                if (skip<count && picked[skip]==i) {
                    skip++;
                    continue;
                }
                used = add(outside,diff[i]>>>bit,used);
                if (used==full) {
                    return upper;
                }
            }
            int prefix = base>>>bit;
            for (int a=0;a<count;a++) {
                System.arraycopy(outside,0,work,0,30);
                int available = used;
                for (int c=0;c<count;c++) {
                    if (c!=a) {
                        available = add(work,vector[c],available);
                    }
                }
                if (moveA[a]>=0) {
                    answer = Math.max(answer,score(work,available,prefix^moveA[a],bit));
                }
                if (moveB[a]>=0) {
                    answer = Math.max(answer,score(work,available,prefix^moveB[a],bit));
                }
                if (answer==upper) {
                    return answer;
                }
                for (int b=a+1;b<count;b++) {
                    System.arraycopy(outside,0,work,0,30);
                    available = used;
                    for (int c=0;c<count;c++) {
                        if (c!=a && c!=b) {
                            available = add(work,vector[c],available);
                        }
                    }
                    for (int x=0;x<2;x++) {
                        int first = x==0 ? moveA[a] : moveB[a];
                        if (first<0) {
                            continue;
                        }
                        for (int y=0;y<2;y++) {
                            int second = y==0 ? moveA[b] : moveB[b];
                            if (second<0) {
                                continue;
                            }
                            int value = score(work,available,prefix^first^second,bit);
                            answer = Math.max(answer,value);
                        }
                    }
                    if (answer==upper) {
                        return answer;
                    }
                }
            }
        }
        return answer;
    }
    public static void main(String[] args) throws IOException {
        Input in =new Input();
        StringBuilder out = new StringBuilder();
        int rounds = in.nextInt();
        while (rounds-- >0) {
            int n = in.nextInt();
            int[] low = new int[n];
            int[] high =new int[n];
            for (int i=0;i<n;i++) {
                low[i] = in.nextInt();
            }
            for (int i=0;i<n;i++) {
                high[i] = in.nextInt();
            }
            out.append(solve(low,high)).append('\n');
        }
        System.out.print(out);
    }
}