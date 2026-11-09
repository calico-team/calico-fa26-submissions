import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;
import java.io.IOException;

public class problemTwoBit {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        
        int t = Integer.parseInt(st.nextToken());
        StringBuilder sb = new StringBuilder();

        while (t-- > 0) {
            if (!br.ready()) break;
            st = new StringTokenizer(br.readLine());
            int n = Integer.parseInt(st.nextToken());
            long r = Long.parseLong(st.nextToken());
            
            long[] a = new long[n];
            st = new StringTokenizer(br.readLine());
            for (int i = 0; i < n; i++) {
                a[i] = Long.parseLong(st.nextToken());
            }

            long cd1 = 0; 
            long cd2 = 0; 
            long lastTime = 0; 
            boolean possible = true;

            for (int i = 0; i < n; i++) {
                long currentTime = a[i];
                long timePassed = currentTime - lastTime; 
                lastTime = currentTime;

                cd1 = Math.max(0, cd1 - timePassed);
                cd2 = Math.max(0, cd2 - timePassed);

                if (cd1 == 0) {
                    cd1 = r; 
                    } else if (cd2 == 0) {
                    cd2 = r; 
                } else {
                    possible = false; 
                    break;
                }
            }

            if (possible) {
                sb.append("YES\n");
            } else {
                sb.append("NO\n");
            }
        }
        System.out.print(sb.toString());
    }
}