import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class Solution5 {

    static int[] A, V, D, vtx, ans;
    static int[] head, next, to;
    static int edgeCount;
    static int[] vis, path, q, stack, edgeIdx;
    
    // Flat arrays for Trie to eliminate GC overhead
    static int[][] nxt;
    static int[] cnt;
    static int nodesCnt;

    public static void main(String[] args) {
        FastReader in = new FastReader();
        PrintWriter out = new PrintWriter(System.out);

        // Pre-allocate to prevent GC (max N is 200,000)
        int MAX_N = 200005;
        A = new int[MAX_N];
        V = new int[MAX_N];
        D = new int[MAX_N];
        vtx = new int[MAX_N];
        ans = new int[MAX_N];
        head = new int[MAX_N];
        next = new int[MAX_N];
        to = new int[MAX_N];
        vis = new int[MAX_N];
        path = new int[MAX_N];
        q = new int[MAX_N];
        stack = new int[MAX_N];
        edgeIdx = new int[MAX_N];
        
        // 10M nodes is well beyond enough since tree paths share identical binary prefixes
        nxt = new int[10000005][2];
        cnt = new int[10000005];

        String tStr = in.next();
        if (tStr == null) return;
        int T = Integer.parseInt(tStr);

        while (T-- > 0) {
            int N = in.nextInt();
            
            edgeCount = 0;
            for (int i = 1; i <= N; i++) {
                head[i] = 0;
                vis[i] = 0;
            }

            // Build reverse adjacency list (tree edges pointing outward from cycle)
            for (int i = 1; i <= N; i++) {
                A[i] = in.nextInt();
                edgeCount++;
                to[edgeCount] = i;
                next[edgeCount] = head[A[i]];
                head[A[i]] = edgeCount;
            }

            for (int i = 1; i <= N; i++) {
                V[i] = in.nextInt();
            }

            // Initialize global Trie root for this test case
            nxt[0][0] = nxt[0][1] = 0;
            cnt[0] = 0;
            nodesCnt = 1;

            // Find cycles and process components
            for (int i = 1; i <= N; i++) {
                if (vis[i] == 0) {
                    int pathLen = 0;
                    int curr = i;
                    while (vis[curr] == 0) {
                        vis[curr] = 1;
                        path[pathLen++] = curr;
                        curr = A[curr];
                    }

                    // A cycle is found within the current traversed path
                    if (vis[curr] == 1) {
                        int startIdx = 0;
                        while (path[startIdx] != curr) {
                            startIdx++;
                        }

                        int r = path[startIdx]; // Designate arbitrary root for the cycle
                        int Ar = A[r];          // The edge we "break" is from r to Ar

                        // 1. BFS to compute distance (D) and states (vtx) iteratively
                        int qHead = 0, qTail = 0;
                        q[qTail++] = r;
                        D[r] = V[r];
                        vtx[r] = 0; // Tree parent of root is defined as 0

                        while (qHead < qTail) {
                            int u = q[qHead++];
                            int e = head[u];
                            while (e != 0) {
                                int v = to[e];
                                e = next[e];
                                // Avoid the broken cycle edge
                                if (u == Ar && v == r) continue;
                                D[v] = V[v] ^ D[u];
                                vtx[v] = D[u];
                                q[qTail++] = v;
                            }
                        }

                        int Sc = D[Ar]; // Total cycle XOR sum

                        // 2. Insert Cycle nodes into the Trie permanently for this component
                        for (int j = startIdx; j < pathLen; j++) {
                            int c = path[j];
                            insertTrie(vtx[c]);
                            insertTrie(vtx[c] ^ Sc);
                        }

                        // 3. Iterative DFS traversal to populate answers without stack overflows
                        int top = 0;
                        stack[top] = r;
                        edgeIdx[top] = head[r];
                        
                        insertTrie(vtx[r]);
                        ans[r] = queryMax(D[r]);

                        while (top >= 0) {
                            int u = stack[top];
                            int e = edgeIdx[top];

                            int nextChild = -1;
                            while (e != 0) {
                                int v = to[e];
                                e = next[e];
                                if (u == Ar && v == r) continue; // Skip broken cycle edge
                                nextChild = v;
                                break;
                            }

                            edgeIdx[top] = e; // Save edge pointer for backtracking

                            if (nextChild != -1) {
                                // Pre-order: Visit child
                                top++;
                                stack[top] = nextChild;
                                edgeIdx[top] = head[nextChild];
                                insertTrie(vtx[nextChild]);
                                ans[nextChild] = queryMax(D[nextChild]);
                            } else {
                                // Post-order: Leave node (backtrack in Trie)
                                removeTrie(vtx[u]);
                                top--;
                            }
                        }

                        // 4. Remove Cycle nodes from Trie to leave it clean for the next component
                        for (int j = startIdx; j < pathLen; j++) {
                            int c = path[j];
                            removeTrie(vtx[c]);
                            removeTrie(vtx[c] ^ Sc);
                        }
                    }
                    
                    // Mark all nodes visited in this phase as fully processed
                    for (int j = 0; j < pathLen; j++) {
                        vis[path[j]] = 2;
                    }
                }
            }

            // Print Output
            for (int i = 1; i <= N; i++) {
                out.print(ans[i]);
                if (i < N) out.print(" ");
            }
            out.println();
        }
        out.flush();
    }

    // O(1) conditional allocation inserts
    static void insertTrie(int x) {
        int u = 0;
        cnt[u]++;
        for (int i = 29; i >= 0; i--) {
            int b = (x >> i) & 1;
            if (nxt[u][b] == 0) {
                nxt[u][b] = nodesCnt;
                nxt[nodesCnt][0] = nxt[nodesCnt][1] = 0;
                cnt[nodesCnt] = 0;
                nodesCnt++;
            }
            u = nxt[u][b];
            cnt[u]++;
        }
    }

    static void removeTrie(int x) {
        int u = 0;
        cnt[u]--;
        for (int i = 29; i >= 0; i--) {
            int b = (x >> i) & 1;
            u = nxt[u][b];
            cnt[u]--;
        }
    }

    static int queryMax(int x) {
        int u = 0;
        int res = 0;
        for (int i = 29; i >= 0; i--) {
            int b = (x >> i) & 1;
            int opposite = 1 ^ b;
            
            // Prefer the opposite bit to maximize XOR
            if (nxt[u][opposite] != 0 && cnt[nxt[u][opposite]] > 0) {
                res |= (1 << i);
                u = nxt[u][opposite];
            } else if (nxt[u][b] != 0 && cnt[nxt[u][b]] > 0) {
                u = nxt[u][b];
            } else {
                break;
            }
        }
        return res;
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