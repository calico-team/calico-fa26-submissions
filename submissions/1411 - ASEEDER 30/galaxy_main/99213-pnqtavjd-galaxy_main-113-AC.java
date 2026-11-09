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
    static String[] solve(int N, int M, int Q, String[] G, int[][] start, int[][] end) {
        int[][] group = new int[N][M];
        int[] rowQueue = new int[N * M];
        int[] colQueue = new int[N * M];
        int[] dr = {-1, 1, 0, 0};
        int[] dc = {0, 0, -1, 1};
        int groupNumber = 0;

        for (int startRow = 0; startRow < N; startRow++) {
            for (int startCol = 0; startCol < M; startCol++) {
                if (group[startRow][startCol] != 0) {
                    continue;
                }

                groupNumber++;
                int front = 0;
                int back = 0;
                rowQueue[back] = startRow;
                colQueue[back] = startCol;
                back++;
                group[startRow][startCol] = groupNumber;

                while (front < back) {
                    int row = rowQueue[front];
                    int col = colQueue[front];
                    front++;

                    for (int d = 0; d < 4; d++) {
                        int newRow = row + dr[d];
                        int newCol = col + dc[d];

                        if (newRow < 0 || newRow >= N || newCol < 0 || newCol >= M
                                || group[newRow][newCol] != 0) {
                            continue;
                        }

                        char current = G[row].charAt(col);
                        char next = G[newRow].charAt(newCol);
                        if ((current == 'R' && next == 'B')
                                || (current == 'B' && next == 'R')) {
                            continue;
                        }

                        group[newRow][newCol] = groupNumber;
                        rowQueue[back] = newRow;
                        colQueue[back] = newCol;
                        back++;
                    }
                }
            }
        }

        String[] answer = new String[Q];
        for (int i = 0; i < Q; i++) {
            answer[i] = group[start[i][0]][start[i][1]] == group[end[i][0]][end[i][1]]
                    ? "YES" : "NO";
        }
        return answer;
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
