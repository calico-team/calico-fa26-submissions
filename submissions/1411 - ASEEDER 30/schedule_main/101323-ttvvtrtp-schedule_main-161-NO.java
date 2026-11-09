import java.util.*;

class Solution {
    /**
     * Return the maximum number of classes that can be taken across M semesters.
     *
     * N: the number of classes
     * M: the number of semesters
     * K: the maximum number of classes you can take per semester
     * P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
     */
    public static int solve(int N, int M, int K, int[] P) {
        List<List<Integer>> children = new ArrayList<List<Integer>>();
        for (int i = 0; i <= N; i++) {
            children.add(new ArrayList<Integer>());
        }
        for (int i = 1; i <= N; i++) {
            int p = P[i - 1];
            if (p != 0) {
                children.get(p).add(i);
            }
        }

        int[] depth = new int[N + 1];
        int maxDepth = 0;
        for (int i = 1; i <= N; i++) {
            if (P[i - 1] == 0) {
                dfs(i, 1, children, depth);
            }
        }
        for (int i = 1; i <= N; i++) {
            if (depth[i] > maxDepth) maxDepth = depth[i];
        }

        int D = Math.min(M, maxDepth);
        if (D <= 0) return 0;

        int[] cnt = new int[D + 2];
        for (int i = 1; i <= N; i++) {
            int d = depth[i];
            if (d <= D) cnt[d]++;
        }

        long[] slack = new long[D + 2];
        for (int t = 1; t <= D; t++) {
            slack[t] = (long) (M - t + 1) * K;
        }

        int answer = 0;
        for (int d = 1; d <= D; d++) {
            if (cnt[d] == 0) continue;
            long limit = Long.MAX_VALUE;
            for (int t = 1; t <= d; t++) {
                limit = Math.min(limit, slack[t]);
            }
            if (limit <= 0) continue;
            int take = (int) Math.min((long) cnt[d], limit);
            if (take == 0) continue;
            answer += take;
            for (int t = 1; t <= d; t++) {
                slack[t] -= take;
            }
        }
        return answer;
    }

    private static void dfs(int u, int d, List<List<Integer>> children, int[] depth) {
        depth[u] = d;
        for (int v : children.get(u)) {
            dfs(v, d + 1, children, depth);
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        while (T-- > 0) {
            int N = sc.nextInt();
            int M = sc.nextInt();
            int K = sc.nextInt();
            int[] P = new int[N];
            for (int i = 0; i < N; i++) {
                P[i] = sc.nextInt();
            }
            solve(N, M, K, P);
        }
        sc.close();
    }
}
