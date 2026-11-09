import java.util.*;


class Solution {

    public static int[][] solve(int N, int M, int Q, List<int[]> earthquakes) {
        int[][] ans = new int[N][M];
        int width = M + 1;
        int[] next = new int[N * width];
        for (int i = 0; i < next.length; i++) next[i] = i;

        for (int i = Q - 1; i >= 0; i--) {
            int[] e = earthquakes.get(i);
            int x = e[0], y = e[1], p = e[2];
            for (int r = x - p; r <= x + p; r++) {
                int d = r - x;
                int rest = p * p - d * d;
                int len = (int) Math.sqrt(rest);
                int base = r * width;
                int right = base + y + len;
                int pos = base + y - len;
                while (pos <= right) {
                    while (next[pos] != pos) {
                        next[pos] = next[next[pos]];
                        pos = next[pos];
                    }
                    if (pos > right) break;

                    int c = pos - base;
                    ans[r][c] = rest - (c - y) * (c - y) + 1;
                    next[pos] = pos + 1;
                    pos++;
                }
            }
        }
        return ans;
    }

    public static void main(String[] args) throws Exception {
        java.io.BufferedReader br = new java.io.BufferedReader(
                new java.io.InputStreamReader(System.in));
        StringBuilder output = new StringBuilder();
        int T = Integer.parseInt(br.readLine().trim());
        while (T-- > 0) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int N = Integer.parseInt(st.nextToken());
            int M = Integer.parseInt(st.nextToken());
            int Q = Integer.parseInt(st.nextToken());
            List<int[]> earthquakes = new ArrayList<>();
            for (int i = 0; i < Q; i++) {
                st = new StringTokenizer(br.readLine());
                int X = Integer.parseInt(st.nextToken());
                int Y = Integer.parseInt(st.nextToken());
                int P = Integer.parseInt(st.nextToken());
                earthquakes.add(new int[]{X, Y, P});
            }
            int[][] answer = solve(N, M, Q, earthquakes);
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    if (j > 0) output.append(' ');
                    output.append(answer[i][j]);
                }
                output.append('\n');
            }
        }
        System.out.print(output);
    }
}
