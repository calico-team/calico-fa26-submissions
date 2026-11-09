
import java.util.Scanner;

class answer {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int t = sc.nextInt();

        for (int i = 0; i < t; i++) {
            String s = sc.next();

            if (s.contains("write_me")) {
                s += "make_it_sound_human";
            } else if (s.contains("what_is")) {
                s += "do_not_hallucinate";
            } else if (s.contains("solve")) {
                s += "make_no_mistakes";
            } else {
                s += "thank_you";
            }

            System.out.println(s);
        }

        sc.close();
    }
}
