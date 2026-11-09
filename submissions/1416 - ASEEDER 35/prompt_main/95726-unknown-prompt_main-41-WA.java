import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        if (!sc.hasNextInt()) return;
        int T = sc.nextInt();
        
        StringBuilder sb = new StringBuilder();

        while (T-- > 0) {
            String s = sc.next();

            if (s.contains("write_me")) {
                sb.append(s).append("_make_it_sound_human\n");
            } else if (s.contains("what_is")) {
                sb.append(s).append("_do_not_hallucinate\n");
            } else if (s.contains("solve")) {
                sb.append(s).append("_make_no_mistakes\n");
            } else {
                sb.append(s).append("_thank_you\n");
            }
        }
        
        System.out.print(sb.toString());
    }
}