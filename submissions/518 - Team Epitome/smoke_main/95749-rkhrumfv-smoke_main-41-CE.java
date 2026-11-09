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
        int charges = 2;
        int firstFinish = -1;
        int secondFinish = -1;

        for(int i = 0 ; i < N; i++)
        {
            int t = A[i];

            //When the recharges are completed before or at time t
            if(firstFinish != -1 && firstFinish <= t)
            {
                charges++;
                firstFinish = secondFinish;
                secondFinish = -1; 
                //Equals -1 when no recharge is available
            }
            if(firstFinish != -1 && firstFinish <= t)
            {
                charges++;
                firstFinish = -1;
            }

            #Checks if a charge is available
            if(charges <= 0)
            {
                return "no";
            }

            //After it consumes its charges, calculates the time it takes to recharge
            charges--;
            if(firstFinish == -1)
            {
                firstFinish = t + R;
            }
            else
            {
                seconfFinish = firstFinish + R;
            }
        }
    }

    return "Yes";

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
