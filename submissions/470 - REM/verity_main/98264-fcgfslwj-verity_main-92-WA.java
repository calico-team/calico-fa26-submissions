import java.io.*;
//import java.util.*;

class Solution {
    
    /*
     * Print a sequence of guesses until you guess the answer string.
     * You may use the readString() and printGuess() helper functions defined below.
     *
     * N: Length of the string
     * K: Number of different -ities
     * A: List containing the different -ities
     */
    static void solve(int N, int K, String[] A) throws IOException {
        char[] correct = new char[N];
        for (int i = 0; i < K; i++) {
            String guess = "";
            for (int j = 0; j < N; j++) {
                guess += A[i];
            }
            printGuess(guess);
            String answer = readString();
            for (int k = 0; k < answer.length(); k++) {
                if (answer.charAt(k) != '_') {
                    correct[k] = answer.charAt(k);
                }
            }
        }
        String a = new String(correct);
        printGuess(a);
        readString();
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
