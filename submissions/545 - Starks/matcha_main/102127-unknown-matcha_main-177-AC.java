import java.io.*;
import java.util.*;

public class Solution8 {
    static DataInputStream in = new DataInputStream(new BufferedInputStream(System.in, 1 << 16));

    static int ni() throws IOException {
        int r = 0, b = in.read();
        while (b < '0') b = in.read();
        while (b >= '0') { r = r * 10 + b - '0'; b = in.read(); }
        return r;
    }

    static boolean insert(int[] basis, int v) {
        for (int b = 31; b >= 0 && v != 0; b--) {
            if (((v >>> b) & 1) == 0) continue;
            if (basis[b] == 0) { basis[b] = v; return true; }
            v ^= basis[b];
        }
        return false;
    }

    static int reduce(int[] basis, int v) {
        for (int b = 31; b >= 0; b--)
            if (((v >>> b) & 1) != 0 && basis[b] != 0) v ^= basis[b];
        return v;
    }

    static int ans(int b, int M0) {
        int hi = (b + 1 >= 31) ? 0 : ((M0 >>> (b + 1)) << (b + 1));
        return hi | ((1 << (b + 1)) - 1);
    }

    static int solve(int n, int[] Ls, int[] Rs) {
        int XL = 0;
        int[] D = new int[n], p = new int[n];
        int[] base = new int[32];
        for (int i = 0; i < n; i++) {
            XL ^= Ls[i];
            D[i] = Ls[i] ^ Rs[i];
            if (D[i] != 0) { p[i] = 31 - Integer.numberOfLeadingZeros(D[i]); insert(base, D[i]); }
            else p[i] = -1;
        }
        // M0 = best result with no deviations
        int x = XL;
        for (int b = 31; b >= 0; b--)
            if (((x >>> b) & 1) == 0 && base[b] != 0) x ^= base[b];
        int M0 = x;

        int[] T = new int[31];
        int[] Bn = new int[32], En = new int[32], qb = new int[32], qm = new int[32];
        int[] nonT = new int[n];
        for (int b = 29; b >= 0; b--) {
            int Y = (M0 ^ XL) >>> (b + 1);
            int c0 = (XL >>> b) & 1;
            int tc = 0, nc = 0;
            boolean fresh = false, big = false;
            for (int i = 0; i < n; i++) {
                if (p[i] > b) {
                    int Lb = (Ls[i] >>> b) & 1, Rb = (Rs[i] >>> b) & 1;
                    if (Lb == 1 && Rb == 0) nonT[nc++] = i;   // cannot deviate at b
                    else {
                        if (tc >= 30) { big = true; break; }
                        T[tc++] = i;                          // can deviate at b
                    }
                } else if (p[i] == b) fresh = true;
            }
            if (big) return ans(b, M0);
            if (tc == 0) continue;

            Arrays.fill(Bn, 0);
            for (int k = 0; k < nc; k++) insert(Bn, D[nonT[k]] >>> (b + 1));

            Arrays.fill(qb, 0); Arrays.fill(qm, 0);
            int kernCnt = 0, kern = 0;
            for (int idx = 0; idx < tc; idx++) {
                int v = reduce(Bn, D[T[idx]] >>> (b + 1));
                int m = 1 << idx;
                boolean placed = false;
                for (int bb = 31; bb >= 0; bb--) {
                    if (((v >>> bb) & 1) == 0) continue;
                    if (qb[bb] == 0) { qb[bb] = v; qm[bb] = m; placed = true; break; }
                    v ^= qb[bb]; m ^= qm[bb];
                }
                if (!placed) { kernCnt++; kern = m; }
            }
            if (kernCnt >= 2) return ans(b, M0);

            int tau = reduce(Bn, Y), s0 = 0;
            for (int bb = 31; bb >= 0; bb--) {
                if (((tau >>> bb) & 1) != 0) { tau ^= qb[bb]; s0 ^= qm[bb]; }
            }
            int nsol = kernCnt == 1 ? 2 : 1;
            boolean enBuilt = false;
            for (int si = 0; si < nsol; si++) {
                int S = si == 0 ? s0 : (s0 ^ kern);
                int cnt = 0, tt = Y, dd = c0;
                for (int idx = 0; idx < tc; idx++) {
                    int j = T[idx];
                    int Lb = (Ls[j] >>> b) & 1, Rb = (Rs[j] >>> b) & 1;
                    int sj = (S >>> idx) & 1;
                    if ((sj == 0 && Lb == 0) || (sj == 1 && Rb == 1)) cnt++;
                    if (sj == 1) { tt ^= D[j] >>> (b + 1); dd ^= (Lb ^ Rb); }
                }
                boolean ok = false;
                if (cnt >= 2) ok = true;
                else if (cnt == 1) {
                    if (!enBuilt) {
                        Arrays.fill(En, 0);
                        for (int k = 0; k < nc; k++) insert(En, ((D[nonT[k]] >>> (b + 1)) << 1) | 1);
                        if (fresh) insert(En, 1);
                        enBuilt = true;
                    }
                    int e = (tt << 1) | (dd & 1);
                    ok = reduce(En, e) == 0;
                }
                if (ok) return ans(b, M0);
            }
        }
        return M0;
    }

    public static void main(String[] args) throws IOException {
        int t = ni();
        StringBuilder sb = new StringBuilder();
        while (t-- > 0) {
            int n = ni();
            int[] Ls = new int[n], Rs = new int[n];
            for (int i = 0; i < n; i++) Ls[i] = ni();
            for (int i = 0; i < n; i++) Rs[i] = ni();
            sb.append(solve(n, Ls, Rs)).append('\n');
        }
        System.out.print(sb);
    }
}