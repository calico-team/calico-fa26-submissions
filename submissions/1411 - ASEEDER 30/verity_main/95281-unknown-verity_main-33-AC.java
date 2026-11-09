import java.io.*;
import java.util.*;

public class Verity {
    static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    static PrintWriter out = new PrintWriter(System.out, true);

    /*
     * Print a sequence of guesses until you guess the answer string.
     * You may use the readString() and printGuess() helper functions defined below.
     *
     * N: Length of the string
     * K: Number of different -ities
     * A: List containing the different -ities
     */
    static void solve(int N, int K, String[] A) throws IOException {
        // YOUR CODE HERE
        char[] answer = new char[N];
        Arrays.fill(answer, '_');

        for (int i = 0; i < K; i++) {
            char[] guess = answer.clone();
            for (int j = 0; j < N; j++) {
                if (guess[j] == '_') {
                    guess[j] = A[i].charAt(0);
                }
            }
            printGuess(new String(guess));

            String reply = readString();
            if (reply == null || reply.equals("CORRECT")) {
                return;
            }
            for (int j = 0; j < N; j++) {
                if (reply.charAt(j) != '_') {
                    answer[j] = reply.charAt(j);
                }
            }
        }
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

    public static void main(String[] args) throws IOException {
        int T = Integer.parseInt(in.readLine().trim());

        for (int i = 0; i < T; i++) {
            String[] temp = in.readLine().trim().split("\\s+");
            int N = Integer.parseInt(temp[0]);
            int K = Integer.parseInt(temp[1]);
            String[] A = in.readLine().trim().split("\\s+");
            solve(N, K, A);
        }
    }
}
