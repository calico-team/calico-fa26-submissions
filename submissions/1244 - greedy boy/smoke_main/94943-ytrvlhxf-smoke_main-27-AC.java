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

    public static void main(String[] args) throws IOException {
        Kattio io = new Kattio();
        int t = io.nextInt();
        for (int test = 0; test < t; test++) {
            int n = io.nextInt();
            int r = io.nextInt();
            int charges = 2;
            long nextCharge = -1;
            long[] a = new long[n];
            boolean smoke = true;
            for (int i = 0; i < n; i++) {
                a[i] = io.nextLong();
                if (!smoke) {
                    continue;
                }
                while (nextCharge != -1 && nextCharge <= a[i]) {
                    charges++;
                    if (charges == 2) {
                        nextCharge = -1;
                    } else {
                        nextCharge += r;
                    }
                }
                if (charges == 0) {
                    smoke = false;
                } else {
                    charges--;
                    if (nextCharge == -1) {
                        nextCharge = a[i] + r;
                    }
                }
            }
            if (smoke) {
                io.println("YES");
            } else {
                io.println("NO");
            }
        }
        io.close();
    }
}