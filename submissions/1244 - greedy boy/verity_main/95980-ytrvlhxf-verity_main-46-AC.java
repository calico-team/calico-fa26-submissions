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
            int k = io.nextInt();
            char[] letters = new char[k];
            for (int i = 0; i < k; i++) {
                letters[i] = io.next().charAt(0);
            }
            char[] guess = new char[n];
            Arrays.fill(guess, letters[0]);
            for (int j = 0; j < k; j++) {
                io.println(new String(guess));
                io.flush();
                String response = io.next();
                if (response.equals("CORRECT")) {
                    break;
                }

                for (int i = 0; i < n; i++) {
                    if (response.charAt(i) == '_') {
                        guess[i] = letters[j + 1];
                    }
                }
            }
        }
        io.close();
    }
}