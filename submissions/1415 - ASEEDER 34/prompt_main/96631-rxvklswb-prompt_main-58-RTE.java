
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int times = scanner.nextInt();

        for (int i = times; i > 0; i--) {
            String S = scanner.nextLine();
            if (isW(S)) {
                if (isR(S )) {
                    System.out.println(S + "make_it_sound_human");
                }else{
                    System.out.println(S + "do_not_hallucinate");
                }

            } else if (isS(S)) {

                System.out.println(S + "make_no_mistakes");

            } else {
                System.out.println(S + "thank_you");
            }
        }
    }


    public static boolean isW(String S) {
        for (int i = 0; i <= S.length(); i++) {
            if (S.charAt(i) == 'w') {
                return true;
            }
        }
        return false;
    }

    public static boolean isS(String S) {
        for (int i = 0; i <= S.length(); i++) {
            if (S.charAt(i) == 's') {
                return true;
            }
        }
        return false;
    }

    public static boolean isR(String S) {
        for (int i = 0; i <= S.length(); i++) {
            if (S.charAt(i) == 'w') {
                if(S.substring(i,i+1).equals("r")){
                    return true;
                }
            }
        }
        return false;
    }
}




