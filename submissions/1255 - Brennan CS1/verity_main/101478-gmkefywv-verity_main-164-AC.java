import java.io.*;
import java.util.*;
public class Main {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        int T = Integer.parseInt(br.readLine());
        while (T-- > 0) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int N = Integer.parseInt(st.nextToken());
            int K = Integer.parseInt(st.nextToken());
            st = new StringTokenizer(br.readLine());
            char[] letters = new char[K];
            for (int i = 0; i < K; i++){
                letters[i] = st.nextToken().charAt(0);}
            char[] ans = new char[N];
            Arrays.fill(ans, '?');
            for (int c = 0; c < K; c++) {
                StringBuilder guess = new StringBuilder();
                for (int i = 0; i < N; i++) {
                    if (ans[i] == '?')
                        guess.append(letters[c]);
                    else
                        guess.append(ans[i]);
                }
                bw.write(guess.toString());
                bw.newLine();
                bw.flush();
                String res = br.readLine();
                if (res.equals("CORRECT"))
                    break;

                for (int i = 0; i < N; i++) {
                    if (res.charAt(i) != '_')
                        ans[i] = res.charAt(i);
                }
            }
        }
        bw.close();
        br.close();
    }
}