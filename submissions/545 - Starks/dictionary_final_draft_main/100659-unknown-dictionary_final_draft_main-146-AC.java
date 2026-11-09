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
    
    // 1D Arrays for Trie to eliminate multi-dimensional object overhead and avoid OutOfMemory
    static int[] nxt0;
    static int[] nxt1;
    static int[] cnt;
    static int nodesCnt;

    public static void main(String[] args) {
        FastReader in = new FastReader();
        PrintWriter out = new PrintWriter(System.out);

        // Pre-allocate base arrays for max N is 200,000
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
        
        // Trie memory: Max nodes = N (200,000) * 30 bits = 6,000,000
        int MAX_TRIE = 6000005;
        nxt0 = new int[MAX_TRIE];
        nxt1 = new int[MAX_TRIE];
        cnt = new int[MAX_TRIE];

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
            nxt0[0] = nxt1[0] = 0;
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

                    if (vis[curr] == 1) {
                        int startIdx = 0;
                        while (path[startIdx] != curr) {
                            startIdx++;
                        }

                        int r = path[startIdx];
                        int Ar = A[r];          

                        int qHead = 0, qTail = 0;
                        q[qTail++] = r;
                        D[r] = V[r];
                        vtx[r] = 0; 

                        while (qHead < qTail) {
                            int u = q[qHead++];
                            int e = head[u];
                            while (e != 0) {
                                int v = to[e];
                                e = next[e];
                                if (u == Ar && v == r) continue;
                                D[v] = V[v] ^ D[u];
                                vtx[v] = D[u];
                                q[qTail++] = v;
                            }
                        }

                        int Sc = D[Ar]; 

                        for (int j = startIdx; j < pathLen; j++) {
                            int c = path[j];
                            insertTrie(vtx[c]);
                            insertTrie(vtx[c] ^ Sc);
                        }

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
                                if (u == Ar && v == r) continue; 
                                nextChild = v;
                                break;
                            }

                            edgeIdx[top] = e; 

                            if (nextChild != -1) {
                                top++;
                                stack[top] = nextChild;
                                edgeIdx[top] = head[nextChild];
                                insertTrie(vtx[nextChild]);
                                ans[nextChild] = queryMax(D[nextChild]);
                            } else {
                                removeTrie(vtx[u]);
                                top--;
                            }
                        }

                        for (int j = startIdx; j < pathLen; j++) {
                            int c = path[j];
                            removeTrie(vtx[c]);
                            removeTrie(vtx[c] ^ Sc);
                        }
                    }
                    
                    for (int j = 0; j < pathLen; j++) {
                        vis[path[j]] = 2;
                    }
                }
            }

            for (int i = 1; i <= N; i++) {
                out.print(ans[i]);
                if (i < N) out.print(" ");
            }
            out.println();
        }
        out.flush();
    }

    static void insertTrie(int x) {
        int u = 0;
        cnt[u]++;
        for (int i = 29; i >= 0; i--) {
            int b = (x >> i) & 1;
            if (b == 0) {
                if (nxt0[u] == 0) {
                    nxt0[u] = nodesCnt;
                    nxt0[nodesCnt] = 0;
                    nxt1[nodesCnt] = 0;
                    cnt[nodesCnt] = 0;
                    nodesCnt++;
                }
                u = nxt0[u];
            } else {
                if (nxt1[u] == 0) {
                    nxt1[u] = nodesCnt;
                    nxt0[nodesCnt] = 0;
                    nxt1[nodesCnt] = 0;
                    cnt[nodesCnt] = 0;
                    nodesCnt++;
                }
                u = nxt1[u];
            }
            cnt[u]++;
        }
    }

    static void removeTrie(int x) {
        int u = 0;
        cnt[u]--;
        for (int i = 29; i >= 0; i--) {
            int b = (x >> i) & 1;
            if (b == 0) {
                u = nxt0[u];
            } else {
                u = nxt1[u];
            }
            cnt[u]--;
        }
    }

    static int queryMax(int x) {
        int u = 0;
        int res = 0;
        for (int i = 29; i >= 0; i--) {
            int b = (x >> i) & 1;
            int opposite = 1 ^ b;
            
            int nxtOpposite = (opposite == 0) ? nxt0[u] : nxt1[u];
            int nxtSame = (b == 0) ? nxt0[u] : nxt1[u];

            if (nxtOpposite != 0 && cnt[nxtOpposite] > 0) {
                res |= (1 << i);
                u = nxtOpposite;
            } else if (nxtSame != 0 && cnt[nxtSame] > 0) {
                u = nxtSame;
            } else {
                break;
            }
        }
        return res;
    }
    
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