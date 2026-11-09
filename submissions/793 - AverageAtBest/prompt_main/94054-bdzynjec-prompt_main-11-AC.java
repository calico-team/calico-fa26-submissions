import java.io.*;

class Solution {

    /**
    * Output the result of adding a certain string to the end of a prompt.
    *
    * @param S Original prompt
    * @return Result of adding the certain string to the end of the prompt
    */
	public static String solve(String S){
		if(S.indexOf("write_me")!=-1)
        	return S+"make_it_sound_human";
        else if(S.indexOf("what_is")!=-1)
        	return S+"do_not_hallucinate";
        else if(S.indexOf("solve")!=-1)
        	return S+"make_no_mistakes";
        else
        	return S+"thank_you";
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