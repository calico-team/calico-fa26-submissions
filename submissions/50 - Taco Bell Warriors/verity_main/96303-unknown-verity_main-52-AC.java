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
    static void solve(int N, int K, String[] A) throws IOException {
        char sol[] = new char[N];
        for(int i = 0; i < A.length; i++){
            StringBuilder sb = new StringBuilder();
            while(sb.length()<N){
                sb.append(A[i]);
            }
            String guess = sb.substring(0, N);
            printGuess(guess);
            String returned = readString();
            if(!returned.contains("_")) return;
            for(int j = 0; j < returned.length(); j++){
                if(returned.charAt(j) != '_'){
                    sol[j] = returned.charAt(j);
                }
            }
        }
        String ans = new String(sol);
        printGuess(ans);
        readString();
    }

    static String readString() throws IOException {
        return in.readLine();
    }

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
