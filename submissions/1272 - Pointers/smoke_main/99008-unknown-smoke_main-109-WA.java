import java.io.*;

class Solution {

    /*
     * Output whether all of the requests can be fulfilled.
     *
     * N: Number of smoke requests
     * R: Number of seconds needed for a smoke charge to recharge
     * A: List of timestamps where smokes are requested
     */
    static String solve(int N, int R, int[] A) {
        int num = 2;
        int[] recharge = {0, 0};
        for (int i = 0; i < A.length - 1; i++) {
            num--;
            if (recharge[0] != 0 && recharge[0] < A[i] && num < 2) {
                num++;
                recharge[0] = 0;
            }
            if (recharge[1] != 0 && recharge[1] < A[i] && num < 2){
                num++;
                recharge[1] = 0;
            }
            if (num == 0) {
                recharge[0] = (recharge[0] == 0) ? A[i] + R : recharge[0];
                recharge[1] = (recharge[1] == 0) ? A[i] + 2 * R : recharge[1];
            }
            else if (num == 1) {
                recharge[0] = (recharge[1] == 0) ? A[i] + R : recharge[1];
                recharge[1] = 0;
            }
            if (num < 0) {
                return "NO";
            }
            if (Math.abs(A[i + 1] - A[i]) < R && num == 0) {
                return "NO";
            }
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
