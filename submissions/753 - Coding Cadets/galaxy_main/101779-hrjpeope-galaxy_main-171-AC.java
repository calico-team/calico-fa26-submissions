
import java.io.*;
import java.util.*;

public class five {

    static int n, m;
    static char[][] grid;
    static int[] comp;

    static int[] dr = {-1, 1, 0, 0};
    static int[] dc = {0, 0, -1, 1};

  
    static boolean active(char ch, int mode) {

        if (ch == '.') {
            return true;
        }

        if (mode == 0 && ch == 'B') {
            return true;
        }

        if (mode == 1 && ch == 'R') {
            return true;
        }

        return false;
    }

    
    static void bfs(int start, int id) {

        Queue<Integer> q = new ArrayDeque<>();

        q.add(start);
        comp[start] = id;

        while (!q.isEmpty()) {

            int current = q.poll();

            int cell = current / 2;
            int mode = current % 2;

            int r = cell / m;
            int c = cell % m;

            // Check four directions
            for (int i = 0; i < 4; i++) {

                int nr = r + dr[i];
                int nc = c + dc[i];

                if (nr >= 0 && nr < n &&
                    nc >= 0 && nc < m) {

                    // Check if next tile is active
                    if (active(grid[nr][nc], mode)) {

                        int next = (nr * m + nc) * 2 + mode;

                        if (comp[next] == -1) {

                            comp[next] = id;
                            q.add(next);
                        }
                    }
                }
            }

          
            if (grid[r][c] == '.') {

                int next = cell * 2 + (1 - mode);

                if (comp[next] == -1) {

                    comp[next] = id;
                    q.add(next);
                }
            }
        }
    }

    public static void main(String[] args) throws IOException {

        BufferedReader br = new BufferedReader(
                new InputStreamReader(System.in));

        StringBuilder out = new StringBuilder();

        int t = Integer.parseInt(br.readLine().trim());

        while (t-- > 0) {

            StringTokenizer st = new StringTokenizer(br.readLine());

            n = Integer.parseInt(st.nextToken());
            m = Integer.parseInt(st.nextToken());
            int q = Integer.parseInt(st.nextToken());

            grid = new char[n][m];

            for (int i = 0; i < n; i++) {
                grid[i] = br.readLine().trim().toCharArray();
            }

          
            comp = new int[n * m * 2];

            Arrays.fill(comp, -1);

            int id = 0;

          
            for (int ri = 0; ri < n; ri++) {

                for (int c = 0; c < m; c++) {

                    for (int mode = 0; mode < 2; mode++) {

                        if (active(grid[ri][c], mode)) {

                            int start = (ri * m + c) * 2 + mode;

                            if (comp[start] == -1) {

                                bfs(start, id);
                                id++;
                            }
                        }
                    }
                }
            }

           
            while (q-- > 0) {

                st = new StringTokenizer(br.readLine());

                int r1 = Integer.parseInt(st.nextToken());
                int c1 = Integer.parseInt(st.nextToken());

                int r2 = Integer.parseInt(st.nextToken());
                int c2 = Integer.parseInt(st.nextToken());

              
                int start = (r1 * m + c1) * 2;

             
                int mode = 0;

                if (grid[r2][c2] == 'R') {
                    mode = 1;
                }

               
                int end = (r2 * m + c2) * 2 + mode;

                if (comp[start] == comp[end]) {
                    out.append("yes\n");
                } else {
                    out.append("no\n");
                }
            }
        }

        System.out.print(out);
    }
}
