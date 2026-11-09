import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class Solution6 {

    public static void main(String[] args) {
        FastReader in = new FastReader();
        PrintWriter out = new PrintWriter(System.out);

        String tStr = in.next();
        if (tStr == null) return;
        int T = Integer.parseInt(tStr);

        while (T-- > 0) {
            int N = in.nextInt();
            int[] L = new int[N];
            int[] R = new int[N];

            for (int i = 0; i < N; i++) {
                L[i] = in.nextInt();
            }
            for (int i = 0; i < N; i++) {
                R[i] = in.nextInt();
            }

            // States for each variable:
            // 0: L_prefix == R_prefix (tight on both)
            // 1: matches L_prefix, strictly less than R_prefix
            // 2: matches R_prefix, strictly greater than L_prefix
            // 3: strictly between L_prefix and R_prefix (fully flexible)
            int[] state = new int[N];

            int ans = 0;

            for (int k = 29; k >= 0; k--) {
                // We want to test if we can form a 1 at the k-th bit of the XOR sum
                int targetXor = 1;

                // DP reachability: dp[has_state_3][xor_value]
                boolean[][] dp = new boolean[2][2];
                dp[0][0] = true;

                // To reconstruct/update states later, we track the bit chosen for each variable
                int[] chosenBit = new int[N];
                int[][] parentState = new int[N + 1][2]; // Simplified tracking

                // Since we need to know transitions, let's use a straightforward check per variable:
                // For each variable, what are the possible bits it can output and what are their resulting states?
                
                boolean possible = false;
                
                // Let's check if we can achieve targetXor = 1 vs 0
                // We test targetBit = 1 first, if possible we take it, else 0.
                for (int targetBit = 1; targetBit >= 0; targetBit--) {
                    boolean[][] nextDp = new boolean[2][2];
                    nextDp[0][0] = dp[0][0];
                    nextDp[0][1] = dp[0][1];
                    nextDp[1][0] = dp[1][0];
                    nextDp[1][1] = dp[1][1];

                    boolean valid = true;
                    int[][] trans = new int[N][2]; // stores whether bit 0/1 is possible and resulting state type

                    for (int i = 0; i < N; i++) {
                        int bitL = (L[i] >> k) & 1;
                        int bitR = (R[i] >> k) & 1;

                        boolean can0 = false, can1 = false;
                        int nextState0 = 0, nextState1 = 0;

                        if (state[i] == 3) {
                            can0 = true; can1 = true;
                            nextState0 = 3; nextState1 = 3;
                        } else if (state[i] == 0) {
                            if (bitL == bitR) {
                                if (bitL == 0) { can0 = true; nextState0 = 0; }
                                else { can1 = true; nextState1 = 0; }
                            } else {
                                can0 = true; can1 = true;
                                nextState0 = 1; // choosing 0 makes it < R_prefix -> state 1
                                nextState1 = 2; // choosing 1 makes it > L_prefix -> state 2
                            }
                        } else if (state[i] == 1) {
                            if (bitL == 0) {
                                can0 = true; nextState0 = 1;
                                can1 = true; nextState1 = 3; // choosing 1 crosses R boundary -> state 3
                            } else {
                                can1 = true; nextState1 = 1;
                            }
                        } else if (state[i] == 2) {
                            if (bitR == 0) {
                                can0 = true; nextState0 = 2;
                            } else {
                                can0 = true; nextState0 = 3; // choosing 0 crosses L boundary -> state 3
                                can1 = true; nextState1 = 2;
                            }
                        }

                        trans[i][0] = can0 ? 1 : 0;
                        trans[i][1] = can1 ? 1 : 0;
                    }

                    // Standard subset convolution / DP for bitwise XOR
                    boolean[][] currDp = new boolean[2][2];
                    currDp[0][0] = true;

                    boolean ok = true;
                    for (int i = 0; i < N; i++) {
                        boolean[][] nextStep = new boolean[2][2];
                        boolean can0 = (trans[i][0] == 1);
                        boolean can1 = (trans[i][1] == 1);

                        for (int has3 = 0; has3 < 2; has3++) {
                            for (int xorVal = 0; xorVal < 2; xorVal++) {
                                if (!currDp[has3][xorVal]) continue;

                                // Try choosing bit 0
                                if (can0) {
                                    int nXor = xorVal ^ 0;
                                    int n3 = has3 | (getNewState3Flag(state[i], 0, k, L[i], R[i]) ? 1 : 0);
                                    nextStep[n3][nXor] = true;
                                }
                                // Try choosing bit 1
                                if (can1) {
                                    int nXor = xorVal ^ 1;
                                    int n3 = has3 | (getNewState3Flag(state[i], 1, k, L[i], R[i]) ? 1 : 0);
                                    nextStep[n3][nXor] = true;
                                }
                            }
                        }
                        currDp = nextStep;
                    }

                    // Check if we can achieve targetBit with either has3 = 0 or 1
                    if (currDp[0][targetBit] || currDp[1][targetBit]) {
                        ans |= (targetBit << k);
                        if (targetBit == 1) {
                            // If we achieved 1, we lock in choices and update states
                            updateStates(state, k, L, R, 1);
                        } else {
                            updateStates(state, k, L, R, 0);
                        }
                        possible = true;
                        break;
                    }
                }
            }
            out.println(ans);
        }
        out.flush();
    }

    private static boolean getNewState3Flag(int currentState, int chosenBit, int k, int L_val, int R_val) {
        int bitL = (L_val >> k) & 1;
        int bitR = (R_val >> k) & 1;
        if (currentState == 3) return true;
        if (currentState == 0 && bitL != bitR) return false;
        if (currentState == 1 && chosenBit == 1 && bitL == 0) return true;
        if (currentState == 2 && chosenBit == 0 && bitR == 1) return true;
        return currentState == 3;
    }

    private static void updateStates(int[] state, int k, int[] L, int[] R, int targetBit) {
        // Greedily update each variable's state based on the chosen bit
        for (int i = 0; i < state.length; i++) {
            int bitL = (L[i] >> k) & 1;
            int bitR = (R[i] >> k) & 1;

            if (state[i] == 0) {
                if (bitL != bitR) {
                    if (targetBit == 0) state[i] = 1;
                    else state[i] = 2;
                }
            } else if (state[i] == 1) {
                if (bitL == 0 && targetBit == 1) state[i] = 3;
            } else if (state[i] == 2) {
                if (bitR == 1 && targetBit == 0) state[i] = 3;
            }
        }
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