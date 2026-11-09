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
        int k = 2;
        int s = 0;
        int time1;
        int time2 = 0;
        int time3 = 0;
        for(int f = 0; f<N; f++){
            time1 = time2;
            time2 = time3;
            time3 = A[f];
            if(k<2&&(time3-time2>=R||(time3-time1>=R&&s==0))){
                k+=1;
                s = 2;
            }
            k-=1;
            s-=1;
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
        }
        out.flush();
    }
}

