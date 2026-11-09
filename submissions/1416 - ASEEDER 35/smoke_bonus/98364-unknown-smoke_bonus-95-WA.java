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
            long chargeOne = 0;
            long chargeTwo = 0;

            for (int i = 0; i < N; i++) {
                long currentTime = A[i];

                if (chargeOne <= currentTime) {
                    chargeOne = currentTime + R;
                } else if (chargeTwo <= currentTime) {
                    chargeTwo = currentTime + R;
                } else {
                    canSmokeAll = false;
                    break;
                }
                
                if (chargeOne > chargeTwo) {
                    long temp = chargeOne;
                    chargeOne = chargeTwo;
                    chargeTwo = temp;
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