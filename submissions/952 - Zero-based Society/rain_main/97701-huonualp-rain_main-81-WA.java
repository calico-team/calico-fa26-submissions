import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.StringTokenizer;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

public class four {

    static class Drone {
        long x, y, z;
        char d;

        Drone(long x, long y, long z, char d) {
            this.x = x;
            this.y = y;
            this.z = z;
            this.d = d;
        }
    }

    public static void main(String[] args) throws IOException {
        FastScanner sc = new FastScanner();
        StringBuilder sb = new StringBuilder();

        if (!sc.hasNext()) return;
        int T = sc.nextInt();

        while (T-- > 0) {
            int N = sc.nextInt();
            long K = sc.nextLong();

            Drone[] drones = new Drone[N];
            for (int i = 0; i < N; i++) {
                drones[i] = new Drone(sc.nextLong(), sc.nextLong(), sc.nextLong(), sc.next().charAt(0));
            }

            long totalWater = 0;

            // Group drones by diagonal constant (X + Y) for intersecting E and N drones
            Map<Long, ArrayList<Drone>> eMap = new HashMap<>();
            Map<Long, ArrayList<Drone>> nMap = new HashMap<>();

            for (Drone drone : drones) {
                long key = drone.x + drone.y;
                if (drone.d == 'E') {
                    eMap.computeIfAbsent(key, k -> new ArrayList<>()).add(drone);
                } else {
                    nMap.computeIfAbsent(key, k -> new ArrayList<>()).add(drone);
                }
            }

            for (Drone drone : drones) {
                long key = drone.x + drone.y;
                Set<Long> blockedDays = new HashSet<>();

                if (drone.d == 'E') {
                    // Check opposing North drones along the same diagonal (X + Y)
                    ArrayList<Drone> candidates = nMap.get(key);
                    if (candidates != null) {
                        for (Drone other : candidates) {
                            if (other.z > drone.z) {
                                long t = other.x - drone.x;
                                if (t >= 0 && t < K && (drone.y - other.y == t)) {
                                    blockedDays.add(t);
                                }
                            }
                        }
                    }
                } else { // drone.d == 'N'
                    // Check opposing East drones along the same diagonal (X + Y)
                    ArrayList<Drone> candidates = eMap.get(key);
                    if (candidates != null) {
                        for (Drone other : candidates) {
                            if (other.z > drone.z) {
                                long t = other.y - drone.y;
                                if (t >= 0 && t < K && (other.x - drone.x == t)) {
                                    blockedDays.add(t);
                                }
                            }
                        }
                    }
                }

                totalWater += (K - blockedDays.size());
            }

            sb.append(totalWater).append("\n");
        }

        System.out.print(sb.toString());
    }

    static class FastScanner {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;

        boolean hasNext() {
            while (st == null || !st.hasMoreTokens()) {
                try {
                    String line = br.readLine();
                    if (line == null) return false;
                    st = new StringTokenizer(line);
                } catch (IOException e) {
                    return false;
                }
            }
            return true;
        }

        String next() {
            while (st == null || !st.hasMoreTokens()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }

        int nextInt() {
            return Integer.parseInt(next());
        }

        long nextLong() {
            return Long.parseLong(next());
        }
    }
}