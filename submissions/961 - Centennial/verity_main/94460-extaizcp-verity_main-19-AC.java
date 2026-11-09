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
    static void solve(int n, int k, String[] A) throws IOException {
        // YOUR CODE HERE
        String[] letters = new String[n];
        for (int i = 0; i < k; i++) {
            String a = "";
            for (int j = 0; j < n; j++) {
                if(letters[j] == null){
                    a+=A[i];
                } else{
                    a+=letters[j];
                }
            }
            printGuess(a);
            String ans = readString();
            if(ans.equals("CORRECT")){
                break;
            }
            String[] res = ans.split("");
            for (int j = 0; j < n; j++) {
                if (!res[j].equals("_")){
                    letters[j]=res[j];
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
