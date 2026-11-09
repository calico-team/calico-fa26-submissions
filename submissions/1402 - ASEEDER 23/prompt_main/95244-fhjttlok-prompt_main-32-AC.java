import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int t = scanner.nextInt();
        for (int i = 0; i < t; i++) {
            String s = scanner.next();
            String suffix;
            if (s.contains("write_me")) {
                suffix = "make_it_sound_human";
            } else if (s.contains("what_is")) {
                suffix = "do_not_hallucinate";
            } else if (s.contains("solve")) {
                suffix = "make_no_mistakes";
            } else {
                suffix = "thank_you";
            }
            System.out.println(s + suffix);
        }
        scanner.close();
    }
}
