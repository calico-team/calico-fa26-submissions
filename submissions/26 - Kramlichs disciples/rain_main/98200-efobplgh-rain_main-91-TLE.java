import java.util.*;

class Solution {

    static class Drone {
        int X, Y, Z;
        char D;
        int rain;

        Drone(int X, int Y, int Z, char D) {
            this.X = X;
            this.Y = Y;
            this.Z = Z;
            this.D = D;
        }

        boolean isAbove(Drone d) {
            return this.X == d.X && this.Y == d.Y && this.Z > d.Z;
        }

        void move() {
            if (D == 'E') {
                X++;
            } else if (D == 'N') {
                Y++;
            }
        }

        void collect() {
            rain++;
        }

        int getRain() {
            return rain;
        }
    }

    static long solve(int N, int K, List<Drone> L) {
        for (int night = 0; night < K; night++) {
            for (int d = 0; d < L.size(); d++) {
                boolean blocked = false;

                for (int c = 0; c < L.size(); c++) {
                    if (c != d && L.get(c).isAbove(L.get(d))) {
                        blocked = true;
                        break;
                    }
                }

                if (!blocked) {
                    L.get(d).collect();
                }
            }

            for (Drone drone : L) {
                drone.move();
            }
        }

        long answer = 0;
        for (Drone drone : L) {
            answer += drone.getRain();
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
