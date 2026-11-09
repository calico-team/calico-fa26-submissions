import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;

public class Main
{
    static String solve(String s)
    {
        if (s.contains("write_me"))
        {
            return s + "make_it_sound_human";
        }
        else if (s.contains("what_is"))
        {
            return s + "do_not_hallucinate";
        }
        else if (s.contains("solve"))
        {
            return s + "make_no_mistakes";
        }
        else
        {
            return s + "thank_you";
        }
    }

    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);

        int t = Integer.parseInt(in.readLine().trim());

        for (int i = 0; i < t; i++)
        {
            String s = in.readLine();

            String answer = solve(s);

            out.println(answer);
        }

        out.flush();
    }
}