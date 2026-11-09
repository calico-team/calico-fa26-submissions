
import java.util.Scanner;

class answer {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int t = sc.nextInt();

        for (int i = 0; i < t; i++) {
            int n = sc.nextInt();
            int r = sc.nextInt();

            int charges = 2;
            long rechargeTime = 0;
            int waiting = 0;
            boolean possible = true;

            for (int j = 0; j < n; j++) {
                long time = sc.nextLong();

                while (waiting > 0 && rechargeTime <= time) {
                    charges++;
                    waiting--;
                    rechargeTime += r;
                }

                if (charges > 0) {
                    charges--;

                    if (waiting == 0) {
                        rechargeTime = time + r;
                    }

                    waiting++;
                } else {
                    possible = false;
                }
            }

            if (possible) {
                System.out.println("YES");
            } else {
                System.out.println("NO");
            }
        }

        sc.close();
    }
}
