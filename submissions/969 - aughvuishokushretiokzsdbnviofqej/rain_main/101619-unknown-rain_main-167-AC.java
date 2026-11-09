import java.util.*;

import static java.lang.Math.abs;

class Main {

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
        long answer = ((long) K) * L.size();
        HashMap<Integer, ArrayList<Drone>> map = new HashMap<Integer, ArrayList<Drone>>();
        for (Drone d : L) {
            if (map.containsKey(d.X + d.Y)) {
                map.get(d.X + d.Y).add(d);
            }
            else {
                map.put(d.X + d.Y, new ArrayList<Drone>(List.of(d)));
            }
        }
        for (int key : map.keySet()) {
            ArrayList<Drone> list = map.get(key);
            for (int i = 0; i < list.size(); i++) {
                Drone d1 = list.get(i);
                int X1 = d1.X;
                char D1 = d1.D;
                for (int j = i; j < list.size(); j++) {
                    Drone d2 = list.get(j);
                    int X2 = d2.X;
                    char D2 = d2.D;
                    if (D1 == D2) {
                        continue;
                    }
                    if ((D1 == 'E' && X1 < X2) || (D1 == 'N' && X1 > X2)) {
                        if (Math.abs(X1 - X2) < K) {
                            answer--;
                        }
                    }
                }
            }
        }
        return answer;
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
