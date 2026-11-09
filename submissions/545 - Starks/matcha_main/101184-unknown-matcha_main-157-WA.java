import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class Solution6 {

    // Pre-allocate arrays to completely bypass Java Garbage Collection overhead
    static int[] L = new int[200005];
    static int[] R = new int[200005];
    static int[] state = new int[200005];
    static int[][] prev_xor_arr = new int[200005][2];

    public static void main(String[] args) {
        FastReader in = new FastReader();
        PrintWriter out = new PrintWriter(System.out);

        String tStr = in.next();
        if (tStr == null) return;
        int T = Integer.parseInt(tStr);

        while (T-- > 0) {
            int N = in.nextInt();
            for (int i = 0; i < N; i++) {
                L[i] = in.nextInt();
            }
            for (int i = 0; i < N; i++) {
                R[i] = in.nextInt();
            }

            for (int i = 0; i < N; i++) {
                state[i] = 0;
            }

            int ans = 0;

            for (int k = 29; k >= 0; k--) {
                // dp[has_state_3][current_xor_sum]
                boolean[][] dp = new boolean[2][2];
                dp[0][0] = true;

                for (int i = 0; i < N; i++) {
                    boolean c0_no3 = false, c1_no3 = false;
                    boolean c0_yes3 = false, c1_yes3 = false;
                    
                    int bitL = (L[i] >> k) & 1;
                    int bitR = (R[i] >> k) & 1;
                    
                    // Determine valid bit choices and whether they lead to a State 3
                    if (state[i] == 0) {
                        if (bitL == 0 && bitR == 0) { c0_no3 = true; }
                        else if (bitL == 1 && bitR == 1) { c1_no3 = true; }
                        else { c0_no3 = true; c1_no3 = true; } 
                    } else if (state[i] == 1) {
                        if (bitL == 0) { c0_no3 = true; c1_yes3 = true; }
                        else { c1_no3 = true; } 
                    } else if (state[i] == 2) {
                        if (bitR == 0) { c0_no3 = true; }
                        else { c1_no3 = true; c0_yes3 = true; } 
                    }
                    
                    boolean[][] next_dp = new boolean[2][2];
                    
                    // Branch 1: Path without entering State 3
                    if (dp[0][0]) {
                        if (c0_no3) { next_dp[0][0] = true; prev_xor_arr[i][0] = 0; }
                        if (c1_no3) { next_dp[0][1] = true; prev_xor_arr[i][1] = 0; }
                        if (c0_yes3) next_dp[1][0] = true;
                        if (c1_yes3) next_dp[1][1] = true;
                    }
                    if (dp[0][1]) {
                        if (c0_no3) { next_dp[0][1] = true; prev_xor_arr[i][1] = 1; }
                        if (c1_no3) { next_dp[0][0] = true; prev_xor_arr[i][0] = 1; }
                        if (c0_yes3) next_dp[1][1] = true;
                        if (c1_yes3) next_dp[1][0] = true;
                    }
                    
                    // Branch 2: Path where State 3 has already been achieved
                    boolean c0_any = c0_no3 || c0_yes3;
                    boolean c1_any = c1_no3 || c1_yes3;
                    
                    if (dp[1][0]) {
                        if (c0_any) next_dp[1][0] = true;
                        if (c1_any) next_dp[1][1] = true;
                    }
                    if (dp[1][1]) {
                        if (c0_any) next_dp[1][1] = true;
                        if (c1_any) next_dp[1][0] = true;
                    }
                    
                    dp = next_dp;
                }

                // Greedily lock in the best optimal outcome based on priority
                if (dp[1][1]) {
                    ans |= (1 << k);
                    if (k > 0) ans |= ((1 << k) - 1);
                    break;
                } else if (dp[0][1]) {
                    ans |= (1 << k);
                    int curr_xor = 1;
                    
                    // Backtrack to update specific variable states
                    for (int i = N - 1; i >= 0; i--) {
                        int p_xor = prev_xor_arr[i][curr_xor];
                        int bit = curr_xor ^ p_xor;
                        
                        if (state[i] == 0) {
                            int bitL = (L[i] >> k) & 1;
                            int bitR = (R[i] >> k) & 1;
                            if (bitL != bitR) {
                                if (bit == 0) state[i] = 1;
                                else state[i] = 2;
                            }
                        }
                        curr_xor = p_xor;
                    }
                } else if (dp[1][0]) {
                    if (k > 0) ans |= ((1 << k) - 1);
                    break;
                } else if (dp[0][0]) {
                    int curr_xor = 0;
                    
                    for (int i = N - 1; i >= 0; i--) {
                        int p_xor = prev_xor_arr[i][curr_xor];
                        int bit = curr_xor ^ p_xor;
                        
                        if (state[i] == 0) {
                            int bitL = (L[i] >> k) & 1;
                            int bitR = (R[i] >> k) & 1;
                            if (bitL != bitR) {
                                if (bit == 0) state[i] = 1;
                                else state[i] = 2;
                            }
                        }
                        curr_xor = p_xor;
                    }
                }
            }
            out.println(ans);
        }
        out.flush();
    }

    static class FastReader {
        BufferedReader br;
        StringTokenizer st;

        public FastReader() {
            br = new BufferedReader(new InputStreamReader(System.in));
        }

        String next() {
            while (st == null || !st.hasMoreElements()) {
                try {
                    String line = br.readLine();
                    if (line == null) return null;
                    st = new StringTokenizer(line);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }

        int nextInt() {
            return Integer.parseInt(next());
        }
    }
}