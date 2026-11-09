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
        int charges = 1;
        int timeBetween = 0;
        int buildup = 0;
        for (int i = 1; i < N; i++)
        {
            timeBetween = A[i] - A[i - 1];
            if (timeBetween < R )
            {
                charges--;
                if (charges == 0)
                {
                    return "NO";
                }
            }
            if (timeBetween <= (2 * R))
            {
            if (buildup >= R)
            {
                charges++;
                buildup = 0;
            }
            }
            else if (timeBetween > 2 * R)
            {
                charges = 2;
            }
            if (charges < 2 && charges >= 0)
            {
                
                if (timeBetween > R)
                {
                    charges++;
                }
                else
                {
                    buildup += timeBetween;
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