import java.io.*;
import java.lang.Math;

class Solution {

    /*
     * Output whether all of the requests can be fulfilled.
     *
     * N: Number of smoke requests
     * R: Number of seconds needed for a smoke charge to recharge
     * A: List of timestamps where smokes are requested
     */
    static String solve(int smokeReq, int timeCharge, int[] array) {
        

        int charges = 2;
        int time = 0;
        
        for(int i = 0; i < array.length; i++){

            if(charges < 2){
                int recovered = (i - time) / timeCharge;
                charges = Math.min(2, charges + recovered);
                time += recovered * timeCharge;
            }

            if(charges == 2){
                time = 1;
            }

            if(charges == 0){
                return "NO";
            }

            charges--;

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
