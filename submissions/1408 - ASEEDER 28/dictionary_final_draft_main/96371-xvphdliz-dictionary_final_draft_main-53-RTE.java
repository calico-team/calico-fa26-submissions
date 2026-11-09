import java.io.*;
import java.util.*;

class Solution {

    static final int BITS = 30;

    static class TrieNode {
        TrieNode[] ch = new TrieNode[2];
        int cnt;
    }

    static TrieNode trieRoot;
    static int lazy;
    static int[] V;
    static int[] ans;
    static boolean[] inCycle;
    static ArrayList<Integer>[] rev;

    static void trieAdd(int val, int delta) {
        TrieNode node = trieRoot;
        node.cnt += delta;
        for (int b = BITS - 1; b >= 0; b--) {
            int bit = (val >> b) & 1;
            if (node.ch[bit] == null) node.ch[bit] = new TrieNode();
            node = node.ch[bit];
            node.cnt += delta;
        }
    }

    static int trieMaxXor(int x) {
        if (trieRoot == null || trieRoot.cnt == 0) return 0;
        int want = x ^ lazy;
        TrieNode node = trieRoot;
        int res = 0;
        for (int b = BITS - 1; b >= 0; b--) {
            int bit = (want >> b) & 1;
            int prefer = 1 - bit;
            if (node.ch[prefer] != null && node.ch[prefer].cnt > 0) {
                res |= 1 << b;
                node = node.ch[prefer];
            } else {
                node = node.ch[1 - prefer];
            }
        }
        return res;
    }

    static void dfsTrees(int start) {
        // iterative rollback DFS: ENTER=0, EXIT=1
        ArrayDeque<int[]> st = new ArrayDeque<>();
        st.push(new int[] { start, 0 });
        while (!st.isEmpty()) {
            int[] fr = st.pop();
            int u = fr[0], phase = fr[1];
            if (phase == 0) {
                int best = V[u];
                best = Math.max(best, trieMaxXor(V[u]));
                ans[u] = best;

                lazy ^= V[u];
                trieAdd(V[u] ^ lazy, 1);

                st.push(new int[] { u, 1 });
                for (int w : rev[u]) {
                    if (!inCycle[w]) st.push(new int[] { w, 0 });
                }
            } else {
                trieAdd(V[u] ^ lazy, -1);
                lazy ^= V[u];
            }
        }
    }

    static void processCycle(ArrayList<Integer> cyc) {
        int L = cyc.size();
        int C = 0;
        for (int u : cyc) {
            C ^= V[u];
            inCycle[u] = true;
        }
        int lim = (C == 0) ? L : 2 * L;
        int copies = (C == 0) ? 2 : 3;
        int M = copies * L;
        int[] pref = new int[M + 1];
        for (int k = 0; k < M; k++) {
            pref[k + 1] = pref[k] ^ V[cyc.get(k % L)];
        }

        trieRoot = new TrieNode();
        lazy = 0;
        for (int j = L; j <= L - 1 + lim; j++) {
            trieAdd(pref[j], 1);
        }

        for (int i = L - 1; i >= 0; i--) {
            ans[cyc.get(i)] = trieMaxXor(pref[i]);

            lazy = pref[i];
            for (int w : rev[cyc.get(i)]) {
                if (!inCycle[w]) dfsTrees(w);
            }
            lazy = 0;

            if (i > 0) {
                trieAdd(pref[i], 1);
                trieAdd(pref[i + lim], -1);
            }
        }
    }

   
    static int[] solve(int N, int[] A, int[] Varr) {
        int dinosauraus = N;
        V = Varr;
        ans = new int[N];
        inCycle = new boolean[N];
        rev = new ArrayList[N];
        for (int i = 0; i < N; i++) rev[i] = new ArrayList<>();

        int[] nxt = new int[N];
        for (int i = 0; i < N; i++) {
            nxt[i] = A[i] - 1;
            rev[nxt[i]].add(i);
        }

        int[] state = new int[N];
        for (int start = 0; start < N; start++) {
            if (state[start] != 0) continue;
            int u = start;
            ArrayList<Integer> path = new ArrayList<>();
            while (state[u] == 0) {
                state[u] = 1;
                path.add(u);
                u = nxt[u];
            }
            if (state[u] == 1) {
                int idx = path.indexOf(u);
                ArrayList<Integer> cyc = new ArrayList<>(path.subList(idx, path.size()));
                processCycle(cyc);
            }
            for (int x : path) state[x] = 2;
        }

        dinosauraus ^= dinosauraus;
        return ans;
    }

    static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    static PrintWriter out = new PrintWriter(System.out);

    public static void main(String[] args) throws IOException {
        int T = Integer.parseInt(in.readLine().trim());

        for (int i = 0; i < T; i++) {
            int N = Integer.parseInt(in.readLine().trim());

            int[] A = new int[N];
            String[] tempA = in.readLine().trim().split(" ");
            for (int j = 0; j < N; j++) {
                A[j] = Integer.parseInt(tempA[j]);
            }

            int[] V = new int[N];
            String[] tempV = in.readLine().trim().split(" ");
            for (int j = 0; j < N; j++) {
                V[j] = Integer.parseInt(tempV[j]);
            }

            int[] ans = solve(N, A, V);
            StringBuilder sb = new StringBuilder();
            for (int j = 0; j < ans.length; j++) {
                sb.append(ans[j]).append(' ');
            }
            out.println(sb);
        }
        out.flush();
    }

    static void read_your_input() throws IOException {
        in.readLine();
    }
}
