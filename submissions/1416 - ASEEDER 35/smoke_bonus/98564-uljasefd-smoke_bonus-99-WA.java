import java.util.Scanner;

public class problemTwoB {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        if (!sc.hasNextInt()) return;
        int T = sc.nextInt();
        StringBuilder sb = new StringBuilder();

        while (T-- > 0) {
            int N = sc.nextInt();
            long R = sc.nextLong();
            
            long[] A = new long[N];
            for (int i = 0; i < N; i++) {
                A[i] = sc.nextLong();
            }

            boolean canSmokeAll = true;
            
            long charge1_ready_time = 0;
            long charge2_ready_time = 0;

            for (int i = 0; i < N; i++) {
                long currentTime = A[i];

                if (charge1_ready_time <= currentTime) {
                    charge1_ready_time = currentTime + R; }
                    
                                    else if (charge2_ready_time <= currentTime) {
                    charge2_ready_time = currentTime + R; 
                } 
                else {
                    canSmokeAll = false;
                    break; 
                }
                
                if (charge1_ready_time > charge2_ready_time) {
                    long temp = charge1_ready_time;
                    charge1_ready_time = charge2_ready_time;
                    charge2_ready_time = temp;
                }
            }

            if (canSmokeAll) {
                sb.append("YES\n");
            } else {
                sb.append("NO\n");
            }
        }
        System.out.print(sb.toString());
    }
}