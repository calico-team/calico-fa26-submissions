import java.io.*;

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        int N = Integer.parseInt(br.readLine());

        for(int i = 0; i < N; i++){
            String S = br.readLine();

            if(S.contains("write_me"))
            {
                S += "make_it_sound_human";
            }
            else if(S.contains("what_is"))
            {
                S += "do_not_hallucinate";
            }
            else if(S.contains("solve"))
            {
                S += "make_no_mistakes";
            }
            else{
                S += "thank_you";
            }
            bw.write(S + "\n");
        }
        br.close();
        bw.close();
    }
}