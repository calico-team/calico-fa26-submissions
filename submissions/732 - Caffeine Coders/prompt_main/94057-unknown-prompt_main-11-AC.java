import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;

public class Main{
    static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    static PrintWriter out = new PrintWriter(System.out);
    public static void main(String[] args) throws IOException{
        int j = Integer.parseInt(in.readLine());
        for (int i = 0; i < j; i++) {
            String s = in.readLine(); 
            out.println(modify(s)); 
            out.flush();
        }
    }

    private static String modify(String s) {
        if(s.contains("write_me")){
            s+= "make_it_sound_human";
        } else if (s.contains("what_is")){
            s+= "do_not_hallucinate";
        } else if (s.contains("solve")){
            s+= "make_no_mistakes";
        } else {
            s+= "thank_you";
        }
        return s;
    }
}