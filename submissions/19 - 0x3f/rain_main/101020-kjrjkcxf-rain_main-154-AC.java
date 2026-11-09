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
            int[] drones = new int[n];
            for (int i = 0; i < n; ++i)
            {
                int x = io.nextInt();
                int y = io.nextInt();
                int sumxy = x + y;
                int z = io.nextInt();
                String d = io.next();
                drones[i] = x;
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
            long ct = 0;
            for (int xy: easts.keySet())
            {
                if (norths.containsKey(xy) && easts.containsKey(xy))
                {
                    ArrayList<Integer> a = norths.get(xy);
                    ArrayList<Integer> b = easts.get(xy);
                    a.sort((x, y) -> Integer.compare(drones[x], drones[y]));
                    b.sort((x, y) -> Integer.compare(drones[x], drones[y]));
                    int i1 = 0;
                    int i2 = 0;
                    for (int i: a)
                    {
                        while (i1 < b.size() && drones[b.get(i1)] < drones[i] - (k - 1))
                        {
                            ++i1;
                        }
                        while (i2 < b.size() && drones[b.get(i2)] < drones[i])
                        {
                            ++i2;
                        }
                        ct += i2 - i1;
                    }
                }
            }
            long out = k * n - ct;
            io.println(out);
        }

        io.close();
    }
    /*static int binarySearch(int a, ArrayList<Integer> arr) //we want the first element greater than a
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
    }*/

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