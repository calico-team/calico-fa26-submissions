import java.util.*;
import java.io.*;

public class Main
{
    public static void main(String[] args) {
        Kattio io = new Kattio();
        int T = io.nextInt();
        while (T-- > 0)
        {
            String s = io.next();
            if (s.contains("write_me"))
            {
                io.println(s + "make_it_sound_human");
            }
            else if (s.contains("what_is"))
            {
                io.println(s + "do_not_hallucinate");
            }
            else if (s.contains("solve"))
            {
                io.println(s + "make_no_mistakes");
            }
            else
            {
                io.println(s + "thank_you");
            }
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