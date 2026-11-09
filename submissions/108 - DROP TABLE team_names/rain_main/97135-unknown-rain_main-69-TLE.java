import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

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
        for (int t = 0; t < K; t++) {
            for (int i = 0; i < L.size(); i++) {
                Drone d = L.get(i);
                long calcx = posX(d, t);
                long calcy = posY(d, t);
                for (int j = 0; j < i; j++) {
                    Drone o = L.get(j);
                    if (calcx == posX(o, t) && calcy == posY(o, t)) {
                        answer--;
                        break;
                    }
                }
            }
        }
        return answer;
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
