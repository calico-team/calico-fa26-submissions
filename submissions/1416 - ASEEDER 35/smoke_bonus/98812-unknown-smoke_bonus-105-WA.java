import java.util.Scanner;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;
import java.io.IOException;

public class problemTwoBO {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        
        int t = Integer.parseInt(st.nextToken());
        StringBuilder sb = new StringBuilder();
        while (t-- > 0) {
            st = new StringTokenizer(br.readLine());
            int n = Integer.parseInt(st.nextToken());
            long r = Long.parseLong(st.nextToken());
            
            long[] a = new long[n];
            st = new StringTokenizer(br.readLine());
            for (int i = 0; i < n; i++) {
                a[i] = Long.parseLong(st.nextToken());
            }

            if (canFulfillRequests(n, r, a)) {
                sb.append("YES\n");
            } else {
                sb.append("NO\n");
            }
        }
        System.out.print(sb.toString()); 
    }

    public static boolean canFulfillRequests(int n, long r, long[] a) {
        long slot1_ready = 0;
        long slot2_ready = 0;

        for (int i = 0; i < n; i++) {
            long currentTime = a[i];

            if (slot1_ready <= currentTime) {
                slot1_ready = currentTime + r;
            } else if (slot2_ready <= currentTime) {
                slot2_ready = currentTime + r;
            } else {
                return false;
            }

            if (slot1_ready > slot2_ready) {
                long temp = slot1_ready;
                slot1_ready = slot2_ready;
                slot2_ready = temp;
            }
        }
        return true;
    }
}