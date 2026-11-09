import java.util.*;
public class calico_2026_2 {
    public static void main (String[] args) {
        Scanner scan = new Scanner (System.in);
        if (!scan.hasNextInt()){
            return;
        }
        int t = scan.nextInt();

        for (int i = 0; i < t; i++) {
            int n = scan.nextInt();
            int r = scan.nextInt();

            int charge = 2;
            int[] recharge = new int [n];
            int head = 0;
            int tail = 0;
            boolean pos = false;

            for (int j = 0; j < n; j++) {
                int time = scan.nextInt();
                while (head < tail && recharge[head] <= time) {
                    head++;
                    charge++;
                }
                if (charge > 0) {
                    charge--;
                    if (head == tail) {
                        recharge[tail] = time + r;
                    } else {
                        recharge[tail] = recharge[tail - 1] + r;
                    }
                    tail++;
                    pos = true;
                } else {
                    pos = false;
                }
            }
            if (pos) {
                System.out.println("yes");
            } else {
                System.out.println("no");
            }
        }
    }
}
