import java.io.*;
import java.util.*;

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(br.readLine().trim());

        for (int tc = 0; tc < t; tc++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int n = Integer.parseInt(st.nextToken());
            int k = Integer.parseInt(st.nextToken());

            st = new StringTokenizer(br.readLine());
            char[] letters = new char[k];
            for (int i = 0; i < k; i++) {
                letters[i] = st.nextToken().charAt(0);
            }

            int[] pos = new int[n];
            char[] ans = new char[n];
            boolean[] done = new boolean[n];

            while (true) {
                for (int i = 0; i < n; i++) {
                    if (!done[i]) {
                        ans[i] = letters[pos[i]];
                    }
                }
                System.out.println(new String(ans));
                System.out.flush();

                String res = br.readLine().trim();
                if (res.equals("CORRECT")) {
                    break;
                }

                for (int i = 0; i < n; i++) {
                    if (res.charAt(i) == '_') {
                        pos[i]++;
                    } else {
                        done[i] = true;
                    }
                }
            }
        }
    }
