import java.io.*;
import java.util.*;

public class problem_8 {
    static int[] par;

    static int find(int x) {
        int r = x;
        while (par[r] != r) r = par[r];
        while (par[x] != r) {
            int nx = par[x];
            par[x] = r;
            x = nx;
        }
        return r;
    }

    public static void main(String[] args) throws IOException {
        StreamTokenizer in = new StreamTokenizer(new BufferedInputStream(System.in, 1 << 16));
        in.nextToken();
        int t = (int) in.nval;
        PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out), 1 << 16));

        while (t-- > 0) {
            in.nextToken(); int n = (int) in.nval;
            in.nextToken(); int m = (int) in.nval;
            in.nextToken(); int q = (int) in.nval;

            int[] R = new int[q], C = new int[q], P = new int[q];
            for (int i = 0; i < q; i++) {
                in.nextToken(); R[i] = (int) in.nval;
                in.nextToken(); C[i] = (int) in.nval;
                in.nextToken(); P[i] = (int) in.nval;
            }

            int[] val = new int[n * m];
            int w1 = m + 1;
            par = new int[n * w1];
            for (int i = 0; i < par.length; i++) par[i] = i;

            for (int i = q - 1; i >= 0; i--) {
                int r0 = R[i], c0 = C[i], p = P[i];
                int p2 = p * p;
                int rLo = Math.max(0, r0 - p), rHi = Math.min(n - 1, r0 + p);
                for (int r = rLo; r <= rHi; r++) {
                    int dr = r - r0;
                    int rem = p2 - dr * dr;
                    int w = (int) Math.sqrt(rem);
                    while (w * w > rem) w--;
                    while ((w + 1) * (w + 1) <= rem) w++;
                    int lo = Math.max(0, c0 - w), hi = Math.min(m - 1, c0 + w);
                    int base = r * w1;
                    int c = find(base + lo);
                    int end = base + hi;
                    while (c <= end) {
                        int col = c - base;
                        int dc = col - c0;
                        val[r * m + col] = rem - dc * dc + 1;
                        par[c] = c + 1;
                        c = find(c + 1);
                    }
                }
            }

            StringBuilder sb = new StringBuilder();
            for (int r = 0; r < n; r++) {
                for (int c = 0; c < m; c++) {
                    if (c > 0) sb.append(' ');
                    sb.append(val[r * m + c]);
                }
                sb.append('\n');
            }
            out.print(sb);
        }
        out.flush();
    }
}