import java.io.PrintWriter;
import java.util.Scanner;

class Solution {
    public static void main(String[] args) {
        PrintWriter out = new PrintWriter(System.out, true);
        Scanner input = new Scanner(System.in);
        String prompt = input.nextLine();
        int t = Integer.parseInt(prompt);
        prompt = input.nextLine();
        String result = "";
        for (int i = 0; i < t; i++) {
            result += prompt;
            if (prompt.contains("write_me")) {
                result += "make_it_sound_human";
            }
            if (prompt.contains("what_is")) {
                result += "do_not_hallucinate";
            }
            if (prompt.contains("solve")) {
                result += "make_no_mistakes";
            } else if (!prompt.contains("write_me") && !prompt.contains("what_is")) {
                result += "thank_you";
            }
            result += "\n";
            prompt = input.nextLine();
        }
        out.println(result);
        out.flush();
    }
}
