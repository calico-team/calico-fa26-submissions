import java.util.*;
import java.io.*;
public class Main {
    static class Kattio extends PrintWriter {
        private BufferedReader r;
        private StringTokenizer st;

        public Kattio() {
            super(new BufferedWriter(new OutputStreamWriter(System.out)));
            r = new BufferedReader(new InputStreamReader(System.in));
        }

        public Kattio(String filename) throws IOException {
            super(new BufferedWriter(new FileWriter(filename + ".out")));
            r = new BufferedReader(new FileReader(filename + ".in"));
        }

        public String next() {
            try {
                while (st == null || !st.hasMoreTokens()) {
                    String line = r.readLine();
                    if (line == null) {
                        throw new NoSuchElementException("Unexpected end of input");
                    }
                    st = new StringTokenizer(line);
                }
                return st.nextToken();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        public int nextInt() {
            return Integer.parseInt(next());
        }

        public long nextLong() {
            return Long.parseLong(next());
        }
    }

    public static int lb(ArrayList<Integer> list, long target) {
        int left = 0;
        int right = list.size();
        while (left < right) {
            int mid = left + (right - left)/ 2;
            if (list.get(mid) < target) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return left;
    }

    public static void main(String[] args) throws IOException {
        Kattio io = new Kattio();
        int t = io.nextInt();
        for (int test = 0; test < t; test++) {
            int n = io.nextInt();
            long k = io.nextLong();
            HashMap<Integer, ArrayList<Integer>> north = new HashMap<>();
            ArrayList<int[]> east = new ArrayList<>();
            for (int i = 0; i < n; i++) {
                int x = io.nextInt();
                int y = io.nextInt();
                int z = io.nextInt();
                char d = io.next().charAt(0);
                int sum = x + y;

                if (d == 'N') {
                    if (!north.containsKey(sum)) {
                        north.put(sum, new ArrayList<>());
                    }
                    north.get(sum).add(x);
                } else {
                    east.add(new int[]{x, sum});
                }
            }
            for (ArrayList<Integer> list : north.values()) {
                Collections.sort(list);
            }
            long total = (long) n * k;

            for (int[] drone : east) {
                int x = drone[0];
                int sum = drone[1];
                if (!north.containsKey(sum)) {
                    continue;
                }
                ArrayList<Integer> list = north.get(sum);
                int left = lb(list, x);
                int right = lb(list, (long) x + k);
                total -= right - left;
            }
            io.println(total);
        }
        io.close();
    }
}