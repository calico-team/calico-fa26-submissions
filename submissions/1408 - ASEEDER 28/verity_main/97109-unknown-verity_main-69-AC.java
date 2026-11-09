import java.io.*;
import java.util.*;

class Solution {

   
    static void solve(int N, int K, String[] A) throws IOException {
        char[] known = new char[N];
        Arrays.fill(known, '_');
        int filled = 0;

        for (String a : A) {
            char c = a.charAt(0);
            StringBuilder sb = new StringBuilder(N);
            for (int i = 0; i < N; i++) {
                sb.append(c);
            }
            printGuess(sb.toString());
            String resp = readString();
            if (resp.equals("CORRECT")) {
                return;
            }
            for (int i = 0; i < N; i++) {
                if (resp.charAt(i) != '_' && known[i] == '_') {
                    known[i] = resp.charAt(i);
                    filled++;
                }
            }
            if (filled == N) {
                break;
            }
        }

        printGuess(new String(known));
        readString(); // CORRECT
    }

    /*
     * Reads a single string from standard input.
     */
    static String readString() throws IOException {
        return in.readLine();
    }

    /*
     * Prints a guess to standard output. The PrintWriter will automatically flush the output stream buffer.
     */
    static void printGuess(String guess) {
        out.println(guess);
    }


    static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    static PrintWriter out = new PrintWriter(System.out, true);

    public static void main(String[] args) throws IOException {
        int T = Integer.parseInt(in.readLine());

        for (int i = 0; i < T; i++) {
            String[] temp = in.readLine().split(" ");
            int N = Integer.parseInt(temp[0]);
            int K = Integer.parseInt(temp[1]);

            String[] A = in.readLine().split(" ");

            solve(N, K, A);
        }
    }
}
