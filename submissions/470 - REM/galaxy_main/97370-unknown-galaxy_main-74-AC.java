import java.io.*;
//import java.util.Arrays;
import java.util.Stack;

class Solution {
    /**
     * Return an array of Q strings, the i-th of which is "YES"
     * if Big Ben can travel from start[i] to end[i], and "NO"
     * otherwise.
     *
     * N: the number of rows in the grid
     * M: the number of columns in the grid
     * Q: the number of queries
     * G: the grid, where each tile is 'R', 'B', or '.'
     * start: the {row, column} of the starting tile of each query
     * end: the {row, column} of the ending tile of each query
     */
    static void solve(int N, int M, int Q, String[] G, int[][] start, int[][] end) {
        boolean[][] possible = new boolean[N][M];
        possible[N-1][M-1] = true;
        Stack<int[]> s = new Stack<>();
        s.push(new int[] {N-1,M-1});
        while (!s.isEmpty()) {
            //System.out.println("Size: " + s.size());
            //System.out.println(Arrays.toString(s.peek()));
            int[] pair = s.pop();
            try {
                if (!possible[pair[0]][pair[1]-1] && !(((G[pair[0]].charAt(pair[1]) == 'R' && G[pair[0]].charAt(pair[1]-1) == 'B')) || (((G[pair[0]].charAt(pair[1]) == 'B' && G[pair[0]].charAt(pair[1]-1) == 'R'))))) {
                    possible[pair[0]][pair[1]-1] = true;
                    s.push(new int[]{pair[0], pair[1]-1});
                }
            } catch (IndexOutOfBoundsException e) {}
            try {
                if (!possible[pair[0]][pair[1]+1] && !(((G[pair[0]].charAt(pair[1]) == 'R' && G[pair[0]].charAt(pair[1]+1) == 'B')) || (((G[pair[0]].charAt(pair[1]) == 'B' && G[pair[0]].charAt(pair[1]+1) == 'R'))))) {
                    possible[pair[0]][pair[1]+1] = true;
                    s.push(new int[]{pair[0], pair[1]+1});
                }
            } catch (IndexOutOfBoundsException e) {}
            try {
                if (!possible[pair[0]-1][pair[1]] && !(((G[pair[0]].charAt(pair[1]) == 'R' && G[pair[0]-1].charAt(pair[1]) == 'B')) || (((G[pair[0]].charAt(pair[1]) == 'B' && G[pair[0]-1].charAt(pair[1]) == 'R'))))) {
                    possible[pair[0]-1][pair[1]] = true;
                    s.push(new int[]{pair[0] - 1, pair[1]});
                }
            } catch (IndexOutOfBoundsException e) {}
            try {
                if (!possible[pair[0]+1][pair[1]] && !(((G[pair[0]].charAt(pair[1]) == 'R' && G[pair[0]+1].charAt(pair[1]) == 'B')) || (((G[pair[0]].charAt(pair[1]) == 'B' && G[pair[0]+1].charAt(pair[1]) == 'R'))))) {
                    possible[pair[0]+1][pair[1]] = true;
                    s.push(new int[]{pair[0] + 1, pair[1]});
                }
            } catch (IndexOutOfBoundsException e) {}
        }
        for (int i = 0; i < Q; i++) {
            int r = start[i][0];
            int c = start[i][1];
            if (possible[r][c]) {
                out.println("YES");
            } else {
                out.println("NO");
            }
        }
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

            solve(N, M, Q, G, start, end);
            /*for (String s : solve(N, M, Q, G, start, end)) {
                out.println(s);
            }*/
        }
        out.flush();
    }
}
