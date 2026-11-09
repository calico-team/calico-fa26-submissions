import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

        int repeats = Integer.parseInt(br.readLine());
        while (repeats-- > 0) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int request = Integer.parseInt(st.nextToken());
            int R = Integer.parseInt(st.nextToken());
            StringTokenizer times = new StringTokenizer(br.readLine());

            int charges = 2;
            int nextRecharge = -1;
            boolean check = true;

            for (int i = 0; i < request; i++) {
                int time = Integer.parseInt(times.nextToken());
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
        bw.close();
        br.close();
    }
}