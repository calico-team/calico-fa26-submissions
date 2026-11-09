import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.StringTokenizer;

public class Solution2 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = null;

        String phase = br.readLine();
        if (phase == null) return;
        phase = phase.trim();

        while (st == null || !st.hasMoreTokens()) {
            st = new StringTokenizer(br.readLine());
        }
        int N = Integer.parseInt(st.nextToken());

        StringBuilder out = new StringBuilder();

        if (phase.equals("FIRST")) {
            // Flat adjacency list for N vertices and 2*(N-1) directed edge entries
            int[] head = new int[N + 1];
            int[] to = new int[2 * N];
            int[] next = new int[2 * N];
            int edgeIdx = 1;

            for (int i = 0; i < N - 1; i++) {
                while (st == null || !st.hasMoreTokens()) {
                    st = new StringTokenizer(br.readLine());
                }
                int u = Integer.parseInt(st.nextToken());
                int v = Integer.parseInt(st.nextToken());

                to[edgeIdx] = v;
                next[edgeIdx] = head[u];
                head[u] = edgeIdx++;

                to[edgeIdx] = u;
                next[edgeIdx] = head[v];
                head[v] = edgeIdx++;
            }

            // Root the tree at vertex 1 using iterative BFS to find parent[2..N]
            int[] parent = new int[N + 1];
            int[] queue = new int[N + 1];
            int qHead = 0, qTail = 0;

            queue[qTail++] = 1;
            parent[1] = -1; // Mark root as visited

            while (qHead < qTail) {
                int u = queue[qHead++];
                for (int e = head[u]; e != 0; e = next[e]) {
                    int v = to[e];
                    if (parent[v] == 0) {
                        parent[v] = u;
                        queue[qTail++] = v;
                    }
                }
            }

            // Compute A[1] as the XOR checksum of A[2]..A[N]
            int xorChecksum = 0;
            for (int i = 2; i <= N; i++) {
                xorChecksum ^= parent[i];
            }

            // Output A[1] A[2] ... A[N]
            out.append(xorChecksum);
            for (int i = 2; i <= N; i++) {
                out.append(' ').append(parent[i]);
            }
            out.append('\n');

        } else {
            // SECOND PHASE: Read A[1..N], recover any erased value, and print edges
            int[] A = new int[N + 1];
            int missingIdx = -1;
            int xorSum = 0;

            for (int i = 1; i <= N; i++) {
                while (st == null || !st.hasMoreTokens()) {
                    st = new StringTokenizer(br.readLine());
                }
                A[i] = Integer.parseInt(st.nextToken());
                if (A[i] == -1) {
                    missingIdx = i;
                } else {
                    xorSum ^= A[i];
                }
            }

            // If a parent value A[k] (for k >= 2) was erased, xorSum equals the missing A[k]!
            if (missingIdx >= 2) {
                A[missingIdx] = xorSum;
            }

            // Output all N - 1 edges (i, parent[i]) for i = 2..N
            for (int i = 2; i <= N; i++) {
                out.append(i).append(' ').append(A[i]).append('\n');
            }
        }

        System.out.print(out);
    }
}