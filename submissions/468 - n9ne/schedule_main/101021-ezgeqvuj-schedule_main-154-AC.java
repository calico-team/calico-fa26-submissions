import java.io.*;
import java.util.*;

public class problem_5 {
    public static void main(String[] args) throws IOException {
        StreamTokenizer in = new StreamTokenizer(new BufferedInputStream(System.in));
        in.nextToken();
        int t = (int) in.nval;
        StringBuilder sb = new StringBuilder();

        while (t-- > 0) {
            in.nextToken(); int n = (int) in.nval;
            in.nextToken(); int m = (int) in.nval;
            in.nextToken(); int k = (int) in.nval;

            int[] p = new int[n + 1];
            int[] head = new int[n + 1];
            int[] next = new int[n + 1];
            Arrays.fill(head, -1);

            int[] order = new int[n];
            int cnt = 0;

            for (int i = 1; i <= n; i++) {
                in.nextToken();
                p[i] = (int) in.nval;
                if (p[i] == 0) {
                    order[cnt++] = i;          
                } else {
                    next[i] = head[p[i]];      
                    head[p[i]] = i;
                }
            }
            int roots = cnt;

            
            for (int idx = 0; idx < cnt; idx++) {
                int u = order[idx];
                for (int c = head[u]; c != -1; c = next[c]) {
                    order[cnt++] = c;
                }
            }

         
            int[] h = new int[n + 1];
            Arrays.fill(h, 1);
            for (int idx = n - 1; idx >= 0; idx--) {
                int u = order[idx];
                int par = p[u];
                if (par != 0 && h[u] + 1 > h[par]) h[par] = h[u] + 1;
            }

            final int BASE = 20000;
            PriorityQueue<Integer> pq = new PriorityQueue<>(Collections.reverseOrder());
            for (int i = 0; i < roots; i++) {
                int r = order[i];
                pq.add(h[r] * BASE + r);
            }

            long taken = 0;
            int[] batch = new int[k];
            for (int sem = 0; sem < m && !pq.isEmpty(); sem++) {
                int b = 0;
                while (!pq.isEmpty() && b < k) {
                    batch[b++] = pq.poll() % BASE;
                }
                taken += b;
                for (int i = 0; i < b; i++) {
                    for (int c = head[batch[i]]; c != -1; c = next[c]) {
                        pq.add(h[c] * BASE + c);
                    }
                }
            }
            sb.append(taken).append('\n');
        }
        System.out.print(sb);
    }
}