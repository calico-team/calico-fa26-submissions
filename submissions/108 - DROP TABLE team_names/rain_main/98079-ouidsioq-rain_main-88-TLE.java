import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Scanner;
import java.util.Set;

public class Solution2 {

    static long posX(Drone d, int t) {
        if (d.D == 'E') {
            return d.X + t;
        }
        return d.X;
    }

    static long posY(Drone d, int t) {
        if (d.D == 'N') {
            return d.Y + t;
        }
        return d.Y;
    }

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
    static long solve(int N, int K, List<Drone> L) {
        long answer = (long) N * K;
        for (int i = 0; i < L.size(); i++) {
            Drone d = L.get(i);
            Set<Long> remset = new HashSet<>();
            for (int j = 0; j < i; j++) {
                long t = wtfkskskskskskksk(d, L.get(j));
                if (t >= 0 && t < K) {
                    remset.add(t);
                }
            }
            answer -= remset.size();
        }
        return answer;
    }

    static long wtfkskskskskskksk(Drone d, Drone o) {
        Drone e = d;
        Drone n = o;
        if (e.D == n.D)
            return -1; // same dir
        if (d.D == 'N') {
            e = o;
            n = d;
        }
        if (n.X - e.X == e.Y - n.Y) {
            return n.X - e.X;
        }
        return -1;
    }

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
