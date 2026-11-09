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
    
public class MyProgram
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
        int numOfDrones = r.nextInt();
        int days = r.nextInt();
        int xCord = 0;
        int yCord = 0;
        int zCord = 0;
        int[] cords = {xCord, yCord, zCord};
        int result = 0;
        
        for(int i=0; i<days; i++)
        {
            for(int j=0; j<numOfDrones; j++)
            {
                xCord = r.nextInt();
                yCord = r.nextInt();
                zCord = r.nextInt();
                String D = r.next();
                if(D.contains("E"))
                {
                    cords[0] = xCord;
                    cords[1] = yCord;
                    cords[2] = zCord;
                    xCord++;
                    int[] newCord = {xCord, yCord, zCord};
                    for(int q = 0; q < cords.length; q++)
                    {
                        if(cords[0] == newCord[0] && cords[1] == newCord[1])
                        {
                            result += 0;
                        }
                        else
                        {
                            result++;
                        }
                    }
                }
                else if(D.contains("N"))
                {
                    cords[0] = xCord;
                    cords[1] = yCord;
                    cords[2] = zCord;
                    yCord++;
                    int[] newCord = {xCord, yCord, zCord};
                    for(int q = 0; q < cords.length; q++)
                    {
                        if(cords[0] == newCord[0] && cords[1] == newCord[1])
                        {
                            result += 0;
                        }
                        else
                        {
                            result++;
                        }
                    }
                }
            }
        }

        out.println(result);
    }
}