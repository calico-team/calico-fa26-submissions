import java.io.*;
import java.util.StringTokenizer;

public class PromptDraft{
	public static void main(String[] args) throws IOException{
        PromptDraft main = new PromptDraft();
        main.solve();
    }

    public void solve() throws IOException{
		BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(System.out);

		StringTokenizer st = new StringTokenizer(r.readLine());
		int t = Integer.parseInt(st.nextToken());

        for(int sus = 0; sus<t; sus++){
            st = new StringTokenizer(r.readLine());
            String str = st.nextToken();
            boolean check1 = str.contains("write_me");
            boolean check2 = str.contains("what_is");
            boolean check3 = str.contains("solve");

            if(check1){
                pw.println(str+"make_it_sound_human");
            }else if(check2){
                pw.println(str+"do_not_hallucinate");
            }else if(check3){
                pw.println(str+"make_no_mistakes");
            }else{
                pw.println(str+"thank_you");
            }
        }

		pw.close();
	}
}
