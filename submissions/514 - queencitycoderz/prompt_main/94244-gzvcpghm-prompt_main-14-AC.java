import java.util.*;

class Solution {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int T = in.nextInt();
        while (T-- > 0) {
            String S = in.next();
            if (S.contains("write_me")) S += "make_it_sound_human";
            else if (S.contains("what_is")) S += "do_not_hallucinate";
            else if (S.contains("solve")) S += "make_no_mistakes";
            else S += "thank_you";
            System.out.println(S);
        }
    }
}