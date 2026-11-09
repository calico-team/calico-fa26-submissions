import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class Solution7 {

    public static void main(String[] args) {
        FastReader in = new FastReader();
        PrintWriter out = new PrintWriter(System.out);

        String tStr = in.next();
        if (tStr == null) return;
        int T = Integer.parseInt(tStr);

        // Pre-allocate queue arrays for up to 100,005 elements to bypass GC overhead
        long[] q = new long[100005];

        while (T-- > 0) {
            int N = in.nextInt();
            long R = in.nextLong();

            long[] A = new long[N];
            for (int i = 0; i < N; i++) {
                A[i] = in.nextLong();
            }

            int head = 0, tail = 0;
            boolean possible = true;

            for (int i = 0; i < N; i++) {
                long t = A[i];

                // Remove recharges that have finished by timestamp t
                while (head < tail && q[head] <= t) {
                    head++;
                }

                // If 2 charges are currently recharging, no charge is available (queue size = tail - head)
                if ((tail - head) >= 2) {
                    possible = false;
                    break;
                }

                // Use a charge at time t and schedule the new recharge sequentially
                long startTime = (head == tail) ? t : q[tail - 1];
                q[tail++] = startTime + R;
            }

            if (possible) {
                out.println("YES");
            } else {
                out.println("NO");
            }
        }
        out.flush();
    }

    // Fast I/O Utility class
    static class FastReader {
        BufferedReader br;
        StringTokenizer st;

        public FastReader() {
            br = new BufferedReader(new InputStreamReader(System.in));
        }

        String next() {
            while (st == null || !st.hasMoreElements()) {
                try {
                    String line = br.readLine();
                    if (line == null) return null;
                    st = new StringTokenizer(line);
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