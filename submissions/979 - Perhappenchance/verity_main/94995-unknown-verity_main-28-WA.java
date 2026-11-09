import java.io.*;

class SolutionVerity {
    
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
        String[] letters = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
        String letter;
        String guess;
        String response;
        String solution = "";
        for (int i = 0; i < N; i++) {
            solution += "_";
        }
        for (int i = 0; i < letters.length; i++){
            letter = letters[i];
            guess = "";
            for (int j = 0; j < N; j++){
                guess += letter;
            }
            printGuess(guess);
            response = readString();
            if (response.contains(letter)){
                for (int j = 0; j < response.length(); j++){
                    if (response.substring(j, j + 1).equals(letter)){
                        if (j == 0){
                            solution = letter + solution.substring(j + 1);
                        } else {
                            solution = solution.substring(0, j) + letter + solution.substring(j + 1);
                        }
                        printGuess(solution);
                        break;
                    }
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
