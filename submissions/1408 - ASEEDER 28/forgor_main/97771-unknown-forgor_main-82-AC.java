import java.io.*;
import java.util.*;

class Solution {

    static int[] solve_phase1(int N, int[][] E) {
        return amnesiac_encode(N, E);
    }

    
    static int[][] solve_phase2(int N, int[] A) {
        return amnesiac_decode(N, A);
    }

    // Root at 1: A[i] = parent(i+1) for i >= 1, A[0] = XOR of all parents.
    static int[] amnesiac_encode(int N, int[][] E) {
        @SuppressWarnings("unchecked")
        ArrayList<Integer>[] g = new ArrayList[N + 1];
        for (int i = 1; i <= N; i++) g[i] = new ArrayList<>();
        for (int[] e : E) {
            g[e[0]].add(e[1]);
            g[e[1]].add(e[0]);
        }

        int[] parent = new int[N + 1];
        int[] q = new int[N];
        int qh = 0, qt = 0;
        q[qt++] = 1;
        parent[1] = 0;
        while (qh < qt) {
            int u = q[qh++];
            for (int v : g[u]) {
                if (v == parent[u]) continue;
                if (parent[v] != 0 || v == 1) continue;
                parent[v] = u;
                q[qt++] = v;
            }
        }

        int[] A = new int[N];
        int xor = 0;
        for (int i = 2; i <= N; i++) {
            A[i - 1] = parent[i];
            xor ^= parent[i];
        }
        A[0] = xor;
        return A;
    }

    static int[][] amnesiac_decode(int N, int[] A) {
        int miss = -1;
        for (int i = 0; i < N; i++) {
            if (A[i] == -1) {
                miss = i;
                break;
            }
        }

        if (miss != 0) {
            int xor = A[0];
            for (int i = 1; i < N; i++) {
                if (i != miss) xor ^= A[i];
            }
            A[miss] = xor;
        }

        int[][] edges = new int[N - 1][2];
        for (int i = 1; i < N; i++) {
            edges[i - 1][0] = i + 1;
            edges[i - 1][1] = A[i];
        }
        return edges;
    }

    static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    static PrintWriter out = new PrintWriter(System.out);

    public static void main(String[] args) throws IOException {
        String phase = in.readLine().trim();
        int N = Integer.parseInt(in.readLine().trim());

        if (phase.equals("FIRST")) {
            int[][] E = new int[N - 1][2];
            for (int i = 0; i < N - 1; i++) {
                String[] temp = in.readLine().trim().split(" ");
                E[i][0] = Integer.parseInt(temp[0]);
                E[i][1] = Integer.parseInt(temp[1]);
            }
            int[] A = solve_phase1(N, E);
            for (int i = 0; i < N; i++) {
                if (i > 0) out.print(' ');
                out.print(A[i]);
            }
            out.println();
        } else {
            String[] temp = in.readLine().trim().split(" ");
            int[] A = new int[N];
            for (int i = 0; i < N; i++) {
                A[i] = Integer.parseInt(temp[i]);
            }
            int[][] edges = solve_phase2(N, A);
            for (int i = 0; i < edges.length; i++) {
                out.println(edges[i][0] + " " + edges[i][1]);
            }
        }
        out.flush();
    }

    static void read_your_input() throws IOException {
        in.readLine();
    }
}
