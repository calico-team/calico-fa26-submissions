import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.StringTokenizer;

// Removed "public" so it compiles regardless of the platform's filename
class Solution {
    
    // Inserts a number into the 31-bit Linear Basis array
    private static void insertBasis(int basis, int x) {
        for (int i = 30; i >= 0; i--) {
            if (((x >> i) & 1) == 1) {
                if (basis[i] == 0) {
                    basis[i] = x;
                    break;
                }
                x ^= basis[i];
            }
        }
    }

    public static void main(String args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = null;
        
        String line = br.readLine();
        if (line == null) return;
        st = new StringTokenizer(line);
        
        int t = Integer.parseInt(st.nextToken());
        StringBuilder out = new StringBuilder();

        while (t-- > 0) {
            // Read N
            while (!st.hasMoreTokens()) {
                String nextLine = br.readLine();
                if (nextLine == null) break;
                st = new StringTokenizer(nextLine);
            }
            int n = Integer.parseInt(st.nextToken());

            int L = new int[n];
            int R = new int[n];

            // Read array L
            for (int i = 0; i < n; i++) {
                while (!st.hasMoreTokens()) {
                    st = new StringTokenizer(br.readLine());
                }
                L[i] = Integer.parseInt(st.nextToken());
            }

            // Read array R
            for (int i = 0; i < n; i++) {
                while (!st.hasMoreTokens()) {
                    st = new StringTokenizer(br.readLine());
                }
                R[i] = Integer.parseInt(st.nextToken());
            }

            // Basis array for up to 30 bits (size 31)
            int basis = new int;

            for (int i = 0; i < n; i++) {
                int li = L[i];
                int ri = R[i];

                if (li == ri) {
                    insertBasis(basis, li);
                } else {
                    int diff = li ^ ri;
                    // Find highest bit position (0-indexed)
                    int highestBit = 31 - Integer.numberOfLeadingZeros(diff);

                    // Insert all components into the basis
                    for (int b = 0; b <= highestBit; b++) {
                        insertBasis(basis, 1 << b);
                    }
                    insertBasis(basis, li);
                }
            }

            // Greedily maximize the total XOR sum
            int maxEnjoyment = 0;
            for (int i = 30; i >= 0; i--) {
                if ((maxEnjoyment ^ basis[i]) > maxEnjoyment) {
                    maxEnjoyment ^= basis[i];
                }
            }

            out.append(maxEnjoyment).append("\n");
        }
        
        // Output all results at once
        System.out.print(out);
    }
}
