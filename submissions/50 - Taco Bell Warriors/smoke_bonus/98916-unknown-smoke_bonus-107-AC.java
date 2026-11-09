import java.util.*;
import java.io.*;


public class p2 {
    public static void main(String args[]) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(br.readLine().trim());
        while (t-- != 0) {
            long t1 = 0; 
            long t2 = 0; 
            StringTokenizer wholeLine = new StringTokenizer(br.readLine());
            int numRequests = Integer.parseInt(wholeLine.nextToken());
            long resetTime = Long.parseLong(wholeLine.nextToken());
            boolean met = true;
            
            wholeLine = new StringTokenizer(br.readLine());
            for (int i = 0; i < numRequests; i++) {
                long time = Long.parseLong(wholeLine.nextToken());
                if (time >= t1) {
                    t1 = t2;
                    t2 = Math.max(time, t2) + resetTime;
                } else {
                    met = false;
                    break;
                }
            }
            if (met) {
                System.out.println("YES");
            } else {
                System.out.println("NO");
            }
        }
    }
}