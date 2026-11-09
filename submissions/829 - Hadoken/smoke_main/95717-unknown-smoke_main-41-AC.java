import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        StreamTokenizer tok = new StreamTokenizer(new BufferedReader(new InputStreamReader(System.in)));
        if (tok.nextToken() == StreamTokenizer.TT_EOF) return;

        int T = (int) tok.nval;
        StringBuilder sb = new StringBuilder();

        while (T-- > 0) {
            tok.nextToken();
            int n = (int) tok.nval;
            tok.nextToken();
            long r = (long) tok.nval;

            int charges = 2;
            long next = Long.MAX_VALUE;
            boolean ok = true;

            for (int i = 0; i < n; i++) {
                tok.nextToken();
                long t = (long) tok.nval;

                if (!ok) continue;

                while (charges < 2 && next <= t) {
                    charges++;
                    next = (charges < 2) ? next + r : Long.MAX_VALUE;
                }

                if (charges == 0) {
                    ok = false;
                } else {
                    if (charges == 2) next = t + r;
                    charges--;
                }
            }
            sb.append(ok ? "YES\n" : "NO\n");
        }
        System.out.print(sb);
    }
}