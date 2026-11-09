public class calico_2026_2 {
    public static void main (String[] args) throws Exception {
        int b = System.in.read();
        while (b <= 32) {
            if (b == -1) {
                return;
            }
            b = System.in.read();
        }
        int t = 0;
        while (b > 32) {
            t = t * 10 + (b - '0');
            b = System.in.read();
        }
        for (int i = 0; i < t; i++) {
            while (b <= 32 && b != -1) {
                b = System.in.read();
            }
            int n = 0;
            while (b > 32) {
                n = n * 10 + (b - '0');
                b = System.in.read();
            }
            while (b <= 32 && b != -1) {
                b = System.in.read();
            }
            long r = 0;
            while (b > 32) {
                r = r * 10 + (b - '0');
                b = System.in.read();
            }
            long charge = 2;
            long [] recharge = new long[n];
            int head = 0;
            int tail = 0;
            boolean pos = true;

            for (int j = 0; j < n; j++) {
                while (b <= 32 && b != -1) {
                    b = System.in.read();
                }
                long time = 0;
                while (b > 32) {
                    time = time * 10 + (b - '0');
                    b = System.in.read();
                }
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
    }
}
