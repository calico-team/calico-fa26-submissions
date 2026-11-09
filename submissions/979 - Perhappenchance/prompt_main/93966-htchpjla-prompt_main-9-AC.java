import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.InputStreamReader;
import java.io.FileReader;
import java.util.*;

public class Prompt
{
    public static void main(String[] args) throws IOException
    {
        PrintWriter out = new PrintWriter(System.out);
        //out.println();

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int cases = Integer.parseInt(br.readLine());
        for (int i = 0; i < cases; i++) {
            String line = "";
            line = br.readLine();

            //do stuff
            if (line.contains("write_me")){
                out.println(line + "make_it_sound_human");
            } else if (line.contains("what_is")){
                out.println(line + "do_not_hallucinate");
            } else if (line.contains("solve")){
                out.println(line + "make_no_mistakes");
            } else {
                out.println(line + "thank_you");
            }
        }
        out.flush();
    }
}