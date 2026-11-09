import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Comparator;

public class prob4 {
    public static void main(String[] args) throws Exception{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);
        int testcases = Integer.parseInt(br.readLine());
        for (int i = 0; i < testcases; i++) {
            String[] info = br.readLine().split(" ");
            int num_drones = Integer.parseInt(info[0]);
            int num_nights = Integer.parseInt(info[1]);
            Drone[] drones = new Drone[num_drones];
            for (int j = 0; j < num_drones; j++) {
                String[] droneInfo = br.readLine().split(" ");
                drones[j] = new Drone(Integer.parseInt(droneInfo[0]), Integer.parseInt(droneInfo[1]), Integer.parseInt(droneInfo[2]), droneInfo[3].charAt(0));
            }

            for (int j = 0; j < num_nights
                ; j++) {
                SortMyThings comparatorThings = new SortMyThings();
                Arrays.sort(drones, comparatorThings);
                // pw.println(Arrays.toString(drones));
                int lastX = -1;
                int lastY = -1;
                for (int k = 0; k < num_drones; k++) {
                    if (drones[k].x == lastX && drones[k].y == lastY){
                        // pw.println("caught the thing");
                        drones[k].move();
                        continue;
                    }
                    lastX = drones[k].x;
                    lastY = drones[k].y;
                    drones[k].waterCollected++;
                    drones[k].move();
                }
            }
            int result = 0;
            for (int j = 0; j < num_drones; j++) {
                result += drones[j].waterCollected;
            }
            pw.println(result);
        
        }
        pw.flush();
    }
}

class SortMyThings implements Comparator<Drone>{
    @Override
    public int compare(Drone one, Drone two) {
        if (one.x < two.x) {
            return -1;
        }
        if (one.x > two.x) {
            return 1;
        }
        if (one.y < two.y) {
            return -1;
        }
        if (one.y > two.y) {
            return 1;
        }
        return 0;
    }
}

class Drone{
    public int x;
    public int y;
    public int z;
    public char direction;
    public int waterCollected = 0;
    public Drone(int x, int y, int z, char direction) {
        this.x = x;
        this.y = y;
        this.z = z;
        this.direction = direction;
    }
    public void move() {
        switch(direction) {
            case 'N':
                y++;
                break;
            case 'E':
                x++;
                break;
        }
    }
    public String toString() {
        return x + " " + y + " " + z;
    }
}
