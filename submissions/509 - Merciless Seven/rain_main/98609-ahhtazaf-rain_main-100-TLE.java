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
    static long solve(int N, int K, List<Drone> L) 
    {
       long sum = 0;
       for(int night = 0; night < K; night++)
       {
            // for(int droneNum = 0; droneNum<N; droneNum++)//collection
            // {
            //     boolean canAdd = true;
            //     Drone temp = L.get(droneNum);
            //     for(Drone d : L)
            //     {
            //         if(!(d==temp))
            //             if(d.X==temp.X&&d.Y==temp.Y&&(!(d.Z>temp.Z)))
            //             {
            //                 canAdd=false;
            //                 break;
            //             }
            //     }
            //     if(canAdd)
            //     {
            //         sum++;
            //     }
            // }
            HashMap<String,Integer> map = new HashMap<>();
            for(Drone d : L)//assignment
            {
                map.put((""+d.X+","+d.Y),(Math.max(map.getOrDefault((""+d.X+","+d.Y),d.Z),(d.Z))));
            }
            for(Drone d : L)//collection
            {
                if(d.Z>=map.get(""+d.X+","+d.Y))
                    sum++;
            }
            for(Drone d : L)//movement
            {
                if(d.D=='N')
                    d.Y++;
                else
                    d.X++;
            }
       }
        return sum;
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
