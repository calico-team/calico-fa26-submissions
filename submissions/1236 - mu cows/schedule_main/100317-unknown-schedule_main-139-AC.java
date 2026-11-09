import java.util.*;
import java.io.*;

public class Schedule {
    static int m, k;
    static int[] parent, depth;
    static List<Integer> order;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

        int t = Integer.parseInt(br.readLine().trim());
        while (t-- > 0) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int n = Integer.parseInt(st.nextToken());
            m = Integer.parseInt(st.nextToken());
            k = Integer.parseInt(st.nextToken());

            parent = new int[n + 1];
            List<Integer>[] children = new ArrayList[n + 1];
            for (int i = 0; i <= n; i++)
                children[i] = new ArrayList<>();

            st = new StringTokenizer(br.readLine());
            for (int i = 1; i <= n; i++) {
                parent[i] = Integer.parseInt(st.nextToken());
                children[parent[i]].add(i);
            }

            depth = new int[n + 1];
            order = new ArrayList<>();
            Queue<Integer> queue = new ArrayDeque<>();
            queue.add(0);
            while (!queue.isEmpty()) {
                int u = queue.poll();
                if (u != 0)
                    order.add(u);
                for (int c : children[u]) {
                    depth[c] = depth[u] + 1;
                    if (depth[c] <= m)
                        queue.add(c);
                }
            }

            int lo = 0, hi = (int) Math.min(order.size(), m * k);
            while (lo < hi) {
                int mid = (lo + hi + 1) / 2;
                if (canTake(mid))
                    lo = mid;
                else
                    hi = mid - 1;
            }
            out.println(lo);
        }
        out.flush();
    }

    public static boolean canTake(int c) {
        boolean[] chosen = new boolean[parent.length];
        int[] dependents = new int[parent.length];

        for (int i = 0; i < c; i++)
            chosen[order.get(i)] = true;
        for (int i = 0; i < c; i++) {
            int u = order.get(i);
            if (parent[u] != 0)
                dependents[parent[u]]++;
        }

        PriorityQueue<Integer> ready = new PriorityQueue<>((a, b) -> depth[b] - depth[a]);
        for (int i = 0; i < c; i++) {
            int u = order.get(i);
            if (dependents[u] == 0)
                ready.add(u);
        }

        int semesters = 0, scheduled = 0;
        while (scheduled < c) {
            semesters++;
            if (semesters > m)
                return false;

            List<Integer> today = new ArrayList<>();
            while (today.size() < k && !ready.isEmpty())
                today.add(ready.poll());

            for (int u : today) {
                scheduled++;
                int pre = parent[u];
                if (pre != 0 && chosen[pre] && --dependents[pre] == 0)
                    ready.add(pre);
            }
        }

        return true;
    }
}