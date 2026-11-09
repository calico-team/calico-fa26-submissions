import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.io.IOException;
import java.util.StringTokenizer;
public class Verity {
    static class Input {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st= new StringTokenizer("");
        String next() throws IOException {
            while (!st.hasMoreTokens()) {
                String line = br.readLine();
                if (line == null) {
                    return null;
                }
                st = new StringTokenizer(line);
            }
            return st.nextToken();
        }
    }
    public static void main(String[] args) throws IOException {
        Input in= new Input();
        PrintWriter out = new PrintWriter(System.out);
        int t = Integer.parseInt(in.next());
        for (int test=0; test<t; test++) {
            int n = Integer.parseInt(in.next());
            int k= Integer.parseInt(in.next());
            char[] letters = new char[k];
            for (int i = 0; i<k; i++) {
                letters[i] = in.next().charAt(0);
            }
            char[] guess= new char[n];
            boolean[] found = new boolean[n];
            for (int turn = 0; turn<k; turn++) {
                for (int i=0; i < n; i++) {
                    if (!found[i]) {
                        guess[i]= letters[turn];
                    }
                }
                out.println(new String(guess));
                out.flush();
                String reply = in.next();
                if (reply==null) {
                    return;
                }
                if (reply.equals("CORRECT")) {
                    break;
                }
                for (int i = 0; i<n; i++) {
                    if (reply.charAt(i) != '_') {
                        found[i]=true;
                    }
                }
            }
        }
    }
}