import java.util.Scanner;
public class p1{ 
    public static void main(String[] args){
        Scanner in = new Scanner(System.in);

        int t = in.nextInt();
        in.nextLine();

        while(t-- != 0){
            String s = in.nextLine();

            if(s.indexOf("write_me") != -1){
                s += "make_it_sound_human";
            } else if(s.indexOf("what_is") != -1){
                s += "do_not_hallucinate";
            } else if(s.indexOf("solve") != -1){
                s += "make_no_mistakes";
            } else { 
                s += "thank_you";
            }
            System.out.println(s);
        }
        in.close();
    }
}