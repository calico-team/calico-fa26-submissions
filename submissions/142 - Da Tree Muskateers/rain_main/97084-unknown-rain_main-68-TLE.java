
import java.io.*;
import java.util.*;

public class skibidi {
    public static void main(String[] args) throws IOException 
    {

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int T = Integer.parseInt(br.readLine().trim());

        for (int t = 0; t < T; t++) 
        {

            StringTokenizer st = new StringTokenizer(br.readLine());

            int N = Integer.parseInt(st.nextToken());
            long K = Long.parseLong(st.nextToken());

            int[] x = new int[N];
            int[] y = new int[N];
            int[] z = new int[N];
            char[] d = new char[N];

            for (int i = 0; i < N; i++) 
            {

                st = new StringTokenizer(br.readLine());

                x[i] = Integer.parseInt(st.nextToken());
                y[i] = Integer.parseInt(st.nextToken());
                z[i] = Integer.parseInt(st.nextToken());
                d[i] = st.nextToken().charAt(0);
            }

            long langfei = 0;

            for (int i = 0; i < N; i++) 
            {

                if (d[i] != 'E') 
                {
                    continue;
                }

                for (int j = 0; j < N; j++) {

                    if (d[j] != 'N') 
                    {
                        continue;
                    }

                    if (x[i] + y[i] != x[j] + y[j]) 
                    {
                        continue;
                    }

                    long days = x[j] - x[i];

                    if (days < 0 || days >= K) {
                        continue;
                    }

                    
                    if (z[i] != z[j]) {
                        langfei++;
                    }
                }
            }

            long answer = (long) N * K - langfei;

            System.out.println(answer);
        }
    }
}
