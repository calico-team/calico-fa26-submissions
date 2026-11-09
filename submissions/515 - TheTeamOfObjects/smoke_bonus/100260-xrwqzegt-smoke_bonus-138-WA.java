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
            if (times.length <= 2) {
                pw.println("YES");
                continue;
            } 
            int lastUsedTime1 = times[0];
            int lastUsedTime2 = times[1];
            boolean breaked = false;
            for (int j = 2; j < num_of_requests; j++) {
                // if (((times[j + 2] - times[j]) < (length_of_recharge*2)) || (times[j + 2] - times[j]) < (length_of_recharge)){
                //     pw.println("NO");
                //     breaked = true;
                //     break;
                // }
                if (times[j] - lastUsedTime1 >= length_of_recharge) {
                    lastUsedTime2 = lastUsedTime1 + length_of_recharge;
                    lastUsedTime1 = times[j];
                } else if (times[j] - lastUsedTime2 >= length_of_recharge) {
                    lastUsedTime1 = lastUsedTime2 + length_of_recharge;
                    lastUsedTime2 = times[j];
                } else {
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
