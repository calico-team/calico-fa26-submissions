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
        long answer = 0;
        for (int t = 1; t <= K; t++) {
            HashSet<String> positions = new HashSet<>();
            for (Drone d : L) {
                long x = d.X;
                long y = d.Y;

                if (d.D == 'E') {
                    x += t;
                }
                else {
                    y += t;
                }

                positions.add(x + "#" + y);
            }
            answer += positions.size();
        }
        return answer;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

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

        sc.close();
    }
}