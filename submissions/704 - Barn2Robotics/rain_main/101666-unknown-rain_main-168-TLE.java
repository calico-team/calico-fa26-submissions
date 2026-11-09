import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;

public class Solution {

    static class Drone {
        int x;
        int y;
        int z;
        char d;

        public Drone(int x, int y, int z, char d) {
            this.x = x;
            this.y = y;
            this.z = z;

            this. d = d;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out, true);

        int testNum = Integer.parseInt(br.readLine());
        ArrayList<Long> xAxis = new ArrayList<Long>(0);
        ArrayList<Long> yAxis = new ArrayList<Long>(0);
        ArrayList<Long> zAxis = new ArrayList<Long>(0);

        for (int z = 0; z < testNum; z++) {
            long count = 0;

            String[] temp = br.readLine().split(" ");
            long droneNum = Integer.parseInt(temp[0]);
            long nightNum = Integer.parseInt(temp[1]);

            xAxis.clear();
            yAxis.clear();
            zAxis.clear();

            ArrayList<Drone> drones = new ArrayList<Drone>((int) droneNum);

            for (int i = 0; i < droneNum; i++) {
                temp = br.readLine().split(" ");

                drones.add(new Drone(
                        Integer.parseInt(temp[0]),
                        Integer.parseInt(temp[1]),
                        Integer.parseInt(temp[2]),
                        temp[3].charAt(0)
                ));

                Drone tempDrone = drones.get(i);

                while (xAxis.size()-1 < tempDrone.x) {
                    xAxis.add(0L);
                }
                while (yAxis.size()-1 < tempDrone.y) {
                    yAxis.add(0L);
                }
                while (zAxis.size()-1 < tempDrone.z) {
                    zAxis.add(0L);
                }

                xAxis.set(tempDrone.x, 1L);
                yAxis.set(tempDrone.y, 1L);
                zAxis.set(tempDrone.z, 1L);
            }


            for (int i = 0; i<nightNum; i++) {

                for (Drone drone1 : drones) {
                    for (Drone droneCompare : drones) {
                        if (drone1.z != droneCompare.z) {
                            if (drone1.x == droneCompare.x
                                    && drone1.y == droneCompare.y) {

                                if (drone1.z < droneCompare.z) {
                                    xAxis.set(drone1.x, 2L);
                                    yAxis.set(drone1.y, 2L);
                                    zAxis.set(drone1.z, 2L);
                                    count++;
                                }
                            }
                        }
                    }
                }

                for (Drone tempDrone : drones) {
                    if (xAxis.get(tempDrone.x) != 2L &&
                            yAxis.get(tempDrone.y) != 2L &&
                            zAxis.get(tempDrone.z) != 2L) {
                        count++;
                    }
                }

                for (Drone tempDrone : drones) {
                    xAxis.set(tempDrone.x, 0L);
                    yAxis.set(tempDrone.y, 0L);
                    zAxis.set(tempDrone.z, 0L);
                }
                for (Drone tempDrone : drones) {
                    if (tempDrone.d == 'E') {
                        xAxis.set(tempDrone.x, 0L);
                        yAxis.set(tempDrone.y, 0L);
                        zAxis.set(tempDrone.z, 0L);

                        if (tempDrone.x+1 < 100000) {
                            if (tempDrone.x+1 >= xAxis.size()) {
                                xAxis.add(0L);
                            }
                            tempDrone.x++;
                        }
                        xAxis.set(tempDrone.x, 1L);
                        yAxis.set(tempDrone.y, 1L);
                        zAxis.set(tempDrone.z, 1L);
                    } else if (tempDrone.d == 'N') {
                        xAxis.set(tempDrone.x, 0L);
                        yAxis.set(tempDrone.y, 0L);
                        zAxis.set(tempDrone.z, 0L);

                        if (tempDrone.y+1 < 100000) {
                            if (tempDrone.y+1 >= yAxis.size()) {
                                yAxis.add(0L);
                            }
                            tempDrone.y++;
                        }
                        xAxis.set(tempDrone.x, 1L);
                        yAxis.set(tempDrone.y, 1L);
                        zAxis.set(tempDrone.z, 1L);
                    }
                }
            }

            out.println(count);
        }

    }




}
