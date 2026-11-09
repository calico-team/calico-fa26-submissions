import java.io.*;
import java.util.Map;

class Solution {

    /**
     * Output the result of adding a certain string to the end of a prompt.
     *
     * @param S Original prompt
     * @return Result of adding the certain string to the end of the prompt
     */
    public static String solve(String S) {
        Map<String, String> mpp = Map.of("write_me", "make_it_sound_human", "what_is", "do_not_hallucinate", "solve",
                "make_no_mistakes");
        String defaultStr = "thank_you";

        for (Map.Entry<String, String> entry : mpp.entrySet()) {
            if (S.contains(entry.getKey())) {
                return S + entry.getValue();
            }
        }

        return S + defaultStr;
    }

    static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

    public static void main(String[] args) throws IOException {
        int T = Integer.parseInt(in.readLine());


        for (int t = 0; t < T; t++) {
            String prompt = in.readLine();

            String result = solve(prompt);
            out.println(result);
        }
        out.flush();
    }
}