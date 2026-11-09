import java.io.*;
import java.util.*;

class Solution {
    
    /*
     * Print a sequence of guesses until you guess the answer string.
     * You may use the readString() and printGuess() helper functions defined below.
     *
     * N: Length of the string
     * K: Number of different -ities
     * A: List containing the different -ities
     */
    static void solve(int N, int K, String[] A) throws IOException 
    {
        // YOUR CODE HERE
        boolean[] correct = new boolean[N];
        String[] correctLetters = new String[N];
        int[] index = new int[N];
        for (;;)
        {
            String guess = "";
            for (int i = 0; i < N; i ++)
                if (correct[i])
                    guess += correctLetters[i];
                else
                    guess += A[index[i]];

            printGuess(guess);
            String reply = readString();

            if (reply.equals("CORRECT"))
                return;
            for (int i = 0; i < N; i++)
                if (!reply.substring(i , i+1).equals("_"))
                {
                    correct[i] = true;
                    correctLetters[i] = reply.substring(i, i+1);
                }
                else 
                    index[i] ++;
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