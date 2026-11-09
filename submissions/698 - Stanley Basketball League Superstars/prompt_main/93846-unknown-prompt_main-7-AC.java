import java.util.*;

public class p1{
    static Scanner sc;
    static void solve(){
        String s = sc.nextLine();
        int N = s.length();

        String check[] = new String[]{"write_me", "what_is", "solve"};
        String ans[] = new String[]{"make_it_sound_human", "do_not_hallucinate", "make_no_mistakes"};
        for(int i = 0; i<3; ++i){
            if(s.contains(check[i])){
                System.out.println(s + ans[i]);
                return;
            }
        }

        System.out.println(s + "thank_you");
    }
    public static void main(String[] args){
        sc = new Scanner(System.in);

        int t = 1;
        t = sc.nextInt(); sc.nextLine();
        while(t-- > 0) solve();
    }
}