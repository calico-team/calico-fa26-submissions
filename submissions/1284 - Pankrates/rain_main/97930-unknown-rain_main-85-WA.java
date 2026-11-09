import java.util.*;
import java.util.HashSet;

class Solution {

    static class Location {
        int X, Y;

        Location(int X, int Y) {
            this.X = X;
            this.Y = Y;
        }
    }

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

    // def solve(N: int, K: int, L: list):

    // collected = 0
    // used_locations = set()

    // for _

    // in range(K):
    //     for drone in range(N):
    //         if (L[drone][0], L[drone][1]) not in used_locations:
    //             used_locations.add((L[drone][0], L[drone][1]))
    //             collected += 1
    //         if L[drone][2] == "E":
    //             L[drone] = (L[drone][0] + 1, L[drone][1], L[drone][2])
    //         else:
    //             L[drone] = (L[drone][0], L[drone][1] + 1, L[drone][2])
    //     used_locations.clear()

    // # for drone in range(N):
    // #     for night in range(K):
    // #         if L[drone][2] == "E":
    // #             used_locations.add((L[drone][0] + night, L[drone][1]))
    // #         else:
    // #             used_locations.add((L[drone][0], L[drone][1] + night))


    // return collected
    // return len(used_locations)

    static long solve(int N, int K, List<Drone> L) {

        HashSet<Location> seen = new HashSet<Location>();
        long answer = 0;


        for (int i = 0; i < K; i ++) {
            for (int j = 0; j < N; j ++) {
                Drone drone = L.get(j);
                // if (seen.contains(new Location(L.get(drone).X, L.get(drone).Y)));
                seen.add(new Location(drone.X, drone.Y));

                if (drone.D == 'E') {
                    drone.X ++;
                }
                else {
                    drone.Y ++;
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
