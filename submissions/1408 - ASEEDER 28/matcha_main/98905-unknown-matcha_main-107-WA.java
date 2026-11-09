import java.io.*;

class Solution {

    static boolean hasBit(int lo, int hi, int pos, int v) {
        if (v == 0) {
            int upper = (hi >>> (pos + 1)) << (pos + 1) | ((1 << pos) - 1);
            return lo <= upper;
        }
        int lower = (lo >>> (pos + 1)) << (pos + 1) | (1 << pos);
        return lower <= hi;
    }

    static void narrow(int[] lo, int[] hi, int i, int pos, int v) {
        if (v == 0) {
            int cap = (hi[i] >>> (pos + 1)) << (pos + 1) | ((1 << pos) - 1);
            hi[i] = Math.min(hi[i], cap);
        } else {
            int floor = (lo[i] >>> (pos + 1)) << (pos + 1) | (1 << pos);
            lo[i] = Math.max(lo[i], floor);
        }
    }

    static boolean canAchieve(int[] L, int[] R, int target, int minBit) {
        int n = L.length;
        int[] lo = L.clone();
        int[] hi = R.clone();
        for (int pos = 30; pos >= minBit; pos--) {
            int need = (target >> pos) & 1;
            int fixed = 0;
            int flex = 0;
            boolean[] can0 = new boolean[n];
            boolean[] can1 = new boolean[n];
            byte[] assign = new byte[n]; // -1 unset, 0/1 fixed

            for (int i = 0; i < n; i++) {
                can0[i] = hasBit(lo[i], hi[i], pos, 0);
                can1[i] = hasBit(lo[i], hi[i], pos, 1);
                if (!can0[i] && !can1[i]) return false;
                assign[i] = -1;
                if (can0[i] && can1[i]) {
                    flex++;
                } else if (can1[i]) {
                    assign[i] = 1;
                    fixed ^= 1;
                } else {
                    assign[i] = 0;
                }
            }
            if ((fixed & 1) != need && flex == 0) return false;
            if ((fixed & 1) != need) {
                for (int i = 0; i < n; i++) {
                    if (can0[i] && can1[i]) {
                        assign[i] = 1;
                        break;
                    }
                }
            }
            for (int i = 0; i < n; i++) {
                if (assign[i] == -1) assign[i] = 0;
                narrow(lo, hi, i, pos, assign[i]);
                if (lo[i] > hi[i]) return false;
            }
        }
        return true;
    }

    static int solve(int N, int[] L, int[] R) {
        int ans = 0;
        for (int b = 30; b >= 0; b--) {
            if (canAchieve(L, R, ans | (1 << b), b)) {
                ans |= 1 << b;
            }
        }
        return ans;
    }

    static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    static PrintWriter out = new PrintWriter(System.out);

    public static void main(String[] args) throws IOException {
        int T = Integer.parseInt(in.readLine());
        for (int tc = 0; tc < T; tc++) {
            int N = Integer.parseInt(in.readLine());
            int[] L = new int[N];
            int[] R = new int[N];
            String[] parts = in.readLine().split(" ");
            for (int i = 0; i < N; i++) L[i] = Integer.parseInt(parts[i]);
            parts = in.readLine().split(" ");
            for (int i = 0; i < N; i++) R[i] = Integer.parseInt(parts[i]);
            out.println(solve(N, L, R));
        }
        out.flush();
    }
}
