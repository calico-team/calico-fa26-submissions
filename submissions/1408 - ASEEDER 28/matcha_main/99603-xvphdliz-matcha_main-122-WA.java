import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Solution {
    // dp最多两个状态，用数组存；0表示空占位
    private static boolean check(long[] L, long[] R, long mask) {
        long a = 0, b = -1; // b=-1代表不存在第二个状态

        int n = L.length;
        for (int i = 0; i < n; i++) {
            long o1 = L[i] & mask;
            long o2 = R[i] & mask;

            long na = -1, nb = -1;
            // 展开旧状态a
            if (a != -1) {
                long v1 = a ^ o1;
                long v2 = a ^ o2;
                na = v1;
                if (v2 != na) nb = v2;
            }
            // 展开旧状态b
            if (b != -1) {
                long v1 = b ^ o1;
                if (na == -1) na = v1;
                else if(v1 != na && nb == -1) nb = v1;
                long v2 = b ^ o2;
                if(v2 != na && v2 != nb) {
                    if(na == -1) na = v2;
                    else if(nb == -1) nb = v2;
                }
            }
            a = na;
            b = nb;
            if(a == -1) return false;
        }
        return (a == mask) || (b == mask);
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
                if(check(L,R,candidate)){
                    ans = candidate;
                }
            }
            sb.append(ans).append('\n');
        }
        System.out.print(sb);
    }
}
