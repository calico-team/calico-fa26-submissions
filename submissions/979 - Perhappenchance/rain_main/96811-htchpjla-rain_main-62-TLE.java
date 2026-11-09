import java.util.*;

class SolutionRain {

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
        ArrayList<Integer> xcoords = new ArrayList<Integer>();
        ArrayList<Integer> ycoords = new ArrayList<Integer>();
        Drone drone;
        int x;
        int y;
        char direction;
        boolean contained;
        for (int night = 0; night < K; night++) {
            // calculate rain
            xcoords = new ArrayList<Integer>();
            ycoords = new ArrayList<Integer>();
            for (int i = 0; i < N; i++) {
                drone = L.get(i);
                x = drone.X;
                y = drone.Y;
                if (xcoords.isEmpty()) {
                    xcoords.add(x);
                    ycoords.add(y);
                    answer++;
                } else {
                    contained = false;
                    for (int p = 0; p < xcoords.size(); p++) {
                        if (xcoords.get(p) == x && ycoords.get(p) == y) {
                            contained = true;
                            break;
                        }
                    }
                    if (!contained) {
                        xcoords.add(x);
                        ycoords.add(y);
                        answer++;
                    }
                }
            }
            // move drones
            for (int i = 0; i < N; i++) {
                drone = L.get(i);
                direction = drone.D;
                if (direction == 'N') {
                    drone.Y += 1;
                } else {
                    drone.X += 1;
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
