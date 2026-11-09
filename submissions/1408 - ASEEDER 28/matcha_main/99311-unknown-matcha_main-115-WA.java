import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder sb = new StringBuilder(); // 批量输出，提升速度
        int T = Integer.parseInt(br.readLine());

        while (T-- > 0) {
            int N = Integer.parseInt(br.readLine());

            long[] L = new long[N];
            long[] R = new long[N];

            StringTokenizer st = new StringTokenizer(br.readLine());
            for (int i = 0; i < N; i++) {
                L[i] = Long.parseLong(st.nextToken());
            }
            st = new StringTokenizer(br.readLine());
            for (int i = 0; i < N; i++) {
                R[i] = Long.parseLong(st.nextToken());
            }

            long ans = 0;
            // 从bit29往下到bit0
            for (int b = 29; b >= 0; b--) {
                long s = 1L << b;
                boolean hasFlex = false;
                long xorG = 0;

                for (int i = 0; i < N; i++) {
                    long lo = L[i] / s;
                    long hi = R[i] / s;
                    if (lo < hi) {
                        hasFlex = true;
                    }
                    xorG ^= lo;
                }

                if (hasFlex) {
                    ans |= s;
                } else {
                    if ((xorG & 1L) == 1) {
                        ans |= s;
                    }
                }
            }
            sb.append(ans).append('\n');
        }
        System.out.print(sb);
    }
}
