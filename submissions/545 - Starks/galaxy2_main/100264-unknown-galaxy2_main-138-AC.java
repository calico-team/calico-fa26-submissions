import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

public class Solution4 {

    static final int INF = 1_000_000_007;
    static final int[] dr = {-1, 1, 0, 0};
    static final int[] dc = {0, 0, -1, 1};

    static class Query {
        int id, sr, sc, er, ec, k;
        int min_dist;
        
        public Query(int id, int sr, int sc, int er, int ec, int k) {
            this.id = id;
            this.sr = sr;
            this.sc = sc;
            this.er = er;
            this.ec = ec;
            this.k = k;
            this.min_dist = INF;
        }
    }

    static int N, M, Q;
    static char[][] grid;
    
    // Global arrays to prevent memory allocation / GC overhead during recursion
    static int[] qr = new int[80005];
    static int[] qc = new int[80005];
    static int[] qmode = new int[80005];
    static int[][][] dist = new int[15][4005][2];

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
        
        dnc(0, M - 1, queries);

        for (Query q : queries) {
            if (q.min_dist <= q.k) {
                out.println("YES");
            } else {
                out.println("NO");
            }
        }
    }

    static void dnc(int L, int R, List<Query> active_queries) {
        if (L > R || active_queries.isEmpty()) return;

        int mid = L + (R - L) / 2;

        // Run a BFS from every valid state on the mid column
        for (int sr = 0; sr < N; ++sr) {
            for (int smode = 0; smode < 2; ++smode) {
                // Cannot be on a Red tile in Blue mode, nor a Blue tile in Red mode
                if (grid[sr][mid] == 'R' && smode == 0) continue;
                if (grid[sr][mid] == 'B' && smode == 1) continue;

                // Clear the exact block of the global distance array we are going to use
                for (int i = 0; i < N; i++) {
                    for (int j = L; j <= R; j++) {
                        dist[i][j][0] = INF;
                        dist[i][j][1] = INF;
                    }
                }

                int head = 0, tail = 0;
                
                qr[tail] = sr;
                qc[tail] = mid;
                qmode[tail] = smode;
                tail++;
                
                dist[sr][mid][smode] = 0;

                // BFS Traversal bounded by [L, R]
                while (head < tail) {
                    int r = qr[head];
                    int c = qc[head];
                    int mode = qmode[head];
                    head++;
                    
                    int d = dist[r][c][mode];

                    // Spatial moves taking 1 second
                    for (int i = 0; i < 4; ++i) {
                        int nr = r + dr[i];
                        int nc = c + dc[i];
                        
                        if (nr >= 0 && nr < N && nc >= L && nc <= R) {
                            if (grid[nr][nc] == '.' || 
                               (grid[nr][nc] == 'B' && mode == 0) || 
                               (grid[nr][nc] == 'R' && mode == 1)) {
                                
                                if (dist[nr][nc][mode] > d + 1) {
                                    dist[nr][nc][mode] = d + 1;
                                    qr[tail] = nr;
                                    qc[tail] = nc;
                                    qmode[tail] = mode;
                                    tail++;
                                }
                            }
                        }
                    }

                    // Spin action taking 1 second
                    if (grid[r][c] == '.') {
                        int nmode = 1 - mode;
                        if (dist[r][c][nmode] > d + 1) {
                            dist[r][c][nmode] = d + 1;
                            qr[tail] = r;
                            qc[tail] = c;
                            qmode[tail] = nmode;
                            tail++;
                        }
                    }
                }

                // Update shortest distance for ALL active queries through this state on mid
                for (Query q : active_queries) {
                    int d1 = dist[q.sr][q.sc][0]; // Start is always Blue (mode 0)
                    int d2 = Math.min(dist[q.er][q.ec][0], dist[q.er][q.ec][1]); // End can be any mode
                    
                    if (d1 != INF && d2 != INF) {
                        q.min_dist = Math.min(q.min_dist, d1 + d2);
                    }
                }
            }
        }

        List<Query> left_queries = new ArrayList<>();
        List<Query> right_queries = new ArrayList<>();

        // Route unresolved queries to subproblems
        for (Query q : active_queries) {
            // Optimization: If a query has already found a path <= k, we no longer need to solve it
            if (q.min_dist <= q.k) continue;

            if (q.sc < mid && q.ec < mid) {
                left_queries.add(q);
            } else if (q.sc > mid && q.ec > mid) {
                right_queries.add(q);
            }
        }

        dnc(L, mid - 1, left_queries);
        dnc(mid + 1, R, right_queries);
    }
    
    // Fast I/O Utility
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