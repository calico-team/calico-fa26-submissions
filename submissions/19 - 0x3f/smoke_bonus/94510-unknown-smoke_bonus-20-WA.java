import java.util.*;
import java.io.*;

public class Main
{
    public static void main(String[] args) {
        Kattio io = new Kattio();
        int T = io.nextInt();
        while (T-- > 0)
        {
            int n = io.nextInt();
            int r = io.nextInt();
            int[] as = new int[n];
            Arrays.sort(as);
            for (int i = 0; i < n; ++i)
            {
                as[i] = io.nextInt();
            }
            int c1 = -r;
            int c2 = -r;
            boolean possible = true;
            for (int t: as)
            {
                if (c1 + r < t)
                {
                    c1 = t;
                }
                else if (c2 + r < t)
                {
                    c2 = c1 + r;
                }
                else
                {
                    possible = false;
                }

            }
            io.println((possible ? "YES":"NO"));

        }
        io.close();
    }

    static class Kattio extends PrintWriter {
        private BufferedReader r;
        private StringTokenizer st;

        public Kattio() {
            this(System.in, System.out); 
        }

        public Kattio(InputStream i, OutputStream o) {
            super(o);
            r = new BufferedReader(new InputStreamReader(i));
        }

        public String next() {
            try {
                while (st == null || !st.hasMoreTokens())
                    st = new StringTokenizer(r.readLine());
                return st.nextToken();
            } catch (Exception e) {}
            return null;
        }
        
        public int nextInt() { return Integer.parseInt(next()); }
        public long nextLong() { return Long.parseLong(next()); }
    }


}