import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.StringTokenizer;

public class two {
    public static void main(String[] args) throws IOException {
        FastScanner sc = new FastScanner();
        StringBuilder sb = new StringBuilder();

        if (!sc.hasNext()) return;
        int T = sc.nextInt();

        while (T-- > 0) {
            int N = sc.nextInt();
            long R = sc.nextLong();

            long[] A = new long[N];
            for (int i = 0; i < N; i++) {
                A[i] = sc.nextLong();
            }

            long firstReady = 0;
            long secondReady = 0;
            boolean possible = true;

            for (long t : A) {
                if (secondReady != 0 && t >= secondReady) {
                    firstReady = 0;
                    secondReady = 0;
                } else if (firstReady != 0 && t >= firstReady) {
                    firstReady = secondReady;
                    secondReady = 0;
                }

                if (firstReady == 0) {
                    firstReady = t + R;
                } else if (secondReady == 0) {
                    secondReady = firstReady + R;
                } else {
                    possible = false;
                    break;
                }
            }

            sb.append(possible ? "YES" : "NO").append("\n");
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