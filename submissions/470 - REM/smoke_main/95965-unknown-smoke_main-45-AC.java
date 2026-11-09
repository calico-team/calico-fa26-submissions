import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

public class prob1 {
    static String solve(int N, int R, int[] A) {
        int smokes = 2;
        int smoke1 = 0, smoke2 = 0; //time till smoke is filled
        for (int i = 0; i < N; i++) {
            int curr = A[i];
            if(smoke1 <= curr) smoke1 = curr + R;
            else if(smoke2 <= curr) smoke2 = Math.max(curr, smoke1) + R;
            else if (smoke1> curr && smoke2 > curr)return "NO";
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
