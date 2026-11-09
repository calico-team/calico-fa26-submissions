import java.io.*;

public class Solution {
    public static void main(String[] args) throws IOException {
        StreamTokenizer in = new StreamTokenizer(new BufferedReader(new InputStreamReader(System.in)));
        StringBuilder sb = new StringBuilder();
        in.nextToken();
        int t = (int) in.nval;

        while (t-- > 0) {
            in.nextToken();
            int n = (int) in.nval;
            in.nextToken();
            long r = (long) in.nval;

            int charges = 2;
            long ready = 0;
            boolean ok = true;

            for (int i = 0; i < n; i++) {
                in.nextToken();
                long a = (long) in.nval;

                while (charges < 2 && ready <= a) {
                    charges++;
                    ready += r;
                }

                if (charges == 0) {
                    ok = false;
                } else {
                    if (charges == 2) {
                        ready = a + r;
                    }
                    charges--;
                }
            }

            sb.append(ok ? "YES" : "NO").append("\n");
        }
        System.out.print(sb);
    }
}