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
        boolean firstCharge = true;
	int firstChargeNum = -1;
	boolean secondCharge = true;
	int secondChargeNum = -1;

	int weAreOn = 0;
	for (int i = A[0]; i < A[N-1]; i++) {
		if (i == A[weAreOn]) { //shooot!
			weAreOn++;
			if (!firstCharge && !secondCharge) {
				return "NO";
			} else if (firstCharge) {
				firstCharge = false;
				firstChargeNum = 0;
			} else if (secondCharge) {
				secondCharge = false;
				secondChargeNum = 0;
			}
		} else { //recharge
			if (!firstCharge) {
				firstChargeNum++;
				if (firstChargeNum == R) {
					firstCharge = true;
					firstChargeNum = -1;
				}
			} else {
				firstChargeNum = -1;

				if (!secondCharge) {
					secondChargeNum++;
					if (secondChargeNum == R) {
						secondCharge = true;
						secondChargeNum = -1;
					}
				} else {
					secondChargeNum = -1;
				}
			}
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
