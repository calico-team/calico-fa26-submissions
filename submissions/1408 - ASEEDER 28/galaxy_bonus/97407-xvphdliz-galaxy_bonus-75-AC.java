import java.io.*;
import java.util.*;

class Solution {
    static final int[] DR = {-1, 1, 0, 0};
    static final int[] DC = {0, 0, -1, 1};

    
    static String[] solve(int N, int M, int Q, String[] G, int[][] start, int[][] end) {
        int V = N * M * 2;
        int[] parent = new int[V];
        int[] rank = new int[V];
        for (int i = 0; i < V; i++) parent[i] = i;

        for (int r = 0; r < N; r++) {
            for (int c = 0; c < M; c++) {
                char ch = G[r].charAt(c);
                if (ch == '.') {
                    unite(parent, rank, sid(r, c, 0, M), sid(r, c, 1, M));
                }
                for (int mode = 0; mode < 2; mode++) {
                    if (!valid(ch, mode)) continue;
                    int u = sid(r, c, mode, M);
                    for (int k = 0; k < 4; k++) {
                        int nr = r + DR[k];
                        int nc = c + DC[k];
                        if (0 <= nr && nr < N && 0 <= nc && nc < M && valid(G[nr].charAt(nc), mode)) {
                            unite(parent, rank, u, sid(nr, nc, mode, M));
                        }
                    }
                }
            }
        }

        String[] out = new String[Q];
        for (int i = 0; i < Q; i++) {
            int rs = start[i][0], cs = start[i][1];
            int re = end[i][0], ce = end[i][1];
            int src = find(parent, sid(rs, cs, 0, M));
            boolean ok = false;
            char ech = G[re].charAt(ce);
            if (valid(ech, 0) && find(parent, sid(re, ce, 0, M)) == src) ok = true;
            if (valid(ech, 1) && find(parent, sid(re, ce, 1, M)) == src) ok = true;
            out[i] = ok ? "YES" : "NO";
        }
        return out;
    }

    static boolean valid(char ch, int mode) {
        if (mode == 0) return ch != 'R'; // blue mode
        return ch != 'B';               // red mode
    }

    static int sid(int r, int c, int mode, int M) {
        return (r * M + c) * 2 + mode;
    }

    static int find(int[] parent, int x) {
        while (parent[x] != x) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }

    static void unite(int[] parent, int[] rank, int a, int b) {
        a = find(parent, a);
        b = find(parent, b);
        if (a == b) return;
        if (rank[a] < rank[b]) {
            int t = a; a = b; b = t;
        }
        parent[b] = a;
        if (rank[a] == rank[b]) rank[a]++;
    }

    static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    static PrintWriter out = new PrintWriter(System.out);

    public static void main(String[] args) throws IOException {
        int T = Integer.parseInt(in.readLine().trim());
        for (int t = 0; t < T; t++) {
            String[] temp = in.readLine().trim().split(" ");
            int N = Integer.parseInt(temp[0]);
            int M = Integer.parseInt(temp[1]);
            int Q = Integer.parseInt(temp[2]);
            String[] G = new String[N];
            for (int i = 0; i < N; i++) {
                G[i] = in.readLine().trim();
            }
            int[][] start = new int[Q][2];
            int[][] end = new int[Q][2];
            for (int i = 0; i < Q; i++) {
                temp = in.readLine().trim().split(" ");
                start[i][0] = Integer.parseInt(temp[0]);
                start[i][1] = Integer.parseInt(temp[1]);
                end[i][0] = Integer.parseInt(temp[2]);
                end[i][1] = Integer.parseInt(temp[3]);
            }

            for (String s : solve(N, M, Q, G, start, end)) {
                out.println(s);
            }
        }
        out.flush();
    }
}
