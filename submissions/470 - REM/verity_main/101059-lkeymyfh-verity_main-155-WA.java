import java.io.*;
//import java.util.*;
import java.util.Arrays;

class Verity {
    
    /*
     * Print a sequence of guesses until you guess the answer string.
     * You may use the readString() and printGuess() helper functions defined below.
     *
     * N: Length of the string
     * K: Number of different -ities
     * A: List containing the different -ities
     */
    static void solve(int N, int K, String[] A) throws IOException {
        String[] format = new String[N];
        String response = "";
        int toTest = 0;
        while(!response.equals("CORRECT")) {
            String[] out = Arrays.copyOf(format, N);
            String curr = A[toTest];
            for (int i = 0; i < N; i++) {
                if(format[i] == null || format[i].equals("_")) {
                    out[i] = curr;
                }
            }
            printGuess(String.join("",out));
            response = readString();
            if(response.equals("CORRECT")) break;
            format = response.split("");
            toTest++;
        }
        System.out.println("dn");
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
