
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int times = scanner.nextInt();

        while(times>0) {
            String S = scanner.nextLine();
            if (isW(S)) {
                if (isWrite(S)) {
                    System.out.println(S + "make_it_sound_human");
                } else if (isWhat(S)){
                    System.out.println(S + "do_not_hallucinate");
                }

            } else if (isSolve(S)) {

                System.out.println(S + "make_no_mistakes");

            } else {
                System.out.println(S + "thank_you");
            }
            times--;
        }
    }


    public static boolean isW(String S) {
        for (int i = 0; i < S.length(); i++) {
            if (S.charAt(i) == 'w') {
                return true;
            }
        }
        return false;
    }

    public static boolean isSolve(String S) {
        for (int i = 0; i < S.length(); i++) {
            if (S.charAt(i) == 's') {
                if (S.substring(i, i + 5).equals("solve")) {
                    return true;
                }
            }

        }
        return false;
    }

    public static boolean isWrite(String S) {
        for (int i = 0; i < S.length(); i++) {
            if (S.charAt(i) == 'w') {
                if(S.substring(i,i+5).equals("write")){
                    return true;
                }
            }
        }
        return false;
    }
    public static boolean isWhat(String S) {
        for (int i = 0; i < S.length(); i++) {
            if (S.charAt(i) == 'w') {
                if(S.substring(i,i+4).equals("what")){
                    return true;
                }
            }
        }
        return false;
    }

}




