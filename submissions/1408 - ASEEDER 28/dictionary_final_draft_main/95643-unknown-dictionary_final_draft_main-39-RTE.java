import java.io.*;

class Solution {

  
    static String solve(int N, int R, int[] A) {
        int charges = 2;
        long cdEnd = -1; // -1 means not recharging

        for (int t : A) {
            while (cdEnd != -1 && cdEnd <= t) {
                charges++;
                if (charges < 2) {
                    cdEnd += R;
                } else {
                    cdEnd = -1;
                }
            }

            if (charges == 0) {
                return "NO";
            }
            charges--;
            if (cdEnd == -1) {
                cdEnd = (long) t + R;
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
