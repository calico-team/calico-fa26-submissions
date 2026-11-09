import java.io.*;

public class prompt_draft_main {

	 static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
     static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

    public static void main(String[] args) throws IOException{ 
        int T = Integer.parseInt(in.readLine());


        for (int t = 0; t < T; t++) {
            String prompt = in.readLine();

            String result = solve(prompt);
            out.println(result);
        }
        out.flush();
    }
    public static String solve(String S){
     
        //Scanner scanner = new Scanner(System.in);
        String promptStatement = S;
        if (promptStatement == null || promptStatement.isEmpty() || promptStatement.length() == 1) {
            promptStatement = "";
        }
        else if (promptStatement.contains("write_me")) {
            promptStatement = promptStatement + "make_it_sound_human";
            //System.out.println(promptStatement);
        } else if (promptStatement.contains("what_is")) {
            promptStatement = promptStatement + "do_not_hallucinate ";
            //System.out.println(promptStatement);
        } else if (promptStatement.contains("solve")) {
            promptStatement = promptStatement + "make_no_mistakes ";
            //System.out.println(promptStatement);
        } else {
            promptStatement = promptStatement + "thank_you";
            //System.out.println(promptStatement);
        }
        return promptStatement;
    }
}