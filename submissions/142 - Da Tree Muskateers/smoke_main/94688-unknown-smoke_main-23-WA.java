
import java.io.*;

public class Valorant {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(
            new InputStreamReader(System.in)
        );

        int T = Integer.parseInt(br.readLine().trim());

        for (int i = 0; i < T; i++) {
            String[] k = br.readLine().trim().split("\\s+");

            int N = Integer.parseInt(k[0]);
            int R = Integer.parseInt(k[1]);

            String[] patrick = br.readLine().trim().split("\\s+");

            long smoke1 = 0;
            long smoke2 = 0;

            boolean p = true;

            for (int j = 0; j < N; j++) {
                long time = Long.parseLong(patrick[j]);

                if (smoke1 <= time) 
                {
                    smoke1 = time + R;
                }
                else if (smoke2 <= time) 
                {
                    smoke2 = time + R;
                }
                else 
                {
                    p = false;
                    break;
                }
            }

            if (p == true) 
            {
                System.out.println("YES");
            } 
            else 
            {
                System.out.println("NO");
            }
        }
    }
}
