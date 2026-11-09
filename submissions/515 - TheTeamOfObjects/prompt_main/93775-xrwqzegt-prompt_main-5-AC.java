
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;

public class prob1 {
    public static void main(String[] args) throws Exception{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);
        int testcases = Integer.parseInt(br.readLine());
        for (int i = 0; i < testcases; i++) {
            String test = br.readLine();
            if (test.contains("write_me")) {
                test += "make_it_sound_human";
            } else if (test.contains("what_is")) {
                test += "do_not_hallucinate";
            } else if (test.contains("solve")) {
                test += "make_no_mistakes";
            } else {
                test += "thank_you";
            }
            pw.println(test);
        }
        pw.flush();
    }
}
