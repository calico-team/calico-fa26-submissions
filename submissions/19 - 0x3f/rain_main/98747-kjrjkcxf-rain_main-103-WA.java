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
            long k = io.nextLong();
            HashMap<Integer, ArrayList<Integer>> easts = new HashMap<>();
            HashMap<Integer, ArrayList<Integer>> norths = new HashMap<>();
            int[][] drones = new int[n][2];
            for (int i = 0; i < n; ++i)
            {
                int x = io.nextInt();
                int y = io.nextInt();
                int sumxy = x + y;
                int z = io.nextInt();
                String d = io.next();
                drones[i][0] = x;
                drones[i][1] = z;
                if (d.equals("E"))
                {
                    easts.putIfAbsent(sumxy, new ArrayList<>());
                    easts.get(sumxy).add(i);
                }
                else
                {
                    norths.putIfAbsent(sumxy, new ArrayList<>());
                    norths.get(sumxy).add(i);
                }
            }
            int ct = 0;
            for (int xy: easts.keySet())
            {
                if (norths.containsKey(xy) && easts.containsKey(xy))
                {
                    ArrayList<Integer> a = norths.get(xy);
                    ArrayList<Integer> b = easts.get(xy);
                    for (int i: a)
                    {
                        for (int j: b)
                        {
                            if (Math.abs(drones[i][0] - drones[j][0]) <= k - 1)
                            {
                                ct += 1; 
                                //io.println(i + " " + j);
                            }
                        }
                    }
                }
            }
            long out = k * n - ct;
            io.println(out);
        }

        io.close();
    }
    static int binarySearch(int a, ArrayList<Integer> arr) //we want the first element greater than a
    {
        int left = 0; 
        int right = arr.size();
        while (left + 1 < right)
        {
            if (arr.get((left + right)/2) <= a)
            {
                left = (left + right) / 2;
            }
            else
            {
                right = (left + right) / 2;
            }
        }
        if (arr.get(0) < a)
            return 0;
        return right;
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