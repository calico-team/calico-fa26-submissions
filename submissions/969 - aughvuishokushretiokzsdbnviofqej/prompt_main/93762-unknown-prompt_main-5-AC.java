import java.io.*;
import java.util.*;

class Main {
    public static void main(String[] args) throws IOException {
        Scanner s = new Scanner(System.in);
        int T = s.nextInt();
        s.nextLine();

        for (int i = 0; i < T; i++) {
            String A = s.nextLine();
            if (A.contains("write_me")) {
                A = A + "make_it_sound_human";
            }
            else if (A.contains("what_is")) {
                A = A + "do_not_hallucinate";
            }
            else if (A.contains("solve")) {
                A = A + "make_no_mistakes";
            }
            else {
                A = A + "thank_you";
            }
            System.out.println(A);
        }
    }
}
