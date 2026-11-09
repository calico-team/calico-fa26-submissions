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
        // YOUR CODE HERE
        int smokes = 2;

        int currentRecharge = 0;

        for(int i=1;i<A.length;i++)
        {
        	if(smokes==2)
        	{
        		smokes--;
        	}else
        	{
        		int diff = A[i]-A[i-1];
        		smokes+=diff/R;
        		currentRecharge+=diff%R;
        		if(currentRecharge>=R)
        		{
        			smokes++;
        			if(smokes==2)
        				currentRecharge = 0;
        			else
        				currentRecharge-=R;
        		}
        		smokes--;
        		if(smokes<=0)
        			return "NO";
        	}
        }
        if(smokes>=0)
        	return "YES";
        else
        	return "NO";
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
