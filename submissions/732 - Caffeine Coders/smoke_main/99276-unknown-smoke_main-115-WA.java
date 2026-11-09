import java.io.*;

class Smoke {

    /*
     * Output whether all of the requests can be fulfilled.
     *
     * N: Number of smoke requests
     * R: Number of seconds needed for a smoke charge to recharge
     * A: List of timestamps where smokes are requested
     */
    static String solve(int N, int R, int[] A) {
        int k = 1;
        int t = 0;
        int c = 0;
        for(int i = 1; i<N; i++){
            t = A[i];
            if(t - A[i-1] >= 2*R){
                k++;
            } else if(t - A[i-1] >= R){
                k++;
            } else {
                c+= t-A[i-1];
            }
            if(c>= R){
                k++;
            }
            k--;
            if(k<0){
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
            out.flush();
        }
    }
}

