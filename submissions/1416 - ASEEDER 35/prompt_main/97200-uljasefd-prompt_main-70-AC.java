import java.util.Scanner;

public class problemOne {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        if (!sc.hasNextInt()) return;
        int T = sc.nextInt();
                sc.nextLine(); 
        
        StringBuilder sb = new StringBuilder();

        while (T > 0) {
            if (!sc.hasNextLine()) {
                break; 
                            }
            
            String s = sc.nextLine();
            
            if (s.trim().isEmpty()) {
                continue; 
            }

            if (s.contains("write_me")) {
                if (s.endsWith("_")) {
                    sb.append(s).append("make_it_sound_human\n");
                } else {
                    sb.append(s).append("_make_it_sound_human\n");
                }
            } else if (s.contains("what_is")) {
                if (s.endsWith("_")) {
                    sb.append(s).append("do_not_hallucinate\n");
                } else {
                    sb.append(s).append("_do_not_hallucinate\n");
                }
            } else if (s.contains("solve")) {
                if (s.endsWith("_")) {
                    sb.append(s).append("make_no_mistakes\n");
                } else {
                    sb.append(s).append("_make_no_mistakes\n");
                }
            } else {
                if (s.endsWith("_")) {
                    sb.append(s).append("thank_you\n");
                } else {
                    sb.append(s).append("_thank_you\n");
                }
            }
            T--; 
                    }
        
        System.out.print(sb.toString());
    }
}