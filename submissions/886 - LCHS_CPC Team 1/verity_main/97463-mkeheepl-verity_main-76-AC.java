import java.io.*;
import java.util.*;

class Solution {
    /*
     * Print a sequence of guesses until you guess the answer string.
     *
     * N: Length of the string
     * K: Number of different "-ities" (Characters)
     * A: List containing the different allowed characters
     */
    static void solve(int N, int K, String[] A) throws IOException {
        char[] arr = new char[N];
        Arrays.fill(arr, '_');

        for (int i = 0; i < K - 1; i++) {
            StringBuilder jadenChong = new StringBuilder();
            for (int j = 0; j < N; j++) {
                jadenChong.append(A[i]);
            }
            
            printGuess(jadenChong.toString());
            String response = readString();
            
            if ("CORRECT".equals(response)) {
                return;
            }
            
            for (int t = 0; t < N; t++) {
                if (response.charAt(t) != '_') {
                    arr[t] = response.charAt(t);
                }
            }
        }

        char lastChar = A[K - 1].charAt(0);
        for (int p = 0; p < N; p++) {
            if (arr[p] == '_') {
                arr[p] = lastChar;
            }
        }
        
        printGuess(new String(arr));
        readString();
    }

    /*
     * Reads a single string from standard input.
     */
    static String readString() throws IOException {
        return in.readLine();
    }

    /*
     * Prints a guess to standard output. The PrintWriter will automatically flush.
     */
    static void printGuess(String guess) {
        out.println(guess);
    }

    static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    static PrintWriter out = new PrintWriter(System.out, true);

    public static void main(String[] args) throws IOException {
        String line = in.readLine();
        if (line == null || line.trim().isEmpty()) return;
        
        int T = Integer.parseInt(line.trim());
        for (int i = 0; i < T; i++) {
            String[] temp = in.readLine().split(" ");
            int N = Integer.parseInt(temp[0]);
            int K = Integer.parseInt(temp[1]);
            String[] A = in.readLine().split(" ");
            solve(N, K, A);
        }
    }
}