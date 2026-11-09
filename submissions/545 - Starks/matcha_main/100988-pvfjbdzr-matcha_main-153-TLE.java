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

            int ans = 0;
            // Build the maximum XOR sum bit by bit from MSB to LSB
            for (int k = 29; k >= 0; k--) {
                int target = (ans << 1) | 1;
                
                if (canForm(L, R, N, k, 0, target)) {
                    ans = target;
                } else {
                    ans = target - 1; // Append 0 instead
                }
            }
            out.println(ans);
        }
        out.flush();
    }

    // Recursive function to check if we can form the 'target' prefix
    private static boolean canForm(int[] L, int[] R, int N, int shift, int index, int target) {
        // Base case: if we have assigned prefixes to all variables
        if (index == N) {
            return target == 0;
        }

        int A = L[index] >> shift;
        int B = R[index] >> shift;

        // If the variable's prefix is completely fixed
        if (A == B) {
            return canForm(L, R, N, shift, index + 1, target ^ A);
        }
        
        // If the valid prefix range is large enough to contain at least an even-odd pair,
        // it acts as a 1-bit wildcard for the lowest bit of the prefix.
        if (B - A >= 2) {
            // We can form both an even prefix and an odd prefix (differs by exactly 1 in the lowest bit)
            // By picking appropriately, we can satisfy the lowest bit requirement of 'target'
            // To aggressively prune, we check if the remaining variables can absorb the rest of the target
            if (canForm(L, R, N, shift, index + 1, target ^ A) || 
                canForm(L, R, N, shift, index + 1, target ^ (A + 1)) ||
                canForm(L, R, N, shift, index + 1, target ^ B) || 
                canForm(L, R, N, shift, index + 1, target ^ (B - 1))) {
                return true;
            }
            return false;
        }

        // B - A == 1: the range contains exactly two elements {A, B}
        if (canForm(L, R, N, shift, index + 1, target ^ A)) {
            return true;
        }
        if (canForm(L, R, N, shift, index + 1, target ^ B)) {
            return true;
        }

        return false;
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