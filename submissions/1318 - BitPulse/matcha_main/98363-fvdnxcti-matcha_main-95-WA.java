import java.util.*;
public class Main {
    static class Range {
        long l, r;
        Range(long L, long R) { l = L; r = R; }
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        while (T-- > 0) {
            int n = sc.nextInt();
            long[] L = new long[n];
            long[] R = new long[n];
            for(int i=0;i<n;i++) L[i]=sc.nextLong();
            for(int i=0;i<n;i++) R[i]=sc.nextLong();
            List<Range> list = new ArrayList<>();
            for(int i=0;i<n;i++) list.add(new Range(L[i],R[i]));

            long ans = 0;
            for(int bit = 29; bit >=0; bit--){
                long candidate = ans | (1L << bit);
                Set<Long> dp = new HashSet<>();
                dp.add(0L);
                boolean valid = true;
                for(Range rg : list){
                    Set<Long> ndp = new HashSet<>();
                    long l = rg.l, r = rg.r;
                    for(long x : dp){
                        if (can(l, r, x, candidate)) {
                            ndp.add(x);
                        }
                    }
                    if(ndp.isEmpty()){
                        valid = false;
                        break;
                    }
                    dp = ndp;
                }
                if(valid) ans = candidate;
            }
            System.out.println(ans);
        }
    }
    static boolean can(long L, long R, long x, long mask) {
        long target = (x ^ mask) & mask;
        return rangeHas(L,R,mask,target);
    }
    static boolean rangeHas(long L, long R, long mask, long target) {
        if ((target & (~mask)) != 0) return false;
        long step = mask + 1;
        long base = L / step * step;
        long cur = base + target;
        if (cur < L) cur += step;
        return cur <= R;
    }
}