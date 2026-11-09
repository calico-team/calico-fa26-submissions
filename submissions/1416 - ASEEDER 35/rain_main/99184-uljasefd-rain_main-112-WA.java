import java.util.Scanner;

public class problemFour {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        if (!sc.hasNextInt()) return;
        int T = sc.nextInt();
        StringBuilder sb = new StringBuilder();

        while (T-- > 0) {
            int N = sc.nextInt();
            long K = sc.nextLong();
            
            int[] x = new int[N];
            int[] y = new int[N];
            int[] z = new int[N];
            char[] d = new char[N];
            
            for (int i = 0; i < N; i++) {
                x[i] = sc.nextInt();
                y[i] = sc.nextInt();
                z[i] = sc.nextInt();
                d[i] = sc.next().charAt(0);
            }

            long totalRain = N * K;

            for (int i = 0; i < N; i++) {
                for (int j = i + 1; j < N; j++) {
                    if (d[i] == d[j]) continue;

                    int e = -1, n = -1;
                    if (d[i] == 'E' && d[j] == 'N') {
                        e = i; n = j;
                    } else if (d[i] == 'N' && d[j] == 'E') {
                        e = j; n = i;
                    } else {
                        continue;
                    }

                    int time = x[n] - x[e];
                   
                    if (time > 0 && time == y[e] - y[n] && time <= K) {
                        if (z[e] < z[n]) {
                            totalRain -= (K - time + 1);
                        } else if (z[n] < z[e]) {
                            totalRain -= (K - time + 1);
                        }
                    }
                }
            }
            sb.append(totalRain).append("\n");
        }
        System.out.print(sb.toString());
    }
}