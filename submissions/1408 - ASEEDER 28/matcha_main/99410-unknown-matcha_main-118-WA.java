import java.io.*;
import java.util.*;

class Solution {

    static final int MAX_BIT = 29;
    static final int FLEX_COMB_LIMIT = 22;

    static int targetGlobal;
    static int minBitGlobal;
    static int bufN;
    static int[] wrLo, wrHi;

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

    static boolean applyAtBit(int pos, int[] lo, int[] hi, int[] forcedIdx, int[] forcedVal, int forcedCnt,
                              int[] flex, int flexCnt, boolean[] flexOne) {
        System.arraycopy(lo, 0, wrLo, 0, bufN);
        System.arraycopy(hi, 0, wrHi, 0, bufN);
        for (int k = 0; k < forcedCnt; k++) {
            narrow(wrLo, wrHi, forcedIdx[k], pos, forcedVal[k]);
            if (wrLo[forcedIdx[k]] > wrHi[forcedIdx[k]]) return false;
        }
        for (int j = 0; j < flexCnt; j++) {
            int i = flex[j];
            narrow(wrLo, wrHi, i, pos, flexOne[i] ? 1 : 0);
            if (wrLo[i] > wrHi[i]) return false;
        }
        return canAchieveBit(pos - 1, wrLo, wrHi);
    }

    static boolean pickSubsets(int pos, int[] lo, int[] hi, int[] forcedIdx, int[] forcedVal, int forcedCnt,
                               int[] flex, int flexCnt, int want, int ones, int[] chosen, int at, int left) {
        if (left == 0) {
            boolean[] flexOne = new boolean[bufN];
            for (int j = 0; j < ones; j++) flexOne[flex[chosen[j]]] = true;
            return applyAtBit(pos, lo, hi, forcedIdx, forcedVal, forcedCnt, flex, flexCnt, flexOne);
        }
        for (int i = at; i <= flexCnt - left; i++) {
            chosen[ones - left] = i;
            if (pickSubsets(pos, lo, hi, forcedIdx, forcedVal, forcedCnt, flex, flexCnt, want, ones, chosen, i + 1, left - 1)) {
                return true;
            }
        }
        return false;
    }

    static boolean dfsFlexBit(int pos, int[] lo, int[] hi, int[] forcedIdx, int[] forcedVal, int forcedCnt,
                              int[] flex, int flexCnt, int fpos, int parity, int want, boolean[] flexOne) {
        if (fpos == flexCnt) {
            if (((parity & 1) != want)) return false;
            return applyAtBit(pos, lo, hi, forcedIdx, forcedVal, forcedCnt, flex, flexCnt, flexOne);
        }
        int i = flex[fpos];
        if (hasBit(lo[i], hi[i], pos, 0)) {
            flexOne[i] = false;
            if (dfsFlexBit(pos, lo, hi, forcedIdx, forcedVal, forcedCnt, flex, flexCnt, fpos + 1, parity, want, flexOne)) {
                return true;
            }
        }
        if (hasBit(lo[i], hi[i], pos, 1)) {
            flexOne[i] = true;
            if (dfsFlexBit(pos, lo, hi, forcedIdx, forcedVal, forcedCnt, flex, flexCnt, fpos + 1, parity ^ 1, want, flexOne)) {
                return true;
            }
        }
        return false;
    }

    static boolean canAchieveBit(int pos, int[] lo, int[] hi) {
        if (pos < minBitGlobal) return true;
        int need = (targetGlobal >> pos) & 1;
        int[] flex = new int[bufN];
        int[] forcedIdx = new int[bufN];
        int[] forcedVal = new int[bufN];
        int flexCnt = 0, forcedCnt = 0;
        int fixedParity = 0;

        for (int i = 0; i < bufN; i++) {
            boolean c0 = hasBit(lo[i], hi[i], pos, 0);
            boolean c1 = hasBit(lo[i], hi[i], pos, 1);
            if (!c0 && !c1) return false;
            if (c0 && c1) {
                flex[flexCnt++] = i;
            } else if (c1) {
                forcedIdx[forcedCnt] = i;
                forcedVal[forcedCnt++] = 1;
                fixedParity ^= 1;
            } else {
                forcedIdx[forcedCnt] = i;
                forcedVal[forcedCnt++] = 0;
            }
        }

        int want = (need - fixedParity) & 1;
        if (flexCnt == 0) {
            if (want != 0) return false;
            return applyAtBit(pos, lo, hi, forcedIdx, forcedVal, forcedCnt, flex, 0, new boolean[bufN]);
        }

        if (flexCnt <= FLEX_COMB_LIMIT) {
            int[] chosen = new int[flexCnt];
            for (int ones = want; ones <= flexCnt; ones += 2) {
                if (pickSubsets(pos, lo, hi, forcedIdx, forcedVal, forcedCnt, flex, flexCnt, want, ones, chosen, 0, ones)) {
                    return true;
                }
            }
            return false;
        }

        boolean[] flexOne = new boolean[bufN];
        return dfsFlexBit(pos, lo, hi, forcedIdx, forcedVal, forcedCnt, flex, flexCnt, 0, 0, want, flexOne);
    }

    static boolean canAchieve(int[] L, int[] R, int target, int minBit) {
        targetGlobal = target;
        minBitGlobal = minBit;
        int[] lo = L.clone();
        int[] hi = R.clone();
        return canAchieveBit(minBit, lo, hi);
    }

    static int solve(int N, int[] L, int[] R) {
        bufN = N;
        wrLo = new int[N];
        wrHi = new int[N];
        int ans = 0;
        for (int b = MAX_BIT; b >= 0; b--) {
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
