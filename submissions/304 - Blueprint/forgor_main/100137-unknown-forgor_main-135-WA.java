import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.StringTokenizer;
import java.util.ArrayList;

public class seven {
    public static void main(String[] args) throws IOException {
        amnesiac();
    }

    public static void amnesiac() throws IOException {
        FastScanner sc = new FastScanner();
        if (!sc.hasNext()) return;

        String phase = sc.next();

        if (phase.equals("FIRST")) {
            int N = sc.nextInt();
            int[] xorSum = new int[N + 1];
            int[] deg = new int[N + 1];

            for (int i = 0; i < N - 1; i++) {
                int u = sc.nextInt();
                int v = sc.nextInt();
                xorSum[u] ^= v;
                xorSum[v] ^= u;
                deg[u]++;
                deg[v]++;
            }

            StringBuilder sb = new StringBuilder();
            for (int i = 1; i <= N; i++) {
                long val = ((long) deg[i] << 18) | xorSum[i];
                sb.append(val).append(i == N ? "" : " ");
            }
            System.out.println(sb.toString());

        } else if (phase.equals("SECOND")) {
            read_your_input(sc);
        }
    }

    public static void read_your_input(FastScanner sc) {
        int N = sc.nextInt();
        long[] A = new long[N + 1];
        int missingIdx = -1;

        for (int i = 1; i <= N; i++) {
            A[i] = sc.nextLong();
            if (A[i] == -1) {
                missingIdx = i;
            }
        }

        long sumDeg = 0;
        int knownXorSum = 0;

        for (int i = 1; i <= N; i++) {
            if (i != missingIdx) {
                long d = A[i] >> 18;
                int xs = (int) (A[i] & ((1 << 18) - 1));
                sumDeg += d;
                knownXorSum ^= xs;
            }
        }

        long missingDeg = 2L * (N - 1) - sumDeg;
        int missingXorSum = knownXorSum;

        A[missingIdx] = (missingDeg << 18) | missingXorSum;

        int[] deg = new int[N + 1];
        int[] xorSum = new int[N + 1];
        ArrayList<Integer> leafQueue = new ArrayList<>();

        for (int i = 1; i <= N; i++) {
            deg[i] = (int) (A[i] >> 18);
            xorSum[i] = (int) (A[i] & ((1 << 18) - 1));
            if (deg[i] == 1) {
                leafQueue.add(i);
            }
        }

        StringBuilder sb = new StringBuilder();
        int ptr = 0;
        while (ptr < leafQueue.size()) {
            int u = leafQueue.get(ptr++);
            if (deg[u] != 1) continue;

            int v = xorSum[u];
            sb.append(u).append(" ").append(v).append("\n");

            deg[u]--;
            deg[v]--;
            xorSum[v] ^= u;

            if (deg[v] == 1) {
                leafQueue.add(v);
            }
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