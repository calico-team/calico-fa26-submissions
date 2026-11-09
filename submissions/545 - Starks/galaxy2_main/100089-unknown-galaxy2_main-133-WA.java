import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.StringTokenizer;

public class Solution4 {

    static final int INF = 1_000_000_007;
    static final int[] dr = {-1, 1, 0, 0};
    static final int[] dc = {0, 0, -1, 1};

    static class Query {
        int id, sr, sc, er, ec, k;
        public Query(int id, int sr, int sc, int er, int ec, int k) {
            this.id = id;
            this.sr = sr;
            this.sc = sc;
            this.er = er;
            this.ec = ec;
            this.k = k;
        }
    }

    static int N, M, Q;
    static char[][] grid;
    static boolean[] ans;

    public static void main(String[] args) {
        FastReader in = new FastReader();
        PrintWriter out = new PrintWriter(System.out);

        int T;
        try {
            String tStr = in.next();
            if (tStr == null) return;
            T = Integer.parseInt(tStr);
        } catch (Exception e) {
            return;
        }

        while (T-- > 0) {
            solve(in, out);
        }
        
        out.flush();
    }

    static void solve(FastReader in, PrintWriter out) {
        N = in.nextInt();
        M = in.nextInt();
        Q = in.nextInt();

        grid = new char[N][M];
        for (int i = 0; i < N; ++i) {
            grid[i] = in.next().toCharArray();
        }

        List<Query> queries = new ArrayList<>(Q);
        for (int i = 0; i < Q; ++i) {
            queries.add(new Query(i, in.nextInt(), in.nextInt(), in.nextInt(), in.nextInt(), in.nextInt()));
        }

        ans = new boolean[Q];
        
        dnc(0, M - 1, queries);

        for (int i = 0; i < Q; ++i) {
            if (ans[i]) {
                out.println("YES");
            } else {
                out.println("NO");
            }
        }
    }

    static void dnc(int L, int R, List<Query> active_queries) {
        if (L > R || active_queries.isEmpty()) return;

        int mid = L + (R - L) / 2;

        List<Query> left_queries = new ArrayList<>();
        List<Query> right_queries = new ArrayList<>();
        List<Query> crossing_queries = new ArrayList<>();

        for (Query q : active_queries) {
            if (q.sc < mid && q.ec < mid) {
                left_queries.add(q);
            } else if (q.sc > mid && q.ec > mid) {
                right_queries.add(q);
            } else {
                crossing_queries.add(q);
            }
        }

        // dist[start_row][start_mode][r][c - L][mode]
        int[][][][][] dist = new int[N][2][N][R - L + 1][2];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < N; k++) {
                    for (int m = 0; m <= R - L; m++) {
                        dist[i][j][k][m][0] = INF;
                        dist[i][j][k][m][1] = INF;
                    }
                }
            }
        }

        // Custom Queue arrays to avoid GC overhead of creating millions of Node objects
        int maxQueueSize = N * (R - L + 1) * 2 + 5;
        int[] qr = new int[maxQueueSize];
        int[] qc = new int[maxQueueSize];
        int[] qmode = new int[maxQueueSize];

        // BFS from every cell on the mid column
        for (int sr = 0; sr < N; ++sr) {
            for (int smode = 0; smode < 2; ++smode) {
                // Skip invalid starting states
                if (grid[sr][mid] == 'R' && smode == 0) continue;
                if (grid[sr][mid] == 'B' && smode == 1) continue;

                int head = 0, tail = 0;
                
                qr[tail] = sr;
                qc[tail] = mid;
                qmode[tail] = smode;
                tail++;
                
                dist[sr][smode][sr][mid - L][smode] = 0;

                while (head < tail) {
                    int r = qr[head];
                    int c = qc[head];
                    int mode = qmode[head];
                    head++;
                    
                    int d = dist[sr][smode][r][c - L][mode];

                    // Spatial moves
                    for (int i = 0; i < 4; ++i) {
                        int nr = r + dr[i];
                        int nc = c + dc[i];
                        
                        if (nr >= 0 && nr < N && nc >= L && nc <= R) {
                            if (grid[nr][nc] == '.' || 
                               (grid[nr][nc] == 'B' && mode == 0) || 
                               (grid[nr][nc] == 'R' && mode == 1)) {
                                
                                if (dist[sr][smode][nr][nc - L][mode] > d + 1) {
                                    dist[sr][smode][nr][nc - L][mode] = d + 1;
                                    qr[tail] = nr;
                                    qc[tail] = nc;
                                    qmode[tail] = mode;
                                    tail++;
                                }
                            }
                        }
                    }

                    // Spin action
                    if (grid[r][c] == '.') {
                        int nmode = 1 - mode;
                        if (dist[sr][smode][r][c - L][nmode] > d + 1) {
                            dist[sr][smode][r][c - L][nmode] = d + 1;
                            qr[tail] = r;
                            qc[tail] = c;
                            qmode[tail] = nmode;
                            tail++;
                        }
                    }
                }
            }
        }

        // Answer crossing queries
        for (Query q : crossing_queries) {
            int min_dist = INF;
            // Best path must pass through some (r, mid, mode) on the mid column
            for (int r = 0; r < N; ++r) {
                for (int mode = 0; mode < 2; ++mode) {
                    // Check if path from mid to start is reachable in blue mode (mode 0)
                    if (dist[r][mode][q.sr][q.sc - L][0] != INF) {
                        int d1 = dist[r][mode][q.sr][q.sc - L][0]; 
                        int d2 = Math.min(dist[r][mode][q.er][q.ec - L][0], 
                                          dist[r][mode][q.er][q.ec - L][1]);
                        min_dist = Math.min(min_dist, d1 + d2);
                    }
                }
            }
            if (min_dist <= q.k) {
                ans[q.id] = true;
            }
        }

        dnc(L, mid - 1, left_queries);
        dnc(mid + 1, R, right_queries);
    }
    
    // Fast I/O Template class
    static class FastReader {
        BufferedReader br;
        StringTokenizer st;

        public FastReader() {
            br = new BufferedReader(new InputStreamReader(System.in));
        }

        String next() {
            while (st == null || !st.hasMoreElements()) {
                try {
                    String line = br.readLine();
                    if (line == null) return null;
                    st = new StringTokenizer(line);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }

        int nextInt() {
            return Integer.parseInt(next());
        }
    }
}