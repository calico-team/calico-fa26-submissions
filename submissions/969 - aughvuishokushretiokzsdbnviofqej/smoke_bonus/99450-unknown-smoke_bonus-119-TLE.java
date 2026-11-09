import java.util.Scanner;
public class calico_2026_2 {
    public static void main (String[] args) {
        Scanner scan = new Scanner (System.in);
        if (!scan.hasNextInt()) {
            scan.close();
            return;
        }
        int t = scan.nextInt();
        for (int i = 0; i < t; i++) {
            int n = scan.nextInt();
            long r = scan.nextLong();
            long charge = 2;
            long[] recharge = new long[n];
            int head = 0;
            int tail = 0;
            boolean pos = true;
            for (int j = 0; j < n; j++) {
                long time = scan.nextLong();
                while (head < tail && recharge[head] <= time) {
                    head++;
                    charge++;
                }
                if (charge > 2) {
                    charge = 2;
                }
                if (pos == true) {
                    if (charge > 0) {
                        charge--;
                        long finish;
                        if (head == tail) {
                            finish = time + r;
                        } else {
                            finish = recharge[tail - 1] + r;
                        }
                        recharge[tail] = finish;
                        tail++;
                    } else {
                        pos = false;
                    }
                }
            }
            if (pos) {
                System.out.println("YES");
            } else {
                System.out.println("NO");
            }
        }
        scan.close();
    }
}
