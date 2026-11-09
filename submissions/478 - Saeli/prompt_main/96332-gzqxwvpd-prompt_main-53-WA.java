import java.io.*;

class Solution {

    /**
    * Output the result of adding a certain string to the end of a prompt.
    *
    * @param S Original prompt
    * @return Result of adding the certain string to the end of the prompt
    */
	public static String solve(String S){
        String newPrompt = S;
        String[] words = newPrompt.split("_");
        for (int i = 0; i < words.length - 1; i++) {
            if (words[i].equals("write") && words[i+1].equals("me")){
                return newPrompt + "make_it_sound_human";
            } else if (words[i].equals("what") && words[i+1].equals("is")){
                return newPrompt + "do_not_hallucinate";
            } else if (words[i].equals("solve") || (i == words.length-2 && words[i+1].equals("solve"))){
                return newPrompt + "make_no_mistakes";
            }
        }
        return newPrompt + "thank_you";
    }

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
}