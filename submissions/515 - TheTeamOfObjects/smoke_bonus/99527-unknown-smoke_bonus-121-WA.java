import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Arrays;

public class prob2b {
    public static void main(String[] args) throws Exception{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);
        int testcases = Integer.parseInt(br.readLine());
        for (int i = 0; i < testcases; i++) {
            String[] info = br.readLine().split(" ");
            int num_of_requests = Integer.parseInt(info[0]);
            int length_of_recharge = Integer.parseInt(info[1]);
            int[] times = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            boolean breaked = false;
            for (int j = 0; j < num_of_requests-2; j++) {
                if ((times[j + 2] - times[j]) < (length_of_recharge)){
                    pw.println("NO");
                    breaked = true;
                    break;
                }
            }
            if (!breaked) {
                pw.println("YES");
            }
        }
        pw.flush();
    }
}
