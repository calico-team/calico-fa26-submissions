import java.util.*;

class Solution {

    // Helper class to represent a Drone tuple
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
    *   X: Starting X location of Drone
    *   Y: Starting Y location of Drone
    *   Z: Starting Z location of Drone
    *   D: Starting direction of Drone
    */
    static long solve(int N, int K, List<Drone> L) {
        long finalresult = (long) N * K;

    Map<Integer, List<Drone>> categories = new HashMap<>();

    for (int p = 0; p < N; p++) {

        Drone d = L.get(p);
          int legend = d.X + d.Y;

        if (!categories.containsKey(legend)) {
            categories.put(legend, new ArrayList<>()); }
        

        categories.get(legend).add(d);
    }

    for (int legend : categories.keySet()) {

        List<Drone> category =  categories.get(legend);

        List<Drone> left = new ArrayList<>();
           List<Drone> up = new ArrayList<>();

        for (int p = 0; p < category.size(); p++) {

              Drone d = category.get(p);

            if (d.D == 'E') {
                left.add(d);
            } else {
                up.add(d);     }
            
        }

        for (int p = 0; p < left.size(); p++) {

            Drone l = left.get(p);

            for (int q = 0; q < up.size(); q++) {

                Drone u = up.get(q);

                if (u.Z > l.Z &&
                    u.X >= l.X &&
                    u.X <= (long) l.X + K - 1) {

                    finalresult--;
                }

                if (l.Z > u.Z &&
                    l.X <= u.X &&
                    l.X >= (long) u.X - K + 1) {

                    finalresult--;
                }
            }
        }
    }

    return finalresult;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        if (!sc.hasNextInt()) return;

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
