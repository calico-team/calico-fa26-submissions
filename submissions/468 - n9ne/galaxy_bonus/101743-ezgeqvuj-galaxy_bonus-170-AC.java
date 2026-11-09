import java.io.*;
import java.util.*;

public class problem_5b1 {
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

    static void union(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) par[a] = b;
    }

    static BufferedReader br;
    static StringTokenizer st;

    static String next() throws IOException {
        while (st == null || !st.hasMoreTokens()) {
            st = new StringTokenizer(br.readLine());
        }
        return st.nextToken();
    }

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in), 1 << 16);
        PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
        int t = Integer.parseInt(next());

        while (t-- > 0) {
            int n = Integer.parseInt(next());
            int m = Integer.parseInt(next());
            int q = Integer.parseInt(next());

            char[][] g = new char[n][];
            for (int i = 0; i < n; i++) g[i] = next().toCharArray();

            par = new int[2 * n * m];
            for (int i = 0; i < par.length; i++) par[i] = i;

            for (int r = 0; r < n; r++) {
                for (int c = 0; c < m; c++) {
                    int id = r * m + c;
                    char ch = g[r][c];
                    if (ch == '.') union(2 * id, 2 * id + 1);

                    for (int mode = 0; mode < 2; mode++) {
                        if (!active(ch, mode)) continue;
                        if (c + 1 < m && active(g[r][c + 1], mode)) {
                            union(2 * id + mode, 2 * (id + 1) + mode);
                        }
                        if (r + 1 < n && active(g[r + 1][c], mode)) {
                            union(2 * id + mode, 2 * (id + m) + mode);
                        }
                    }
                }
            }

            for (int i = 0; i < q; i++) {
                int rs = Integer.parseInt(next());
                int cs = Integer.parseInt(next());
                int re = Integer.parseInt(next());
                int ce = Integer.parseInt(next());
                int s = find(2 * (rs * m + cs));
                int e = re * m + ce;
                boolean ok = find(2 * e) == s || find(2 * e + 1) == s;
                out.println(ok ? "YES" : "NO");
            }
        }
        out.flush();
    }

    static boolean active(char ch, int mode) {
        if (ch == '.') return true;
        if (ch == 'B') return mode == 0;
        return mode == 1; 
    }
}