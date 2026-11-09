import java.io.*;
import java.util.*;

class Solution {

    static final int BITS = 30;
    static final int MAXPOOL = 11000000;

    static int[] tr0, tr1, sz;
    static int pool, cap;
    static int lazy;
    static int[] Vglob;
    static int[] ans;
    static boolean[] inCycle;
    static ArrayList<Integer>[] rev;

    static void ensurePool(int n) {
       
        int need = (n <= 5000)
                ? (int) Math.max(5000L, 55L * n + 100)
                : MAXPOOL;
        if (tr0 != null && cap >= need) return;
        tr0 = null;
        tr1 = null;
        sz = null;
        cap = need;
        tr0 = new int[cap];
        tr1 = new int[cap];
        sz = new int[cap];
    }

    static int newNode() {
        int x = ++pool;
        tr0[x] = 0;
        tr1[x] = 0;
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
        int node = root, res = 0;
        for (int b = BITS - 1; b >= 0; b--) {
            int prefer = 1 - ((want >> b) & 1);
            int ch = (prefer == 0) ? tr0[node] : tr1[node];
            if (ch != 0 && sz[ch] > 0) {
                res |= 1 << b;
                node = ch;
            } else {
                node = (prefer == 0) ? tr1[node] : tr0[node];
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
                ans[u] = Math.max(Vglob[u], trieMaxXor(root, Vglob[u]));
                lazy ^= Vglob[u];
                trieAdd(root, Vglob[u] ^ lazy, 1);
                st.push(new int[] { u, 1 });
                for (int w : rev[u]) if (!inCycle[w]) st.push(new int[] { w, 0 });
            } else {
                trieAdd(root, Vglob[u] ^ lazy, -1);
                lazy ^= Vglob[u];
            }
        }
    }

    static void processCycle(ArrayList<Integer> cyc) {
        int L = cyc.size();
        int Cxor = 0;
        for (int u : cyc) {
            Cxor ^= Vglob[u];
            inCycle[u] = true;
        }
        boolean hasTree = false;
        for (int u : cyc) {
            for (int w : rev[u]) if (!inCycle[w]) { hasTree = true; break; }
            if (hasTree) break;
        }

        // One lap in window; if trees need 2nd lap (Cxor != 0), keep 2L window once (O(N), not O(N^2)).
        int lim = (Cxor != 0 && hasTree) ? 2 * L : L;
        int copies = (lim == 2 * L) ? 3 : 2;
        int[] pref = new int[copies * L + 1];
        for (int k = 0; k < copies * L; k++) {
            pref[k + 1] = pref[k] ^ Vglob[cyc.get(k % L)];
        }

        pool = 0;
        int root = newNode();
        lazy = 0;
        for (int j = L; j <= L - 1 + lim; j++) trieAdd(root, pref[j], 1);

        for (int i = L - 1; i >= 0; i--) {
            if (lim == L && Cxor != 0) {
                ans[cyc.get(i)] = Math.max(trieMaxXor(root, pref[i]), trieMaxXor(root, pref[i] ^ Cxor));
            } else {
                ans[cyc.get(i)] = trieMaxXor(root, pref[i]);
            }

            lazy = pref[i];
            for (int w : rev[cyc.get(i)]) if (!inCycle[w]) dfsTrees(root, w);
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
    static int[] solve(int N, int[] A, int[] V) {
        int dinosauraus = N;
        ensurePool(N);
        Vglob = V;
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
        for (int s = 0; s < N; s++) {
            if (state[s] != 0) continue;
            int u = s;
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
            StringTokenizer sta = new StringTokenizer(in.readLine());
            for (int j = 0; j < N; j++) A[j] = Integer.parseInt(sta.nextToken());
            int[] V = new int[N];
            StringTokenizer stv = new StringTokenizer(in.readLine());
            for (int j = 0; j < N; j++) V[j] = Integer.parseInt(stv.nextToken());
            int[] res = solve(N, A, V);
            StringBuilder sb = new StringBuilder();
            for (int j = 0; j < res.length; j++) sb.append(res[j]).append(' ');
            out.println(sb);
        }
        out.flush();
    }

    static void read_your_input() throws IOException {
        in.readLine();
    }
}
