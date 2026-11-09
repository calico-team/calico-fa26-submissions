import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(br.readLine().trim());

        for (int c = 0; c < t; c++) {
            String[] a = br.readLine().trim().split(" ");
            int n = Integer.parseInt(a[0]);
            long k = Long.parseLong(a[1]);

            long[] x = new long[n];
            long[] y = new long[n];
            String[] d = new String[n];

            for (int i = 0; i < n; i++) {
                a = br.readLine().trim().split(" ");
                x[i] = Long.parseLong(a[0]);
                y[i] = Long.parseLong(a[1]);
                d[i] = a[3];
            }

            long[] ea = new long[n];
            long[] no = new long[n];
            int ec = 0;
            int nc = 0;

            for (int i = 0; i < n; i++) {
                long v = (x[i] + y[i]) * 1000000 + x[i];
                if (d[i].equals("E")) {
                    ea[ec] = v;
                    ec++;
                } else {
                    no[nc] = v;
                    nc++;
                }
            }

            Arrays.sort(ea, 0, ec);
            Arrays.sort(no, 0, nc);

            long m = 0;
            int p = 0;
            int q = 0;

            for (int j = 0; j < nc; j++) {
                long v = no[j];
                long s = (v / 1000000) * 1000000;
                long l = v - (k - 1);
                if (l < s) {
                    l = s;
                }
                while (p < ec && ea[p] < l) {
                    p++;
                }
                while (q < ec && ea[q] <= v) {
                    q++;
                }
                m += q - p;
            }

            System.out.println(n * k - m);
        }
    }
}
