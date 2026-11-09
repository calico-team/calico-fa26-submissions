import java.io.*;

class Solution {

    /**
    * Output the result of adding a certain string to the end of a prompt.
    *
    * @param S Original prompt
    * @return Result of adding the certain string to the end of the prompt
     * You are given a string S which is a prompt to an SI. Depending on what substring is in the prompt
     * S, modify the prompt as follows:
     *
     * • If the prompt contains the substring write_me, append make_it_sound_human to the end.
     *
     * • If the prompt contains the substring what_is, append do_not_hallucinate to the end.
     *
     * • If the prompt contains the substring solve, append make_no_mistakes to the end.
     *
     * • Otherwise, append thank_you to the end.
     *
     * Output the modified prompt, including the original string with the correct words appended to the
     * end. The input string will contain at most one of the three substrings. Do not add extra spaces
     * or punctuation to your answer. All characters are lowercase letters, digits, or underscores.
    */
	public static String solve(String S){
        if(S.contains("write_me")){
            return S + "make_it_sound_human";
        }
        else if(S.contains("what_is")){
            return S + "do_not_hallucinate";
        }
        else if(S.contains("solve")){
            return S + "make_no_mistakes";
        }
        else {
            return S + "thank_you";
        }
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