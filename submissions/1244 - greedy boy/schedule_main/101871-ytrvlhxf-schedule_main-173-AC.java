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

    public static int h(int u, ArrayList<Integer>[] child, int[] memo) {
        if (memo[u] != 0) {
            return memo[u];
        }
        int longest = 1;
        for (int v : child[u]) {
            longest = Math.max(longest, 1 + h(v, child, memo));
        }
        memo[u] = longest;
        return longest;
    }

    public static void main(String[] args) throws IOException {
        Kattio io = new Kattio();
        int t = io.nextInt();
        for (int test = 0; test < t; test++) {
            int n = io.nextInt();
            int m = io.nextInt();
            int k = io.nextInt();
            ArrayList<Integer>[] child = new ArrayList[n + 1];
            for (int i = 0; i <= n; i++) {
                child[i] = new ArrayList<>();
            }
            int[] prereq = new int[n + 1];
            for (int i = 1; i <= n; i++) {
                prereq[i] = io.nextInt();
                if (prereq[i] != 0) {
                    child[prereq[i]].add(i);
                }
            }

            int[] memo = new int[n + 1];
            for (int i = 1; i <= n; i++) {
                h(i, child, memo);
            }
            PriorityQueue<Integer> pq = new PriorityQueue<>((a, b) -> Integer.compare(memo[b], memo[a]));
            for (int i = 1; i <= n; i++) {
                if (prereq[i] == 0) {
                    pq.add(i);
                }
            }
            int total = 0;

            for (int i = 0; i < m && !pq.isEmpty(); i++) {
                ArrayList<Integer> unlocked = new ArrayList<>();
                for (int j = 0; j < k && !pq.isEmpty(); j++) {
                    int course = pq.poll();
                    total++;
                    unlocked.addAll(child[course]);
                }
                pq.addAll(unlocked);
            }
            io.println(total);
        }
        io.close();
    }
}