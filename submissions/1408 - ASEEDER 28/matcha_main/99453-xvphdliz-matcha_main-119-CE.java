import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashSet;
import java.util.StringTokenizer;

public class Main {

    // 给定 [L, R], mask，返回所有可能的 (x & mask)，最多两个
    static HashSet<Long> getOptions(long L, long R, long mask) {
        HashSet<Long> res = new HashSet<>();
        long a = L & mask;
        long b = R & mask;
        res.add(a);
        res.add(b);
        // 核心性质：区间里x & mask 只能是 a 或者 b（mask是高位连续1）
        return res;
    }

    // 检查：是否可以选每个区间一个数，使得 (xor) & mask == mask
    static boolean ok(long[] L, long[] R, long mask) {
        HashSet<Long> dp = new HashSet<>();
        dp.add(0L);
        int n = L.length;
        for (int i = 0; i < n; i++) {
            HashSet<Long> opt = getOptions(L[i], R[i], mask);
            HashSet<Long> ndp = new HashSet<>();
            for (long d : dp) {
                for (long o : opt) {
                    ndp.add(d ^ o);
                }
            }
            dp = ndp;
            if (dp.isEmpty()) break;
        }
        long want = mask;
        return dp.contains(want);
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
            for (int b = 29; b >= 0; b--) {
                long tryBit = 1L << b;
                long candidate = ans | tryBit;
                if (ok(L, R, candidate)) {
                    ans = candidate;
                }
            }
            sb.append(ans).append('\n');
        }
        System.out.print(sb);
    }
}
