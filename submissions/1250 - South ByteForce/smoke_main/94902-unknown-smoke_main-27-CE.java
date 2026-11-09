import java.io.*;
import java.uil.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int T = Integer.parseInt(br.readLine().trim());

        for (int test = 0; test < T; test++) {
            String[] firstLine = br.readLine().trim().split(" ");
            int N = Integer.parseInt(firstLine[0]);
            int R = Integer.parseInt(firstLine[1]);

            String[] secondLine = br.readLine().trim().split(" ");

            long ready1 = 0;
            long ready2 = 0;

            boolean possible = true;

            for (int i = 0; i < N; i++) {
                long a = Long.parseLong(secondLine[i]);

                if (possible == false) {
                    continue;
                }

                if (ready1 > ready2) {
                    long temp = ready1;
                    ready1 = ready2;
                    ready2 = temp;
                }

                if (ready1 <= a) {
                    long start = a;
                    if (ready2 > a) {
                        start = ready2;
                    }
                    ready1 = start + R;
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
    }
}