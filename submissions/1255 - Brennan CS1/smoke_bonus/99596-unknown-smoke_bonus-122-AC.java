import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        int T = Integer.parseInt(br.readLine());
        while (T-- > 0) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int N = Integer.parseInt(st.nextToken());
            long R = Long.parseLong(st.nextToken());
            st = new StringTokenizer(br.readLine());

            int charges = 2;
            long nextRecharge = -1;
            boolean check = true;

            for (int i = 0; i < N; i++) {
                long time = Long.parseLong(st.nextToken());

                while (charges < 2 && nextRecharge != -1 && nextRecharge <= time) {
                    charges++;

                    if (charges == 2) {
                        nextRecharge = -1;
                    } else {
                        nextRecharge += R;
                    }
                }

                if (charges == 0) {
                    check = false;
                    break;
                }

                charges--;

                if (charges == 1 && nextRecharge == -1) {
                    nextRecharge = time + R;
                }
            }

            bw.write(check ? "YES" : "NO");
            bw.newLine();
        }

        bw.flush();
        bw.close();
        br.close();
    }
}