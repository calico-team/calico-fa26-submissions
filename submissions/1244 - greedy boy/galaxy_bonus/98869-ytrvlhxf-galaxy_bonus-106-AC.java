import java.util.*;
import java.io.*;
public class Main {
    static class Kattio extends PrintWriter {
        private BufferedReader r;
        private StringTokenizer st;

        public Kattio() {
            super(new BufferedWriter(new OutputStreamWriter(System.out)));
            r = new BufferedReader(new InputStreamReader(System.in));
        }

        public Kattio(String filename) throws IOException {
            super(new BufferedWriter(new FileWriter(filename + ".out")));
            r = new BufferedReader(new FileReader(filename + ".in"));
        }

        public String next() {
            try {
                while (st == null || !st.hasMoreTokens()) {
                    String line = r.readLine();
                    if (line == null) {
                        throw new NoSuchElementException("Unexpected end of input");
                    }
                    st = new StringTokenizer(line);
                }
                return st.nextToken();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        public int nextInt() {
            return Integer.parseInt(next());
        }

        public long nextLong() {
            return Long.parseLong(next());
        }
    }

    public static void main(String[] args) throws IOException {
        Kattio io = new Kattio();
        int t = io.nextInt();
        for (int test = 0; test < t; test++) {
            int n = io.nextInt();
            int m = io.nextInt();
            int q = io.nextInt();
            char[][] grid = new char[n][m];
            for (int i = 0; i < n; i++) {
                grid[i] = io.next().toCharArray();
            }

            int[][] part = new int[n][m];
            for (int[] row : part) {
                Arrays.fill(row, -1);
            }

            int[] dr = {0, 0, 1, -1};
            int[] dc = {1, -1, 0, 0};
            int id = 0;
            for (int r = 0; r < n; r++) {
                for (int c = 0; c < m; c++) {
                    if (part[r][c] != -1) {
                        continue;
                    }
                    ArrayDeque<int[]> queue = new ArrayDeque<>();
                    queue.add(new int[]{r, c});
                    part[r][c] = id;

                    while (!queue.isEmpty()) {
                        int[] pos = queue.poll();
                        int row = pos[0];
                        int col = pos[1];
                        for (int d = 0; d < 4; d++) {
                            int nr = row + dr[d];
                            int nc = col + dc[d];
                            if (nr < 0 || nr >= n || nc < 0 || nc >= m) {
                                continue;
                            }
                            if (part[nr][nc] != -1) {
                                continue;
                            }
                            char current = grid[row][col];
                            char next = grid[nr][nc];
                            if ((current == 'R' && next == 'B') || (current == 'B' && next == 'R')) {
                                continue;
                            }
                            part[nr][nc] = id;
                            queue.add(new int[]{nr, nc});
                        }
                    }
                    id++;
                }
            }
            for (int i = 0; i < q; i++) {
                int r1 = io.nextInt();
                int c1 = io.nextInt();
                int r2 = io.nextInt();
                int c2 = io.nextInt();
                if (part[r1][c1] == part[r2][c2]) {
                    io.println("YES");
                } else {
                    io.println("NO");
                }
            }
        }
        io.close();
    }
}