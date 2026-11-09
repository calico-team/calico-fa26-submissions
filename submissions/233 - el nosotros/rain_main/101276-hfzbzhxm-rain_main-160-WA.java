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

        long total = N * K;

        if(N == 1){
            return K;
        }

        for(int i = 0; i < N-1; i++){
            for(int j = i+1; j < N; j++){
                total -= intersect(L.get(i),L.get(j),K);
            }
        }

        return total;
    }

    static long intersect(Drone d1, Drone d2, int K){
        if(d1.D == d2.D){
            return 0;
        }

        Drone u;
        Drone r;
        
        if(d1.D == 'E'){
            u = d2;
            r = d1;
        } else {
            u = d1;
            r = d2;
        }

        if(r.Y - u.Y == u.X - r.X && r.Y - u.Y < K && r.Y - u.Y > 0){
            return 1;
        }
        return 0;
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
