import java.io.*;
import java.util.*;

class Solution {
    /**
    * Output a list of N integers A_1 .. A_N
    *
    * N: the number of vertices
    * E: the N - 1 edges of the tree as (u, v) pairs
    */
    static int[] solve_phase1(int N, int[][] E) {
        List<List<Integer>> graph = new ArrayList<>();
        int[] degree = new int[N + 1];

        for (int i = 0; i <= N; i++) {
            graph.add(new ArrayList<>());
        }

        for (int[] edge : E) {
            int u = edge[0];
            int v = edge[1];
            graph.get(u).add(v);
            graph.get(v).add(u);
            degree[u]++;
            degree[v]++;
        }

        PriorityQueue<Integer> leaves = new PriorityQueue<>();
        for (int i = 1; i <= N; i++) {
            if (degree[i] == 1) {
                leaves.offer(i);
            }
        }

        int[] answer = new int[N];
        long checksum = 0;
        int mod = 999983;

        for (int i = 0; i < N - 2; i++) {
            int leaf = leaves.poll();
            int neighbor = 0;

            for (int next : graph.get(leaf)) {
                if (degree[next] > 0) {
                    neighbor = next;
                    break;
                }
            }

            answer[i] = neighbor;
            checksum = (checksum + neighbor) % mod;
            degree[leaf] = 0;
            degree[neighbor]--;

            if (degree[neighbor] == 1) {
                leaves.offer(neighbor);
            }
        }

        answer[N - 2] = (int) checksum;
        answer[N - 1] = 0;
        return answer;
    }

    /**
    * Output the N - 1 edges of the original tree as (u, v) pairs
    *
    * N: the number of vertices
    * A: the N integers A_1 .. A_N with one value replaced with -1
    */
    static int[][] solve_phase2(int N, int[] A) {
        int mod = 999983;
        int missing = -1;

        for (int i = 0; i < N; i++) {
            if (A[i] == -1) {
                missing = i;
                break;
            }
        }

        if (missing < N - 2) {
            long sum = 0;
            for (int i = 0; i < N - 2; i++) {
                if (i != missing) {
                    sum += A[i];
                }
            }
            A[missing] = (int) ((A[N - 2] - sum % mod + mod) % mod);
        }

        int[] degree = new int[N + 1];
        Arrays.fill(degree, 1);
        degree[0] = 0;

        for (int i = 0; i < N - 2; i++) {
            degree[A[i]]++;
        }

        PriorityQueue<Integer> leaves = new PriorityQueue<>();
        for (int i = 1; i <= N; i++) {
            if (degree[i] == 1) {
                leaves.offer(i);
            }
        }

        int[][] edges = new int[N - 1][2];

        for (int i = 0; i < N - 2; i++) {
            int leaf = leaves.poll();
            int neighbor = A[i];
            edges[i][0] = leaf;
            edges[i][1] = neighbor;

            degree[leaf]--;
            degree[neighbor]--;
            if (degree[neighbor] == 1) {
                leaves.offer(neighbor);
            }
        }

        edges[N - 2][0] = leaves.poll();
        edges[N - 2][1] = leaves.poll();
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
}
