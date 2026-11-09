import java.io.*;

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
    static int[] dr = {-1, 1, 0, 0}, dc = {0, 0, -1, 1};
    static String[] solve(int N, int M, int Q, String[] G, int[][] start, int[][] end) {
        String[] result = new String[Q];
        
        char[][] grid = new char[N][M];
        for (int i = 0; i < N; i++) grid[i] = G[i].toCharArray();
        
        
        for (int i = 0; i < Q; i++) {
            
            boolean[][][] visited = new boolean[N][M][2];
            
            result[i] = dfs(start[i][0], start[i][1], 0, end[i][0], end[i][1], N, M, grid, visited) ? "YES" : "NO";
        }
        
        return result;
    }

    static boolean dfs(int r, int c, int mode, int rEnd, int cEnd, int N, int M, char[][] grid, boolean[][][] visited) {
        if (r == rEnd && c == cEnd) return true;
        

        visited[r][c][mode] = true;

        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i], nc = c + dc[i];

            if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                                                  
                if (
                        (
                            (grid[nr][nc] == '.') || 
                            (grid[nr][nc] == 'B' && mode == 0) || 
                            (grid[nr][nc] == 'R' && mode == 1)
                        ) && 
                        !visited[nr][nc][mode] &&
                        (dfs(nr, nc, mode, rEnd, cEnd, N, M, grid, visited))
                    ) return true;
            }
        }

        if (grid[r][c] == '.') {
            int nextMode = 1 - mode; 
            if (!visited[r][c][nextMode] && dfs(r, c, nextMode, rEnd, cEnd, N, M, grid, visited)) return true;
        }

        return false;
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
