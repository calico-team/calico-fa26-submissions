import java.util.*;

/*
* Return an N by M grid displaying the reading of the block seismometers after all earthquakes occur.
*
* N: number of rows in the grid
* M: number of columns in the grid
* Q: number of earthquakes
* earthquakes: a list of arrays {X, Y, P}, where:
*     X: column of the epicenter
*     Y: row of the epicenter
*     P: power of the earthquake
*/
class Solution {

    public static int[][] solve(int N, int M, int Q, List<int[]> earthquakes) {
        int[][] ans = new int[N][M];
        int width = M + 1;
        int[] next = new int[N * width];
        for (int i = 0; i < next.length; i++) next[i] = i;

        class DSU {
            int find(int x) {
                while (next[x] != x) {
                    next[x] = next[next[x]];
                    x = next[x];
                }
                return x;
            }
        }
        DSU dsu = new DSU();

        for (int i = Q - 1; i >= 0; i--) {
            int[] e = earthquakes.get(i);
            int x = e[0], y = e[1], p = e[2];
            for (int r = x - p; r <= x + p; r++) {
                int d = r - x;
                int rest = p * p - d * d;
                int len = (int) Math.sqrt(rest);
                int base = r * width;
                int right = base + y + len;
                int pos = dsu.find(base + y - len);
                while (pos <= right) {
                    int c = pos - base;
                    ans[r][c] = rest - (c - y) * (c - y) + 1;
                    next[pos] = dsu.find(pos + 1);
                    pos = next[pos];
                }
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        while (T-- > 0) {
            int N = sc.nextInt();
            int M = sc.nextInt();
            int Q = sc.nextInt();
            List<int[]> earthquakes = new ArrayList<>();
            for (int i = 0; i < Q; i++) {
                int X = sc.nextInt();
                int Y = sc.nextInt();
                int P = sc.nextInt();
                earthquakes.add(new int[]{X, Y, P});
            }
            int[][] answer = solve(N, M, Q, earthquakes);
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    if (j > 0) System.out.print(" ");
                    System.out.print(answer[i][j]);
                }
                System.out.println();
            }
        }
        sc.close();
    }
}