import java.io.*;
import java.util.*;

class Solution {

    static class Drone {
        int X, Y, Z;
        char D;

        Drone(int X, int Y, int Z, char D) {
            this.X = X;
            this.Y = Y;
            this.Z = Z;
            this.D = D;
        }
    }

 
    static long solve(int N, int K, List<Drone> L) {
        // Group by X+Y; meetings only between one E and one N on the same diagonal.
        HashMap<Integer, ArrayList<Integer>> east = new HashMap<>();
        HashMap<Integer, ArrayList<Integer>> north = new HashMap<>();

        for (Drone d : L) {
            int s = d.X + d.Y;
            if (d.D == 'E') {
                east.computeIfAbsent(s, k -> new ArrayList<>()).add(d.X);
            } else {
                north.computeIfAbsent(s, k -> new ArrayList<>()).add(d.X);
            }
        }

        long meetings = 0;
        for (Map.Entry<Integer, ArrayList<Integer>> e : east.entrySet()) {
            ArrayList<Integer> nxs = north.get(e.getKey());
            if (nxs == null) continue;
            ArrayList<Integer> exs = e.getValue();
            Collections.sort(exs);
            for (int xn : nxs) {
                // xe in [xn - K + 1, xn]
                long lo = (long) xn - K + 1;
                int left = lowerBound(exs, lo);
                int right = upperBound(exs, xn);
                meetings += right - left;
            }
        }

        return (long) N * K - meetings;
    }

    // first index with value >= target
    static int lowerBound(ArrayList<Integer> a, long target) {
        int lo = 0, hi = a.size();
        while (lo < hi) {
            int mid = (lo + hi) >>> 1;
            if (a.get(mid) >= target) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }

    // first index with value > target
    static int upperBound(ArrayList<Integer> a, int target) {
        int lo = 0, hi = a.size();
        while (lo < hi) {
            int mid = (lo + hi) >>> 1;
            if (a.get(mid) > target) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int T = Integer.parseInt(br.readLine().trim());
        while (T-- > 0) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int N = Integer.parseInt(st.nextToken());
            int K = Integer.parseInt(st.nextToken());

            List<Drone> L = new ArrayList<>(N);
            for (int i = 0; i < N; i++) {
                st = new StringTokenizer(br.readLine());
                int X = Integer.parseInt(st.nextToken());
                int Y = Integer.parseInt(st.nextToken());
                int Z = Integer.parseInt(st.nextToken());
                char D = st.nextToken().charAt(0);
                L.add(new Drone(X, Y, Z, D));
            }

            out.println(solve(N, K, L));
        }
        out.flush();
    }
}
