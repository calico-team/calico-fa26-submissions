import java.util.*;
import java.util.Map.Entry;

class Rain {

    // Helper class to represent a Drone tuple
    static class Drone {
        long pos;
        int x, y, z;
        char D;

        Drone(int X, int Y, int Z, char D) {
            this.x = X; this.y = Y; this.z = Z;
            pos = Y * 10000 + X;
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
        long answer = 1L * N * K;
        HashMap<Long,ArrayList<Drone>> map = new HashMap<>();
        for(Drone d : L) {
            long xy = d.x + d.y;
            if(map.containsKey(xy)) map.get(xy).add(d);
            else {
                ArrayList<Drone> out = new ArrayList<>();
                out.add(d);
                map.put(xy, out);
            }
        }
        for(ArrayList<Drone> e : map.values()) {
            ArrayList<Drone> easts = new ArrayList<>();
            ArrayList<Drone> norths = new ArrayList<>();
            
            for(Drone d : e) {
                if(d.D == 'N')norths.add(d);
                else easts.add(d);
            }
            for(Drone nor : norths) {
                for(Drone eas : easts) {
                    int night = nor.x - eas.x + 1;
                    if(night > 0 && night <= K) answer--;
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
