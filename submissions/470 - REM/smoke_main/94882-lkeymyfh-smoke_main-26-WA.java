import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;

public class prob1 {
    static String solve(int N, int R, int[] A) {
        int smokes = 2;
        int timeleft = 0;
        for (int i = 0; i < N; i++) {
            int curr = A[i];
            while(timeleft <= curr && smokes < 2 && true) {
                smokes++;timeleft += R;
            }
            if(smokes <= 0) return "NO";
            smokes--;
            if(timeleft < curr + R) timeleft = curr + R;
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
