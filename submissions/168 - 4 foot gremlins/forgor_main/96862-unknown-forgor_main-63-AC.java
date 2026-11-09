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
        ArrayList<ArrayList<Integer>> adj = new ArrayList<>();
        for (int i = 0; i <= N; i++){
            adj.add(new ArrayList<>());
        }
        for (int e[]:E){
            adj.get(e[0]).add(e[1]);
            adj.get(e[1]).add(e[0]);
        }
        int[] parent = new int[N+1];
        boolean[] seen = new boolean[N+1];
        ArrayDeque<Integer> q = new ArrayDeque<>();
        q.add(1);
        seen[1] = true;
        while (!q.isEmpty()){
            int u = q.poll();
            for (int v:adj.get(u)){
                if (!seen[v]){
                    seen[v]=true;
                    parent[v]=u;
                    q.add(v);
                }
            }
        }
        int[] ans = new int[N];
        long sum = 0;
        for (int i = 2; i <= N; i++){
            ans[i-1] = parent[i];
            sum += parent[i];
        }
        ans[0] = modulo(sum,N);
        return ans;
    }
    /**
     * Output the N - 1 edges of the original tree as (u, v) pairs
     *
     * N: the number of vertices
     * A: the N integers A_1 .. A_N with one value replaced with -1
     */
    static int[][] solve_phase2(int N, int[] A) {
        // YOUR CODE HERE
        int missing = -1;
        for (int i = 0; i < N; i++){
            if (A[i]==-1){
                missing=i;
                break;
            }
        }
        if (missing>0){
            long others = 0;
            for (int i = 1; i < N; i++){
                if (i!=missing){
                    others+=A[i];
                }
            }
            A[missing]=modulo(A[0]-others,N);
        }
        int[][] edges = new int[N-1][2];
        for(int i = 2; i<=N; i++){
            edges[i-2][0]=i;
            edges[i-2][1]=A[i-1];
        }
        return edges;
    }

    static int modulo(long x, int N){
        int r = (int)(((x%N)+N)%N);
        if (r==0){
            return N;
        }else{
            return r;
        }
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
