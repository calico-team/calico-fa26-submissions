import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
class Solution {
    static String solve(int N, int R, int[] A) {
        int smokes = 2;
        int lastRecharge = 0;
        int seconds = 0;
        for(int i=0; i<A.length; i++){
            seconds = A[i];
            int count = (seconds-lastRecharge)/R;
            smokes += count;
            if(smokes>=2){smokes=2; lastRecharge=seconds;} else{lastRecharge+=count*R;}
            if(smokes==0){return "NO";}
            smokes--;
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
