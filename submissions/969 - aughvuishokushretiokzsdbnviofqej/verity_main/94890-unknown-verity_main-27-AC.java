import java.io.*;
import java.util.*;

class Main {

    /*
     * Print a sequence of guesses until you guess the answer string.
     * You may use the readString() and printGuess() helper functions defined below.
     *
     * N: Length of the string
     * K: Number of different -ities
     * A: List containing the different -ities
     */
    static void solve(int N, int K, String[] A) throws IOException {
        String guess = "";
        for (int i = 0; i < N; i++) {
            guess = guess + A[0];
        }

        ArrayList<Integer> correct = new ArrayList<Integer>();
        for (int i = 0; i < K; i++) {
            for (int j = 0; j < N; j++) {
                if (!correct.contains(j)) {
                    guess = guess.substring(0, j) + A[i] + guess.substring(j + 1);
                }
            }

            printGuess(guess);
            String response = readString();
            if (response.equals("CORRECT")) {
                break;
            }
            for (int j = 0; j < N; j++) {
                if (response.charAt(j) != '_' && !correct.contains(j)) {
                    correct.add(j);
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