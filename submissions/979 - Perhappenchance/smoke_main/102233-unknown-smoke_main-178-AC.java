import java.io.*;

class smoke {

    /*
     * Output whether all of the requests can be fulfilled.
     *
     * N: Number of smoke requests
     * R: Number of seconds needed for a smoke charge to recharge
     * A: List of timestamps where smokes are requested
     */
    static String solve(int N, int R, int[] A) {
        // YOUR CODE HERE
        int max = A[A.length - 1];
        boolean yes = true;
        int count = 0;
        int index = 0;
        int smokes = 2;
        for (int t = 0; t <= max; t++){
            if (A[index] == t){
                index++;
                smokes--;
            }
            if (smokes < 2 && count >= R){
                smokes++;
                count = 0;
            }
            if (smokes < 2){
                count++;
            }
            if (smokes < 0){
                yes = false;
                System.out.println("NO");
                break;
            }
        }
        if (yes){
            System.out.println("YES");
        }

        return "";
    }

    static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    static PrintWriter out = new PrintWriter(System.out);

    public static void main(String[] args) throws IOException {
        int T = Integer.parseInt(in.readLine());

        for (int i = 0; i < T; i++) {
            String[] temp = in.readLine().split(" ");
            int N = Integer.parseInt(temp[0]);
            int R = Integer.parseInt(temp[1]);

            int[] A = new int[N];
            String[] req = in.readLine().split(" ");
            for (int j = 0; j < N; j++) {
                A[j] = Integer.parseInt(req[j]);
            }

            out.println(solve(N, R, A));
        }
        out.flush();
    }
}
