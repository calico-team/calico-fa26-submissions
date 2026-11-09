import java.io.*;
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
        long answer = 0;
        for (int t = 1; t <= K; t++) {
            HashSet<String> pos = new HashSet<>();
            for (Drone d : L) {
                long x = d.X;
                long y = d.Y;
                if (d.D == 'E')
                    x += t;
                else
                    y += t;
                pos.add(x + "#" + y);
            }
            answer += pos.size();
        }
        return answer;
    }
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int T = Integer.parseInt(br.readLine().trim());
        while (T-- > 0) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int N = Integer.parseInt(st.nextToken());
            int K = Integer.parseInt(st.nextToken());
            List<Drone> L = new ArrayList<>();
            for (int i = 0; i < N; i++) {
                st = new StringTokenizer(br.readLine());
                int X = Integer.parseInt(st.nextToken());
                int Y = Integer.parseInt(st.nextToken());
                int Z = Integer.parseInt(st.nextToken());
                char D = st.nextToken().charAt(0);
                L.add(new Drone(X, Y, Z, D));
            }
            System.out.println(solve(N, K, L));
        }
    }
}
