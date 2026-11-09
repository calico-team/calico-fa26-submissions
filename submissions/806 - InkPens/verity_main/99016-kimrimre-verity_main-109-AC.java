import java.io.*;
import java.util.*;

class Solution {
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
        String current = "";
        for (int i = 0; i < N; i++) {
            current += A[0];
        }
        for (int z = 1; z < K + 1; z++) {
            printGuess(current);
            String input = readString();
            if (input.equals("CORRECT")) return;

            for (int i = 0; i < N; i++) {
                if (input.charAt(i) == '_') {
                    current = current.substring(0, i) + A[z] + current.substring(i + 1);
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