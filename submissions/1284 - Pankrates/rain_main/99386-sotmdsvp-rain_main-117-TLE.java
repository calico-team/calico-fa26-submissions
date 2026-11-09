import java.util.*;
import java.util.HashSet;

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

    static long solve(int N, int K, List<Drone> L) {

        HashSet<Long> seen = new HashSet<>();
        long answer = 0;


        for (int i = 0; i < K; i++) {
            for (int j = 0; j < N; j++) {
                Drone drone = L.get(j);

                long packed = (((long) drone.X << 32) ^ (drone.Y) & 0xFFFFFFFFL);
                seen.add(packed);

                if (drone.D == 'E') {
                    drone.X++;
                }
                else {
                    drone.Y++;
                }
            }   
            answer += seen.size();
            seen.clear();
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
