import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
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
        int available = 2;
        long nextFinish = 0;
        int waiting = 0;

        for (long time : a) {

            while (nextFinish > 0 && nextFinish <= time) {
                available++;
                if (waiting > 0) {
                    waiting--;
                    nextFinish = nextFinish + r;
                } else {
                    nextFinish = 0;
                    break;
                }
            }


            if (available > 0) {
                available--;
                if (nextFinish == 0) {

                    nextFinish = time + r;
                } else {

                    waiting++;
                }
            } else {
                return false;
            }
        }
        return true;
    }
}