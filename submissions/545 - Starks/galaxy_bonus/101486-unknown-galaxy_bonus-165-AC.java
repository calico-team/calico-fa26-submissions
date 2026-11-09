import java.io.*;
import java.util.*;

public class Solution6 {
    static BufferedReader br;
    static StringTokenizer st;

    static String next() throws IOException {
        while (st == null || !st.hasMoreTokens()) {
            String line = br.readLine();
            if (line == null) return null;
            st = new StringTokenizer(line);
        }
        return st.nextToken();
    }

    static int nextInt() throws IOException {
        return Integer.parseInt(next());
    }

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in), 1 << 16);
        StringBuilder out = new StringBuilder();

        int T = nextInt();
        while (T-- > 0) {
            int n = nextInt(), m = nextInt(), q = nextInt();
            int total = n * m;
            char[] g = new char[total];
            for (int i = 0; i < n; i++) {
                String row = next();
                row.getChars(0, m, g, i * m);
            }

            // node id = 2*cell + mode ; mode 0 = blue, mode 1 = red
            boolean[] act = new boolean[2 * total];
            for (int c = 0; c < total; c++) {
                act[2 * c] = g[c] != 'R';       // blue mode: active unless R
                act[2 * c + 1] = g[c] != 'B';   // red mode: active unless B
            }

            int[] comp = new int[2 * total];
            Arrays.fill(comp, -1);
            int[] stack = new int[2 * total];
            int cid = 0;

            for (int s = 0; s < 2 * total; s++) {
                if (!act[s] || comp[s] != -1) continue;
                comp[s] = cid;
                int sp = 0;
                stack[sp++] = s;
                while (sp > 0) {
                    int u = stack[--sp];
                    int c = u >> 1, mode = u & 1;
                    int i = c / m, j = c % m;

                    // spin on a normal tile
                    if (g[c] == '.') {
                        int v = u ^ 1;
                        if (comp[v] == -1) { comp[v] = cid; stack[sp++] = v; }
                    }
                    // moves within the same mode
                    if (i > 0) {
                        int v = 2 * (c - m) + mode;
                        if (act[v] && comp[v] == -1) { comp[v] = cid; stack[sp++] = v; }
                    }
                    if (i < n - 1) {
                        int v = 2 * (c + m) + mode;
                        if (act[v] && comp[v] == -1) { comp[v] = cid; stack[sp++] = v; }
                    }
                    if (j > 0) {
                        int v = 2 * (c - 1) + mode;
                        if (act[v] && comp[v] == -1) { comp[v] = cid; stack[sp++] = v; }
                    }
                    if (j < m - 1) {
                        int v = 2 * (c + 1) + mode;
                        if (act[v] && comp[v] == -1) { comp[v] = cid; stack[sp++] = v; }
                    }
                }
                cid++;
            }

            for (int k = 0; k < q; k++) {
                int rs = nextInt(), cs = nextInt(), re = nextInt(), ce = nextInt();
                int sc = comp[2 * (rs * m + cs)];   // start in blue mode
                int e = re * m + ce;
                boolean ok = (act[2 * e] && comp[2 * e] == sc)
                          || (act[2 * e + 1] && comp[2 * e + 1] == sc);
                out.append(ok ? "YES\n" : "NO\n");
            }
        }
        System.out.print(out);
    }
}