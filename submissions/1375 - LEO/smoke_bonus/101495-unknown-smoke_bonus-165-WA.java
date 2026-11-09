import java.io.*;
import java.util.function.IntBinaryOperator;

class Solution {

    /*
     * Output whether all of the requests can be fulfilled.
     *
     * N: Number of smoke requests
     * R: Number of seconds needed for a smoke charge to recharge
     * A: List of timestamps where smokes are requested
     */
    static String solve(int N, int R, int[] A) {
        
        int[] charges = {0,0};

        IntBinaryOperator smokeBLAST = (charge, time) -> 
            charges[charge] <= time ? (charges[charge] = time + R) * 0 + 1 : 0;

        int i = 0;

        while (i < N) {
            int used = smokeBLAST.applyAsInt(0, A[i]);
            used |= (1 - used) * smokeBLAST.applyAsInt(1, A[i]);
            if (used == 0) return "NO";
            i++;
        }

        return "YES";
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
