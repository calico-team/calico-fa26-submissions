import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class Main {
    public static void Main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int t = scanner.nextInt();

        while (t-- > 0) {
            int n = scanner.nextInt();
            long r = scanner.nextLong();
            long[] a = new long[n];
            for (int i = 0; i < n; i++) {
                a[i] = scanner.nextLong();
            }

            if (canFulfillRequests(n, r, a)) {
                System.out.println("YES");
            } else {
                System.out.println("NO");
            }
        }
        scanner.close();
    }

    public static boolean canFulfillRequests(int n, long r, long[] a) {
        int currentCharges = 2;
        Queue<Long> rechargeQueue = new LinkedList<>();
        for (long time : a) {
            while (!rechargeQueue.isEmpty() && rechargeQueue.peek() <= time) {
                rechargeQueue.poll();
                currentCharges++;
            }
            if (currentCharges > 0) {
                currentCharges--;
                rechargeQueue.add(time + r);
            } else {
                return false;
            }
        }
        return true;
        }
}