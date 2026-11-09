import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(
            new InputStreamReader(System.in)
        );

        int t = Integer.parseInt(br.readLine());
        StringBuilder ans = new StringBuilder();

        while (t-- > 0) {
            String s = br.readLine();

            if (s.contains("write_me")) {
                ans.append(s).append("make_it_sound_human");
            } 
            else if (s.contains("what_is")) {
                ans.append(s).append("do_not_hallucinate");
            } 
            else if (s.contains("solve")) {
                ans.append(s).append("make_no_mistakes");
            } 
            else {
                ans.append(s).append("thank_you");
            }

            ans.append('\n');
        }

        System.out.print(ans);
    }
}