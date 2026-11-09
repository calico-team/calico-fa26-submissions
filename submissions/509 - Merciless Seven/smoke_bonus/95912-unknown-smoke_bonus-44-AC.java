import java.io.*;
import java.util.*;

class Solution {

    /*
     * Output whether all of the requests can be fulfilled.
     *
     * N: Number of smoke requests
     * R: Number of seconds needed for a smoke charge to recharge
     * A: List of timestamps where smokes are requested
     */
    static String solve(int N, int R, int[] A) {
        int smokes = 2;
        int reload1 = 0;
        int reload2 = 0;
        int prev = 0;
        for (int i = 0; i < N; i++)
        {
        	if (reload1 > 0)
        	{
        		reload1 -= (A[i] - prev);
        	if (reload1 <= 0)
        	{
        		reload1 = 0;
        		smokes++;
        	}

        	}
        	if (reload2 > 0)
        	{

        	reload2 -= (A[i] - prev);
        	if (reload2 <= 0)
        	{
        		reload2 = 0;
        		smokes++;
        	}
        	}
       		if (reload1 == 0)
        	{
        		smokes--;
        		reload1 = R + reload2;
        	} else if (reload2 == 0)
        	{
        		smokes--;
        		reload2 = R + reload1;
        	} else {
        		return "NO";
        	}
        	prev = A[i];
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
