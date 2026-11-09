import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

public class Solution2 {

    /*
     * static long posX(Drone d, int t) {
     * if (d.D == 'E') {
     * return d.X + t;
     * }
     * return d.X;
     * }
     */

    /*
     * static long posY(Drone d, int t) {
     * if (d.D == 'N') {
     * return d.Y + t;
     * }
     * return d.Y;
     * }
     */

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

    /*
     * Return an integer denoting the amount of rain collected after the Kth nights
     * 
     * N: Number of drones
     * K: Number of nights
     * L: a list in this order [X, Y, Z, D] for each drone
     * X: Starting X location of Drone
     * Y: Starting Y location of Drone
     * Z: Starting Z location of Drone
     * D: Starting direction of Drone
     */
    // group xpy for n and sort
    // search e for
    /*
     * static long solve(int N, int K, List<Drone> L) {
     * long answer = (long) N * K;
     * for (int i = 0; i < L.size(); i++) {
     * Drone d = L.get(i);
     * for (int j = 0; j < i; j++) {
     * long t = wtfkskskskskskksk(d, L.get(j));
     * if (t >= 0 && t < K) {
     * answer--;
     * }
     * }
     * }
     * 
     * return answer;
     * }
     */
    static long solve(int N, int K, List<Drone> L) {
        long answer = (long) N * K;

        Map<Long, List<Long>> n = new HashMap<>();
        for (Drone d : L) {
            if (d.D == 'N') {
                /*
                 * if (xposlist == null) {
                 * xposlist = new ArrayList<>();
                 * n.put((long) d.X + d.Y, xposlist);
                 * }
                 */
                n.putIfAbsent((long) d.X + d.Y, new ArrayList<>());
                List<Long> xposlist = n.get((long) d.X + d.Y);
                xposlist.add((long) d.X);
            }
        }
        for (List<Long> xpoList : n.values()) {
            Collections.sort(xpoList);
        }
        for (Drone d : L) {
            if (d.D == 'E') {
                List<Long> xpolist = n.get((long) d.X + d.Y);
                if (xpolist != null) {
                    answer -= indexgreater(xpolist, (long) d.X + K) - indexgreater(xpolist, d.X); // 25 - (1 - 0) - (2 -
                                                                                                  // 0)
                }
            }
        }

        return answer;
    }

    // getfirst index bigger than given x val
    static int indexgreater(List<Long> xposlist, long x) {
        int i = Collections.binarySearch(xposlist, x);
        if (i < 0) {
            return -1 - i; // rev to insertion point if can't find
        }
        return i;
    }

    /*
     * static long wtfkskskskskskksk(Drone d, Drone o) {
     * Drone e = d;
     * Drone n = o;
     * if (e.D == n.D)
     * return -1; // same dir
     * if (d.D == 'N') {
     * e = o;
     * n = d;
     * }
     * if (n.X - e.X == e.Y - n.Y) {
     * return n.X - e.X;
     * }
     * return -1;
     * }
     */

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        if (!sc.hasNextInt())
            return;

        int T = sc.nextInt();
        while (T-- > 0) {
            int N = sc.nextInt();
            int K = sc.nextInt();

            List<Drone> L = new ArrayList<>();
            for (int i = 0; i < N; i++) {
                int X = sc.nextInt();
                int Y = sc.nextInt();
                int Z = sc.nextInt();
                char D = sc.next().charAt(0);
                L.add(new Drone(X, Y, Z, D));
            }

            System.out.println(solve(N, K, L));
        }
    }

}
