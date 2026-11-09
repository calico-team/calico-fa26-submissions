import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.StringTokenizer;

public class Solution3 {
    // Iterative path-halving DSU find to jump over already-painted cells in row r
    static int findNext(int[] nextCol, int rowOffset, int c) {
        int curr = rowOffset + c;
        while (nextCol[curr] != c) {
            int nextC = nextCol[curr];
            int nextIdx = rowOffset + nextC;
            nextCol[curr] = nextCol[nextIdx]; // Path halving
            c = nextC;
            curr = nextIdx;
        }
        return c;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = null;

        String firstLine = br.readLine();
        if (firstLine == null) return;
        int T = Integer.parseInt(firstLine.trim());

        StringBuilder out = new StringBuilder();

        for (int t = 0; t < T; t++) {
            while (st == null || !st.hasMoreTokens()) {
                st = new StringTokenizer(br.readLine());
            }
            int N = Integer.parseInt(st.nextToken());
            int M = Integer.parseInt(st.nextToken());
            int Q = Integer.parseInt(st.nextToken());

            int[] R = new int[Q];
            int[] C = new int[Q];
            int[] P = new int[Q];

            for (int i = 0; i < Q; i++) {
                while (st == null || !st.hasMoreTokens()) {
                    st = new StringTokenizer(br.readLine());
                }
                R[i] = Integer.parseInt(st.nextToken());
                C[i] = Integer.parseInt(st.nextToken());
                P[i] = Integer.parseInt(st.nextToken());
            }

            // Flatten N x (M + 1) so each row has a sentinel column M at the right end
            int stride = M + 1;
            int totalSize = N * stride;
            int[] ans = new int[totalSize];
            int[] nextCol = new int[totalSize];

            // Initialize each cell to point to its own column c
            for (int r = 0; r < N; r++) {
                int rowOffset = r * stride;
                for (int c = 0; c <= M; c++) {
                    nextCol[rowOffset + c] = c;
                }
            }

            // Process earthquakes in REVERSE chronological order (Q - 1 down to 0)
            for (int i = Q - 1; i >= 0; i--) {
                int r0 = R[i];
                int c0 = C[i];
                long p = P[i];
                long pSq = p * p;

                int rStart = r0 - (int) p;
                int rEnd = r0 + (int) p;

                for (int r = rStart; r <= rEnd; r++) {
                    long dr = r - r0;
                    long remSq = pSq - dr * dr;
                    int dc = (int) Math.sqrt(remSq);

                    int cStart = c0 - dc;
                    int cEnd = c0 + dc;
                    int rowOffset = r * stride;

                    // Jump across unpainted cells in [cStart, cEnd]
                    int c = findNext(nextCol, rowOffset, cStart);
                    while (c <= cEnd) {
                        long distSq = dr * dr + (long) (c - c0) * (c - c0);
                        ans[rowOffset + c] = (int) (pSq - distSq + 1);

                        // Mark column c as painted by pointing it to the next unpainted column >= c + 1
                        nextCol[rowOffset + c] = findNext(nextCol, rowOffset, c + 1);
                        c = nextCol[rowOffset + c];
                    }
                }
            }

            // Format output grid for this test case
            for (int r = 0; r < N; r++) {
                int rowOffset = r * stride;
                for (int c = 0; c < M; c++) {
                    if (c > 0) out.append(' ');
                    out.append(ans[rowOffset + c]);
                }
                out.append('\n');
            }
        }

        System.out.print(out);
    }
}