import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;
import java.io.IOException;

public class problemFourShi {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        
        int T = Integer.parseInt(st.nextToken());
        StringBuilder sb = new StringBuilder();

        while (T-- > 0) {
            st = new StringTokenizer(br.readLine());
            int N = Integer.parseInt(st.nextToken());
            long K = Long.parseLong(st.nextToken());
            
            int[] x = new int[N];
            int[] y = new int[N];
            int[] z = new int[N];
            char[] d = new char[N];
            
            for (int i = 0; i < N; i++) {
                st = new StringTokenizer(br.readLine());
                x[i] = Integer.parseInt(st.nextToken());
                y[i] = Integer.parseInt(st.nextToken());
                z[i] = Integer.parseInt(st.nextToken());
                d[i] = st.nextToken().charAt(0);
            }

            long totalRain = (long) N * K;

            for (int i = 0; i < N; i++) {
                for (int j = i + 1; j < N; j++) {
                    if (d[i] == d[j]) continue;

                    int e = -1, n = -1;
                    if (d[i] == 'E' && d[j] == 'N') { e = i; n = j; }
                    else if (d[i] == 'N' && d[j] == 'E') { e = j; n = i; }
                    else continue;

                    long timeToMeet = x[n] - x[e];
                    
                    if (timeToMeet > 0 && timeToMeet == y[e] - y[n] && timeToMeet <= K) {
                        if (z[e] < z[n]) {
                            totalRain -= (K - timeToMeet + 1);
                        } else if (z[n] < z[e]) {
                            totalRain -= (K - timeToMeet + 1);
                        }
                    }
                }
            }
            sb.append(totalRain).append("\n");
        }
        System.out.print(sb.toString());
    }
}