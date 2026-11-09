import java.util.*;
public class calico_2026_2 {
    public static void main (String[] args) {
        Scanner scan = new Scanner (System.in);
        if (!scan.hasNextInt()){
            scan.close();
            return;
        }
        int t = scan.nextInt();
        for (int i = 0; i < t; i++) {
            int n = scan.nextInt();
            long r = scan.nextLong();
            long charge = 2;
            long[] recharge = new long [n];
            int head = 0;
            int tail = 0;
            boolean pos = true;
            for (int j = 0; j < n; j++) {
                long time = scan.nextLong();
                while (head < tail && recharge[head] <= time) {
                    head++;
                    charge++;
                }
                if(pos == true) {
                    if (charge > 0) {
                        charge--;
                        if (head == tail) {
                            recharge[tail] = time + r;
                        } else {
                            recharge[tail] = recharge[tail - 1] + r;
                        }
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
