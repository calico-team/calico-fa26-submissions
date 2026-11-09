import java.io.*;

class Solution {

    /*
     * Return an array of N integers, the i-th of which
     * represents Big Ben's maximum happiness if he
     * starts by trying to define word i.
     *
     * N: the number of words in the dictionary
     * A: the first word in the definition of word i
     * V: the value associated with the happiness of each word
     */
    static int[] solve(int N, int[] A, int[] V) {
        
        int[] ans = new int[N];
        int[] state = new int[N];
        int[] pos = new int[N];

        Arrays.fill(pos, -1);

        int start = 0;

        while (start < N) {

            if (state[start] != 0) {
                start++;
                continue;
            }

            ArrayList<Integer> path = new ArrayList<>();
            int curr = start;

            while (state[curr] == 0) {
                state[curr] = 1;
                pos[curr] = path.size();
                path.add(curr);
                curr = A[curr] - 1;
            }

            int cycleStart = state[curr] == 1 ? pos[curr] : path.size();

            int xor = 0;

            int i = path.size() - 1;

            while (i >= cycleStart) {
                xor ^= V[path.get(i)];
                i--;
            }

            int cycleXor = xor;

            i = path.size() - 1;

            while (i >= cycleStart) {
                int node = path.get(i);
                ans[node] = cycleXor;
                state[node] = 2;
                i--;
            }

            i = cycleStart - 1;

            while (i >= 0) {
                int node = path.get(i);
                ans[node] = V[node] ^ ans[A[node] - 1];
                state[node] = 2;
                i--;
            }

            start++;
        }

        return ans;
        
    }

    static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    static PrintWriter out = new PrintWriter(System.out);

    public static void main(String[] args) throws IOException {
        int T = Integer.parseInt(in.readLine().trim());

        for (int i = 0; i < T; i++) {
            int N = Integer.parseInt(in.readLine().trim());

            int[] A = new int[N];
            String[] tempA = in.readLine().trim().split(" ");
            for (int j = 0; j < N; j++) {
                A[j] = Integer.parseInt(tempA[j]);
            }

            int[] V = new int[N];
            String[] tempV = in.readLine().trim().split(" ");
            for (int j = 0; j < N; j++) {
                V[j] = Integer.parseInt(tempV[j]);
            }

            int[] ans = solve(N, A, V);
            StringBuilder sb = new StringBuilder();
            for (int j = 0; j < ans.length; j++) {
                sb.append(ans[j]).append(' ');
            }
            out.println(sb);
        }
        out.flush();
    }
}
