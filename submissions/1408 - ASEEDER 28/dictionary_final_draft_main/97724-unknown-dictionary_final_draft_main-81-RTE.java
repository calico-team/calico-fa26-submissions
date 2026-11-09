import java.io.*;
import java.util.*;

class Solution {

    static final int BITS = 30;
    static final int POOL = 12000000;

    static int[] tr0, tr1, sz;
    static int pool;
    static int lazy;
    static int[] V;
    static int[] ans;
    static boolean[] inCycle;
    static ArrayList<Integer>[] rev;

    static void ensurePool() {
        if (tr0 == null) {
            tr0 = new int[POOL];
            tr1 = new int[POOL];
            sz = new int[POOL];
        }
    }

    static int newNode() {
        int x = ++pool;
        tr0[x] = tr1[x] = 0;
        sz[x] = 0;
        return x;
    }

    static void trieAdd(int root, int val, int delta) {
        int node = root;
        sz[node] += delta;
        for (int b = BITS - 1; b >= 0; b--) {
            int bit = (val >> b) & 1;
            if (bit == 0) {
                if (tr0[node] == 0) tr0[node] = newNode();
                node = tr0[node];
            } else {
                if (tr1[node] == 0) tr1[node] = newNode();
                node = tr1[node];
            }
            sz[node] += delta;
        }
    }

    static int trieMaxXor(int root, int x) {
        if (sz[root] <= 0) return 0;
        int want = x ^ lazy;
        int node = root;
        int res = 0;
        for (int b = BITS - 1; b >= 0; b--) {
            int prefer = 1 - ((want >> b) & 1);
            int ch = prefer == 0 ? tr0[node] : tr1[node];
            if (ch != 0 && sz[ch] > 0) {
                res |= 1 << b;
                node = ch;
            } else {
                node = prefer == 0 ? tr1[node] : tr0[node];
                if (node == 0) break;
            }
        }
        return res;
    }

    static void dfsTrees(int root, int start) {
        ArrayDeque<int[]> st = new ArrayDeque<>();
        st.push(new int[] { start, 0 });
        while (!st.isEmpty()) {
            int[] fr = st.pop();
            int u = fr[0], phase = fr[1];
            if (phase == 0) {
                ans[u] = Math.max(V[u], trieMaxXor(root, V[u]));
                lazy ^= V[u];
                trieAdd(root, V[u] ^ lazy, 1);
                st.push(new int[] { u, 1 });
                for (int w : rev[u]) {
                    if (!inCycle[w]) st.push(new int[] { w, 0 });
                }
            } else {
                trieAdd(root, V[u] ^ lazy, -1);
                lazy ^= V[u];
            }
        }
    }

    static void processCycle(ArrayList<Integer> cyc) {
        int L = cyc.size();
        int Cxor = 0;
        for (int u : cyc) {
            Cxor ^= V[u];
            inCycle[u] = true;
        }
        int lim = (Cxor == 0) ? L : 2 * L;
        int copies = (Cxor == 0) ? 2 : 3;
        int M = copies * L;
        int[] pref = new int[M + 1];
        for (int k = 0; k < M; k++) {
            pref[k + 1] = pref[k] ^ V[cyc.get(k % L)];
        }

        pool = 0;
        int root = newNode();
        lazy = 0;
        for (int j = L; j <= L - 1 + lim; j++) {
            trieAdd(root, pref[j], 1);
        }

        for (int i = L - 1; i >= 0; i--) {
            ans[cyc.get(i)] = trieMaxXor(root, pref[i]);

            lazy = pref[i];
            for (int w : rev[cyc.get(i)]) {
                if (!inCycle[w]) dfsTrees(root, w);
            }
            lazy = 0;

            if (i > 0) {
                trieAdd(root, pref[i], 1);
                trieAdd(root, pref[i + lim], -1);
            }
        }
    }

    /*
     * Return an array of N integers, the i-th of which
     * represents Big Ben's maximum happiness if he
     * starts by trying to define word i.
     *
     * N: the number of words in the dictionary
     * A: the first word in the definition of word i
     * V: the value associated with the happiness of each word
     */
    static int[] solve(int N, int[] A, int[] Varr) {
        int dinosauraus = N;
        ensurePool();
        V = Varr;
        ans = new int[N];
        inCycle = new boolean[N];
        @SuppressWarnings("unchecked")
        ArrayList<Integer>[] revLocal = new ArrayList[N];
        rev = revLocal;
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
                processCycle(new ArrayList<>(path.subList(idx, path.size())));
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
        for (int tc = 0; tc < T; tc++) {
            int N = Integer.parseInt(in.readLine().trim());
            int[] A = new int[N];
            String[] tempA = in.readLine().trim().split(" ");
            for (int j = 0; j < N; j++) A[j] = Integer.parseInt(tempA[j]);
            int[] VV = new int[N];
            String[] tempV = in.readLine().trim().split(" ");
            for (int j = 0; j < N; j++) VV[j] = Integer.parseInt(tempV[j]);
            int[] res = solve(N, A, VV);
            StringBuilder sb = new StringBuilder();
            for (int j = 0; j < res.length; j++) {
                if (j > 0) sb.append(' ');
                sb.append(res[j]);
            }
            out.println(sb);
        }
        out.flush();
    }

    static void read_your_input() throws IOException {
        in.readLine();
    }
}
