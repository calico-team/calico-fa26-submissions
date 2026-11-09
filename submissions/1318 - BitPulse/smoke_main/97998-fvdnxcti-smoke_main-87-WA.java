import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        while (T-- > 0) {
            int N = sc.nextInt();
            int R = sc.nextInt();
            long t1 = 0;
            long t2 = 0;
            boolean ok = true;
            for (int i = 0; i < N; i++) {
                long a = sc.nextLong();
                if (!ok) continue;
                long first, second;
                if (t1 < t2) {
                    first = t1;
                    second = t2;
                } else {
                    first = t2;
                    second = t1;
                }
                if (first <= a) {
                    first = a + R;
                    second = Math.max(second, first);
                } else {
                    ok = false;
                }
                t1 = first;
                t2 = second;
            }
            System.out.println(ok ? "YES" : "NO");
        }
        sc.close();
    }
}