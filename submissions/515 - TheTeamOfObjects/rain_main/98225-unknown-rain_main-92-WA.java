import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Comparator;

public class prob4redone {
    public static void main(String[] args) throws Exception{
    
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);
        int testcases = Integer.parseInt(br.readLine());
        for (int i = 0; i < testcases; i++) {
            String[] info = br.readLine().split(" ");
            int num_drones = Integer.parseInt(info[0]);
            int num_nights = Integer.parseInt(info[1]);
            ArrayList<int[]> easternFlights = new ArrayList<int[]>();
            ArrayList<int[]> northernFlights = new ArrayList<int[]>();
            for (int j = 0; j < num_drones; j++) {
                String[] droneInfo = br.readLine().split(" ");
                if (droneInfo[3].equals("E")){
                    int[] infos = new int[2];
                    infos[0] = Integer.parseInt(droneInfo[0]);
                    infos[1] = Integer.parseInt(droneInfo[1]);
                    easternFlights.add(infos);
                } else {
                    int[] infos = new int[2];
                    infos[0] = Integer.parseInt(droneInfo[0]);
                    infos[1] = Integer.parseInt(droneInfo[1]);
                    northernFlights.add(infos);
                }
            }
            int subtract = 0;
            northernFlights.sort(new SortMyThingsX());
            // pw.println(Arrays.deepToString(northernFlights.toArray()));
            for (int j = 0; j < easternFlights.size(); j++) {
                for (int k = 0; k < northernFlights.size(); k++){
                    int[] ething;
                    int[] nthing;
                    if ((ething = easternFlights.get(j))[0] >= (nthing = northernFlights.get(k))[0]){
                        break;
                    }
                    else {
                        if (nthing[0] - ething[0] == ething[1] - nthing[1] && nthing[0] - ething[0] <= num_nights-1){
                            subtract ++;
                        }
                    }
                }
            }
            pw.println(num_drones * num_nights - subtract);
        }
        pw.flush();
    }
}

class SortMyThingsX implements Comparator<int[]>{
    @Override
    public int compare(int[] one, int[] two) {
        if (one[0] < two[0]) {
            return -1;
        }
        if (one[0] > two[0]) {
            return 1;
        }
        // if (one.y < two.y) {
        //     return -1;
        // }
        // if (one.y > two.y) {
        //     return 1;
        // }
        return 0;
    }
}
// class SortMyThingsX implements Comparator<Drone>{
//     @Override
//     public int compare(Drone one, Drone two) {
//         if (one.x < two.x) {
//             return -1;
//         }
//         if (one.x > two.x) {
//             return 1;
//         }
//         // if (one.y < two.y) {
//         //     return -1;
//         // }
//         // if (one.y > two.y) {
//         //     return 1;
//         // }
//         return 0;
//     }
// }

// class SortMyThingsY implements Comparator<Drone>{
//     @Override
//     public int compare(Drone one, Drone two) {
//         // if (one.x < two.x) {
//         //     return -1;
//         // }
//         // if (one.x > two.x) {
//         //     return 1;
//         // }
//         if (one.y < two.y) {
//             return -1;
//         }
//         if (one.y > two.y) {
//             return 1;
//         }
//         return 0;
//     }
// }
// class SortMyThingsY implements Comparator<int[]>{
//     @Override
//     public int compare(int[] one, int[] two) {
//         if (one[1] < two[1]) {
//             return -1;
//         }
//         if (one[1] > two[1]) {
//             return 1;
//         }
//         // if (one.y < two.y) {
//         //     return -1;
//         // }
//         // if (one.y > two.y) {
//         //     return 1;
//         // }
//         return 0;
//     }
// }



// class Drone{
//     public int x;
//     public int y;
//     public int z;
//     public char direction;
//     public int waterCollected = 0;
//     public Drone(int x, int y, int z, char direction) {
//         this.x = x;
//         this.y = y;
//         this.z = z;
//         this.direction = direction;
//     }
//     // public void move() {
//     //     switch(direction) {
//     //         case 'N':
//     //             y++;
//     //             break;
//     //         case 'E':
//     //             x++;
//     //             break;
//     //     }
//     // }
//     public String toString() {
//         return x + " " + y + " " + z;
//     }
// }