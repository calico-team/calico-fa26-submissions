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
        boolean[] charges = new boolean[2];
        charges[0] = true;
        charges[1] = true;
        int currentCharge = 0;
        int chargeTime = R;

        for(int x=0; x<A.length; x++){
            if(x>0){
                currentCharge -= A[x-1]-A[x];
            }else{
                currentCharge -= 0-A[x];
            }
            while (currentCharge>=chargeTime) { 
                currentCharge -= chargeTime;
                if(!charges[0]){
                    charges[0] = true;
                }else{
                    charges[1] = true;
                }
            }
            if(!charges[0]&&!charges[1]){
                return "NO";
            }

            if(charges[0]){
                charges[0]=false;
                continue;
            }else if(charges[1]){
                charges[1]=false;
                continue;
            }else{
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