import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashSet;
import java.util.StringTokenizer;

public class Solution {
    // mask 一定是低b位全0，高位连续1，block = 1 << b
    private static HashSet<Long> getOptions(long L, long R, long mask) {
        HashSet<Long> res = new HashSet<>();
        long block = mask & -mask; // 取出mask最低的那一个1，也就是 1<<b
        long k0 = L / block;
        long k1 = R / block;
        if (k0 == k1) {
            // 只在一个块里面，只有一种选择
            res.add(k0 * block);
        } else {
            // 跨块，可以选k0 或者 k0+1
            res.add(k0 * block);
            res.add((k0 + 1) * block);
        }
        return res;
    }

    private static boolean check(long[] L, long[] R, long mask) {
        HashSet<Long> dp = new HashSet<>();
        dp.add(0L);
        int n = L.length;
        for (int i = 0; i < n; i++) {
            HashSet<Long> opts = getOptions(L[i], R[i], mask);
            HashSet<Long> newDp = new HashSet<>();
            for (long prev : dp) {
                for (long o : opts) {
                    newDp.add(prev ^ o);
                }
            }
            dp = newDp;
            if (dp.isEmpty()) return false;
        }
        return dp.contains(mask);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder sb = new StringBuilder();
        int T = Integer.parseInt(br.readLine());
        while (T-- > 0) {
            int N = Integer.parseInt(br.readLine());
            long[] L = new long[N];
            long[] R = new long[N];
            StringTokenizer st = new StringTokenizer(br.readLine());
            for (int i = 0; i < N; i++) L[i] = Long.parseLong(st.nextToken());
            st = new StringTokenizer(br.readLine());
            for (int i = 0; i < N; i++) R[i] = Long.parseLong(st.nextToken());

            long ans = 0;
            for (int bit = 29; bit >= 0; bit--) {
                long tryBit = 1L << bit;
                long candidate = ans | tryBit;
                if (check(L, R, candidate)) {
                    ans = candidate;
                }
            }
            sb.append(ans).append('\n');
        }
        System.out.print(sb);
    }
}
