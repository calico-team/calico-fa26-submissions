import java.io.*;
import java.util.*;

class Solution {
    static final long INF = 1L << 60;
    static final int[] DR = {-1, 1, 0, 0};
    static final int[] DC = {0, 0, -1, 1};


    static String[] solve(int N, int M, int Q, String[] G, int[][] start, int[][] end, int[] K) {
        int V = N * M * 2;
        long[] ans = new long[Q];
        Arrays.fill(ans, INF);

        ArrayList<Integer> all = new ArrayList<>(Q);
        for (int i = 0; i < Q; i++) all.add(i);
        dac(0, M, all, N, M, G, start, end, ans);

        String[] out = new String[Q];
        for (int i = 0; i < Q; i++) {
            out[i] = ans[i] <= K[i] ? "YES" : "NO";
        }
        return out;
    }

    static boolean valid(String[] G, int r, int c, int mode) {
        char ch = G[r].charAt(c);
        if (mode == 0) return ch != 'R'; // blue
        return ch != 'B';               // red
    }

    static int sid(int r, int c, int mode, int M) {
        return (r * M + c) * 2 + mode;
    }

    static int[] bfsFrom(int sr, int sc, int smode, int L, int R, int N, int M, String[] G) {
        int V = N * M * 2;
        int[] dist = new int[V];
        Arrays.fill(dist, -1);
        if (!(L <= sc && sc < R) || !valid(G, sr, sc, smode)) return dist;
        int s = sid(sr, sc, smode, M);
        dist[s] = 0;
        ArrayDeque<Integer> q = new ArrayDeque<>();
        q.add(s);
        while (!q.isEmpty()) {
            int u = q.poll();
            int d = dist[u];
            int mode = u & 1;
            int tmp = u >> 1;
            int r = tmp / M;
            int c = tmp % M;
            if (G[r].charAt(c) == '.') {
                int v = u ^ 1;
                if (dist[v] == -1) {
                    dist[v] = d + 1;
                    q.add(v);
                }
            }
            for (int k = 0; k < 4; k++) {
                int nr = r + DR[k];
                int nc = c + DC[k];
                if (0 <= nr && nr < N && L <= nc && nc < R && valid(G, nr, nc, mode)) {
                    int v = sid(nr, nc, mode, M);
                    if (dist[v] == -1) {
                        dist[v] = d + 1;
                        q.add(v);
                    }
                }
            }
        }
        return dist;
    }

    static void dac(int L, int R, ArrayList<Integer> qs, int N, int M, String[] G,
                    int[][] start, int[][] end, long[] ans) {
        if (qs.isEmpty() || L >= R) return;
        int mid = (L + R) / 2;
        ArrayList<int[]> dists = new ArrayList<>();
        for (int r = 0; r < N; r++) {
            for (int mode = 0; mode < 2; mode++) {
                if (valid(G, r, mid, mode)) {
                    dists.add(bfsFrom(r, mid, mode, L, R, N, M, G));
                }
            }
        }

        ArrayList<Integer> leftQs = new ArrayList<>();
        ArrayList<Integer> rightQs = new ArrayList<>();
        for (int qi : qs) {
            int rs = start[qi][0], cs = start[qi][1];
            int re = end[qi][0], ce = end[qi][1];
            long best = ans[qi];
            int ss = sid(rs, cs, 0, M);
            for (int[] dist : dists) {
                int ds = dist[ss];
                if (ds < 0) continue;
                for (int emode = 0; emode < 2; emode++) {
                    if (!valid(G, re, ce, emode)) continue;
                    int de = dist[sid(re, ce, emode, M)];
                    if (de >= 0) best = Math.min(best, (long) ds + de);
                }
            }
            ans[qi] = best;
            if (cs < mid && ce < mid) leftQs.add(qi);
            else if (cs >= mid && ce >= mid) rightQs.add(qi);
        }

        if (R - L == 1) return;
        dac(L, mid, leftQs, N, M, G, start, end, ans);
        dac(mid, R, rightQs, N, M, G, start, end, ans);
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
            int[] K = new int[Q];
            for (int i = 0; i < Q; i++) {
                temp = in.readLine().trim().split(" ");
                start[i][0] = Integer.parseInt(temp[0]);
                start[i][1] = Integer.parseInt(temp[1]);
                end[i][0] = Integer.parseInt(temp[2]);
                end[i][1] = Integer.parseInt(temp[3]);
                K[i] = Integer.parseInt(temp[4]);
            }

            for (String s : solve(N, M, Q, G, start, end, K)) {
                out.println(s);
            }
        }
        out.flush();
    }
}
