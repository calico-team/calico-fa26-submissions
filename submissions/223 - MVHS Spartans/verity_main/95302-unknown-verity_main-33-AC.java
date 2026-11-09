import java.io.*;
import java.util.StringTokenizer;

public class Verity{
	public static void main(String[] args) throws IOException{
        Verity main = new Verity();
        main.solve();
    }

    public void solve() throws IOException{
		BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(System.out);

		StringTokenizer st = new StringTokenizer(r.readLine());
		int t = Integer.parseInt(st.nextToken());

        for(int sus = 0; sus<t; sus++){
            st = new StringTokenizer(r.readLine());
            int N = Integer.parseInt(st.nextToken());
            int K = Integer.parseInt(st.nextToken());
            String[] letters = new String[K];

            st = new StringTokenizer(r.readLine());
            for(int i = 0; i<K; i++){
                letters[i] = st.nextToken();
            }
            boolean done = false;
            String[] word = new String[N];
            for(int i = 0; i<K; i++){
                String suspect = "";
                for(int j = 0; j<N; j++){
                    suspect=suspect+letters[i];
                }
                pw.println(suspect);
                pw.flush();
                st = new StringTokenizer(r.readLine());
                String response = st.nextToken();
                if(response.equals("CORRECT")){
                    done = true;
                    break;
                }

                int curr = 0;
                for(char ch : response.toCharArray()) {
                    if(String.valueOf(ch).equals(letters[i])){
                        word[curr] = letters[i];
                    }
                    curr++;
                }
            }
            if(done == false){
                String ans = "";
                for(int i = 0; i<N; i++){
                    ans = ans+word[i];
                }
                pw.println(ans);
                pw.flush();
                st = new StringTokenizer(r.readLine());
            }
        }

		pw.close();
	}
}
