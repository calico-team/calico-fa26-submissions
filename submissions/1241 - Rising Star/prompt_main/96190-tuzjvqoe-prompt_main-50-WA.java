import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter a prompt statement: ");
        String promptStatement = scanner.nextLine();
        if (promptStatement.length()==1) {
            System.out.println("");
        }
        else if (promptStatement.contains("write_me")) {
            promptStatement = promptStatement + "make_it_sound_human";
            System.out.println(promptStatement);
        } else if (promptStatement.contains("what_is")) {
            promptStatement = promptStatement + "do_not_hallucinate ";
            System.out.println(promptStatement);
        } else if (promptStatement.contains("solve")) {
            promptStatement = promptStatement + "make_no_mistakes ";
            System.out.println(promptStatement);
        } else {
            promptStatement = promptStatement + "thank_you";
            System.out.println(promptStatement);
        }
    }
}