import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.FileReader;
import java.io.PrintWriter;
import java.util.StringTokenizer;

class Reader extends BufferedReader
{

    StringTokenizer st;

    public Reader()
    {
        super(new InputStreamReader(System.in));
    }

    public Reader(String fileName) throws IOException
    {
        super(new FileReader(fileName));
    }

    public void skipLine() throws IOException
    {
        String line = readLine();

        if(line == null) return;

        st = new StringTokenizer(line);
    }

    public String next() throws IOException
    {
        while(st == null || !st.hasMoreTokens())
        {
            String line = readLine();
            if(line == null) return null;
            st = new StringTokenizer(line);
        }

        return st.nextToken();
    }


    public int nextInt() throws IOException
    {
        return Integer.parseInt(next());
    }

    public double nextDouble() throws IOException
    {
        return Double.parseDouble(next());
    }
    public boolean nextBoolean() throws IOException
    {
        return Boolean.parseBoolean(next());
    }
    public long nextLong() throws IOException
    {
        return Long.parseLong(next());
    }

}

public class Task1
{
    static Reader r = new Reader();
    static PrintWriter out = new PrintWriter(System.out);

    public static void main(String[] args) throws IOException
    {
        int t = r.nextInt();

        for(int i = 0; i < t; i++)
        {
            logic();
        }

        out.flush();
    }

    static void logic() throws IOException
    {
        long requests = r.nextLong();
        long cooldown = r.nextLong();

        long reloadTime = 0;

        int smokeAvailable = 2;

        long fulfilledRequests = 0;

        long previousTimestamp = 0;

        for(long i = 0; i < requests; i++)
        {
            long timestamp = r.nextLong();

            long difference = timestamp - previousTimestamp;

            if(difference >= cooldown)
            {
                for(long j = difference; j >= 0; j -= cooldown)
                {
                    if(difference - cooldown >= 0)
                    {
                        smokeAvailable++;
                        reloadTime = Math.max(0, reloadTime - cooldown);
                    }
                    else
                    {
                        reloadTime = Math.max(0, reloadTime - difference);
                    }
                }
            }
            else
            {
                reloadTime = Math.max(0, reloadTime - difference);
            }


            if(smokeAvailable > 0)
            {
                smokeAvailable--;
                fulfilledRequests++;
                reloadTime += cooldown;
            }

            previousTimestamp = timestamp;
        }


        out.println(fulfilledRequests == requests ? "YES" : "NO");
    }

}