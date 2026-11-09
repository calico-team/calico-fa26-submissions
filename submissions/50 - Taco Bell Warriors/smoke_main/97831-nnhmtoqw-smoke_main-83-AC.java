import java.util.*;

public class p2 {
    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);
        int t = in.nextInt();
        while (t-- != 0) {
            int t1 = 0; 
            int t2 = 0; 
            int numRequests = in.nextInt();
            int resetTime = in.nextInt();
            boolean met = true;

            for (int i = 0; i < numRequests; i++) {
                int time = in.nextInt();
                if (time >= t1) {
                    t1 = t2;
                    t2 = Math.max(time, t2) + resetTime;
                } else {
                    met = false;
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