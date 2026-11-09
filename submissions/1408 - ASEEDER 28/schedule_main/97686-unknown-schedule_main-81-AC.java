import java.io.*;
import java.util.*;

class Solution {

    
    public static int solve(int N, int M, int K, int[] P) {
        ArrayList<Integer>[] children = new ArrayList[N + 1];
        for (int i = 1; i <= N; i++) children[i] = new ArrayList<>();
        int[] parent = new int[N + 1];
        for (int i = 1; i <= N; i++) {
            parent[i] = P[i - 1];
            if (parent[i] != 0) children[parent[i]].add(i);
        }

        // Topological order (parents before children), then heights bottom-up.
        int[] order = new int[N];
        int osz = 0;
        int[] deg = new int[N + 1];
        ArrayDeque<Integer> q = new ArrayDeque<>();
        for (int i = 1; i <= N; i++) {
            if (parent[i] == 0) q.add(i);
            else deg[i] = 1;
        }
        while (!q.isEmpty()) {
            int u = q.poll();
            order[osz++] = u;
            for (int v : children[u]) {
                if (--deg[v] == 0) q.add(v);
            }
        }

        int[] height = new int[N + 1];
        for (int i = osz - 1; i >= 0; i--) {
            int u = order[i];
            int h = 1;
            for (int v : children[u]) h = Math.max(h, 1 + height[v]);
            height[u] = h;
        }

        // Highest remaining chain first (critical-path / Hu-style for out-trees).
        PriorityQueue<int[]> avail = new PriorityQueue<>((a, b) -> {
            if (a[0] != b[0]) return Integer.compare(b[0], a[0]);
            return Integer.compare(a[1], b[1]);
        });
        for (int i = 1; i <= N; i++) {
            if (parent[i] == 0) avail.offer(new int[]{height[i], i});
        }

        int taken = 0;
        for (int sem = 0; sem < M && !avail.isEmpty(); sem++) {
            int take = Math.min(K, avail.size());
            int[] batch = new int[take];
            for (int t = 0; t < take; t++) {
                batch[t] = avail.poll()[1];
                taken++;
            }
            for (int u : batch) {
                for (int v : children[u]) {
                    avail.offer(new int[]{height[v], v});
                }
            }
        }
        return taken;
    }

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int T = Integer.parseInt(st.nextToken());
        StringBuilder sb = new StringBuilder();
        while (T-- > 0) {
            st = new StringTokenizer(br.readLine());
            int N = Integer.parseInt(st.nextToken());
            int M = Integer.parseInt(st.nextToken());
            int K = Integer.parseInt(st.nextToken());
            st = new StringTokenizer(br.readLine());
            int[] P = new int[N];
            for (int i = 0; i < N; i++) P[i] = Integer.parseInt(st.nextToken());
            sb.append(solve(N, M, K, P)).append('\n');
        }
        System.out.print(sb);
    }
}
