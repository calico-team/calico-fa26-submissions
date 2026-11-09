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
        int totalPower = 2;
    long timeToRecharge = 0;

    long[] rechargeTimes = new long[N];

    int refillNumber = 0;
    int refillRatio = 0;

    for (int i = 0; i < N; i++) {

        for (int j = refillNumber; j < refillRatio; j++) {

            if (rechargeTimes[j] > A[i]) {
                break;
            }

            totalPower++;
            refillNumber++;
        }

        if (totalPower == 0) {
            return "NO";
        }

        totalPower--;

        if (timeToRecharge < A[i]) {
            timeToRecharge = A[i];
        }

        timeToRecharge += R;

        rechargeTimes[refillRatio] = timeToRecharge;
        refillRatio++;
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
