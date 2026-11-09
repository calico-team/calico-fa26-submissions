import java.io.*;
import java.util.*;

public class MyProgram {
    static void solve(int n, long r, long[] a) {
        int charges = 2;
        long ready = Long.MAX_VALUE;
        boolean possible = true;
        for (int i = 0; i < n; i++) {
            long t = a[i];
            while (charges < 2 && ready <= t) {
                charges++;
                if (charges < 2) {
                    ready = ready + r;
                } else {
                    ready = Long.MAX_VALUE;
                }
            }
            if (charges == 0) {
                possible = false;
                break;
            }
            charges--;
            if (ready == Long.MAX_VALUE) {
                ready = t + r;
            }
        }
        if (possible) {
            System.out.println("YES");
        } else {
            System.out.println("NO");
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int T = Integer.parseInt(br.readLine().trim());
        for (int tc = 0; tc < T; tc++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int n = Integer.parseInt(st.nextToken());
            long r = Long.parseLong(st.nextToken());

            st = new StringTokenizer(br.readLine());
            long[] a = new long[n];
            for (int i = 0; i < n; i++) {
                a[i] = Long.parseLong(st.nextToken());
            }
            solve(n, r, a);
        }
    }
}