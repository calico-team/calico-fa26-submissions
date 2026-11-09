import java.util.Scanner;
public class one {
    public static void main(String[] args) {
       Scanner a= new Scanner(System.in);
       System.out.println("input?");
       a.nextInt();
       while (a.hasNextLine()){
            String input = a.nextLine();
            StringBuilder s= new StringBuilder(input);
            if(input.contains("write_me")){
                s.append("make_it_sound_human");
            }else if(input.contains("what_is")){
                s.append("do_not_hallucinate");
            }else if(input.contains("solve")){
                s.append("make_no_mistakes ");
            }else{
                s.append("thank_you");
            }
            System.out.println(s);
       }
       a.close();
       
    }
}