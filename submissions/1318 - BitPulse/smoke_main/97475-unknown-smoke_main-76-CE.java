import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        while (T-- > 0) {
            int N = sc.nextInt();
            long R = sc.nextLong();
            boolean ok = true;
            for (int i = 0; i < N; i++) {
                long a = sc.nextLong();
                if (!ok) continue;
                if (t1 <= a) {
                    t1 = a + R;
                } else if (t2 <= a) {
                    t2 = a + R;
                } else {
                    ok = false;
                }
            }
            System.out.println(ok ? "YES" : "NO");
        }
        sc.close();
    }
}