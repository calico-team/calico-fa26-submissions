import java.io.*;
import java.util.*;

class Solution {
    /**
     * Return an array of Q strings, the i-th of which is "YES"
     * if Big Ben can travel from start[i] to end[i] within K[i]
     * seconds, and "NO" otherwise.
     *
     * N: the number of rows in the grid
     * M: the number of columns in the grid
     * Q: the number of queries
     * G: the grid, where each tile is 'R', 'B', or '.'
     * start: the {row, column} of the starting tile of each query
     * end: the {row, column} of the ending tile of each query
     * K: the maximum number of seconds allowed for each query
     */
    static String[] solve(int N, int M, int Q, String[] G, int[][] start, int[][] end, int[] K) {
        rows = N;
        cols = M;
        grid = new char[N][];
        for (int r = 0; r < N; r++){
            grid[r] = G[r].toCharArray();
        }
        st = start;
        en = end;

        dist = new int[2*N][2*N*M];
        q = new int[2*N*M];
        best = new int[Q];
        Arrays.fill(best, -1);

        int[] all = new int[Q];
        for (int i = 0; i < Q; i++){
            all[i] = i;
        }
        divide(0, M-1, all, Q);
        String[] ans = new String[Q];
        for (int i = 0; i < Q; i++) {
            if((best[i]!=-1) && (best[i]<=K[i])){
                ans[i]="YES";
            }else{
                ans[i]="NO";
            }
        }
        return ans;
    }

    static int rows;
    static int cols;
    static char[][] grid;
    static int[][] st;
    static int[][] en;
    static int[][] dist;
    static int[] q;
    static int[] best;

    static boolean active(int r, int c, int mode){
        char ch = grid[r][c];
        return (ch == '.')||((ch == 'B') && (mode == 0))||((ch == 'R')&&(mode == 1));
    }

    static int local(int r, int c, int mode, int lo, int w){
        return ((r*w)+(c-lo))*2 + mode;
    }

    static void divide(int lo, int hi, int[] qs, int cnt){
        if ((lo>hi) || (cnt==0)){
            return;
        }
        int mid = (lo+hi)/2;
        int w = hi-lo+1;

        int k = 0;
        for (int r = 0; r < rows; r++){
            for (int mode = 0; mode < 2; mode++){
                if (active(r, mid, mode)){
                    bfs(dist[k], local(r, mid, mode, lo, w), lo, hi, w);
                    k++;
                }
            }
        }

        int[] left = new int[cnt];
        int[] right = new int[cnt];
        int lc = 0;
        int rc = 0;
        for (int i = 0; i < cnt; i++){
            int q = qs[i];
            int sr = st[q][0];
            int sc = st[q][1];
            int er = en[q][0];
            int ec = en[q][1];
            int s = local(sr, sc, 0, lo, w);
            for (int j = 0; j < k; j++){
                int ds = dist[j][s];
                if (ds==-1){
                    continue;
                }
                for (int mode = 0; mode < 2; mode++){
                    if (!active(er, ec, mode)){
                        continue;
                    }
                    int de = dist[j][local(er, ec, mode, lo, w)];
                    if (de==-1){
                        continue;
                    }
                    int cand = ds+de;
                    if ((best[q]==-1)||(cand<best[q])){
                        best[q] = cand;
                    }
                }
            }
            if ((sc<mid)&&(ec<mid)){
                left[lc++] = q;
            } else if ((sc>mid)&&(ec>mid)){
                right[rc++] = q;
            }
        }


        divide(lo, mid-1, left, lc);
        divide(mid+1, hi, right, rc);
    }

    static void bfs(int[] d, int src, int lo, int hi, int w) {
        Arrays.fill(d, 0, rows*w*2, -1);
        int head = 0;
        int tail = 0;
        d[src] = 0;
        q[tail++] = src;
        int[] dr = {1,-1,0,0};
        int[] dc = {0,0,1,-1};


        while (head<tail){
            int cur = q[head++];
            int mode = cur&1;
            int cell = cur>>1;
            int r = cell/w;
            int c = cell%w + lo;
            int nd = d[cur]+1;

            if (grid[r][c]=='.'){
                int nxt = cur^1;
                if (d[nxt]==-1){
                    d[nxt]=nd;
                    q[tail++]=nxt;
                }
            }

            for (int t = 0; t < 4; t++) {
                int nr = r+dr[t];
                int nc = c+dc[t];
                if ((nr < 0)||(nr >= rows)||(nc < lo)||(nc > hi)){
                    continue;
                }
                if (!active(nr, nc, mode)){
                    continue;
                }
                int nxt = local(nr, nc, mode, lo, w);
                if (d[nxt]==-1){
                    d[nxt] = nd;
                    q[tail++] = nxt;
                }
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
            int[] K = new int[Q];
            for (int i = 0; i < Q; i++) {
                temp = in.readLine().trim().split(" ");
                start[i][0] = Integer.parseInt(temp[0]);
                start[i][1] = Integer.parseInt(temp[1]);
                end[i][0] = Integer.parseInt(temp[2]);
                end[i][1] = Integer.parseInt(temp[3]);
                K[i] = Integer.parseInt(temp[4]);
            }

            for (String s : solve(N, M, Q, G, start, end, K)) {
                out.println(s);
            }
        }
        out.flush();
    }
}