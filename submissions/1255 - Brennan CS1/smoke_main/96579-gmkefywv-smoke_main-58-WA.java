import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

        int N = Integer.parseInt(br.readLine());

        for (int i = 0; i < N; i++) {
            ArrayList<Integer> list = new ArrayList<>();
            StringTokenizer st = new StringTokenizer(br.readLine());
            int request = Integer.parseInt(st.nextToken());
            int recharge = Integer.parseInt(st.nextToken());

            StringTokenizer s = new StringTokenizer(br.readLine());
            while (s.hasMoreTokens()) {
                list.add(Integer.parseInt(s.nextToken()));
            }
            boolean check = true;
            for (int j = 0; j < request - 1; j++) {
                int distance = Math.abs(list.get(j) - list.get(j + 1));
                if (distance >= recharge) {
                    check = true;
                }
                else{
                    check = false;
                    break;
                }
            }
            bw.write(check ? "Yes" : "No");
            bw.newLine();
        }

        bw.flush();
        bw.close();
        br.close();
    }
}