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
    int available = 2;
    int pending = 0;
    long firstRecharge = 0;
    long secondRecharge = 0;

    for (int i = 0; i < N; i++) {
        long time = A[i];

        while (pending > 0 && firstRecharge <= time) {
            available++;

            if (pending == 2) {
                firstRecharge = secondRecharge;
            }
            pending--;
        }

        if (available == 0) {
            return "NO";
        }

        available--;

        if (pending == 0) {
            firstRecharge = time + R;
        } else {
            secondRecharge = Math.max(time, firstRecharge) + R;
        }
        pending++;
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
