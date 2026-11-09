import java.util.Scanner;
public class Main {
    public static void main(String [] args) {
        Scanner sc = new Scanner(System.in);
        int x = sc.nextInt();
        sc.nextLine();
        for(int i = 0;x > i;i++){
            String str = sc.nextLine();
            String result;
            if(str.contains("write_me")){
                result = str + "make_it_sound_human";
            }
            else if(str.contains("what_is")){
                result = str + "do_not_hallucinate";
            }
            else if(str.contains("solve")){
                result = str + "make_no_mistakes";
            }
            else{
                result = str + "thank_you";
            }
            System.out.println(result);
        }
        sc.close();
    }
}
