import java.io.*;
import java.util.*;

class Solution {


    public static int[][] solve(int N, int M, int Q, List<int[]> earthquakes) {
        int[][] ans = new int[N][M];
        // Per-row DSU: parent[r][c] = next unpainted column >= c (M means none).
        int[][] parent = new int[N][M + 1];
        for (int r = 0; r < N; r++) {
            for (int c = 0; c <= M; c++) parent[r][c] = c;
        }

        for (int i = Q - 1; i >= 0; i--) {
            int R = earthquakes.get(i)[0];
            int C = earthquakes.get(i)[1];
            int P = earthquakes.get(i)[2];
            int P2 = P * P;
            int base = P2 + 1;

            for (int r = R - P; r <= R + P; r++) {
                int dr2 = (r - R) * (r - R);
                int rem = P2 - dr2;
                int w = isqrt(rem);
                int L = C - w;
                int Right = C + w;

                int[] prow = parent[r];
                int c = find(prow, L);
                while (c <= Right) {
                    int dc = c - C;
                    ans[r][c] = base - dr2 - dc * dc;
                    prow[c] = c + 1;
                    c = find(prow, c + 1);
                }
            }
        }
        return ans;
    }

    static int find(int[] p, int x) {
        while (p[x] != x) {
            p[x] = p[p[x]];
            x = p[x];
        }
        return x;
    }

    static int isqrt(int n) {
        int w = (int) Math.sqrt(n);
        while ((long) (w + 1) * (w + 1) <= n) w++;
        while ((long) w * w > n) w--;
        return w;
    }

    static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    static PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));

    public static void main(String[] args) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        int T = Integer.parseInt(st.nextToken());
        while (T-- > 0) {
            st = new StringTokenizer(in.readLine());
            int N = Integer.parseInt(st.nextToken());
            int M = Integer.parseInt(st.nextToken());
            int Q = Integer.parseInt(st.nextToken());
            List<int[]> earthquakes = new ArrayList<>(Q);
            for (int i = 0; i < Q; i++) {
                st = new StringTokenizer(in.readLine());
                int R = Integer.parseInt(st.nextToken());
                int C = Integer.parseInt(st.nextToken());
                int P = Integer.parseInt(st.nextToken());
                earthquakes.add(new int[]{R, C, P});
            }
            int[][] answer = solve(N, M, Q, earthquakes);
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    if (j > 0) out.print(' ');
                    out.print(answer[i][j]);
                }
                out.println();
            }
        }
        out.flush();
    }
}
