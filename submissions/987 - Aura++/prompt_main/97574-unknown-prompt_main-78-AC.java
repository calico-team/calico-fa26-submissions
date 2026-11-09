
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
        String S = r.next();
        String result = "";
        result += S;
        
        if(S.contains("write_me"))
        {
            result += "make_it_sound_human";
        }
        else if(S.contains("what_is"))
        {
            result += "do_not_hallucinate";
        }
        else if(S.contains("solve"))
        {
            result += "make_no_mistakes";
        }
        else 
        {
            result += "thank_you";
        }
        out.println(result);
    }

}