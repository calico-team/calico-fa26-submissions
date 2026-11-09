import java.util.Scanner;

public class p1 {

    static String append(String original, String toAdd) {
        return original + toAdd;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int trials = scanner.nextInt();
        scanner.nextLine();
        for(int i = 0; i < trials; i++) {
          String line = scanner.nextLine();
          if(line.contains("write_me")) {
            System.out.println(append(line, "make_it_sound_human"));
          }
          else if (line.contains("what_is")) {
            System.out.println(append(line, "do_not_hallucinate"));
          }
          else if (line.contains("solve")) {
            System.out.println(append(line, "make_no_mistakes"));
          }
          else System.out.println(append(line, "thank_you"));
        }
        

        scanner.close();
    }
}
