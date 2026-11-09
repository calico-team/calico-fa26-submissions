import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.*;

class Main {
    /**
     * Return the maximum number of classes that can be taken across M semesters.
     *
     * N: the number of classes
     * M: the number of semesters
     * K: the maximum number of classes you can take per semester
     * P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
     */
    public static int solve(int N, int M, int K, int[] P) {
        ArrayList<Integer>[] graph = new ArrayList[N];
        for(int i = 0; i < N; i++) graph[i] = new ArrayList<>();
       
        int[] prereq= new int[N];

        for(int i = 0; i < N; i++) {
            if(P[i] != 0 ) {
                graph[P[i]-1].add(i);
                prereq[i]++;
            }
        }

        int[] depth = new int[N];
        for(int i = 0; i < N; i++) {
            if(prereq[i] == 0) dfs(i, graph, depth);
        }

        PriorityQueue<Integer> courses = new PriorityQueue<>((a,b) -> Integer.compare(depth[b], depth[a]));

        for(int i = 0; i < N; i++) {
            if(prereq[i] == 0) courses.add(i);
        }

        int returned = 0;

        for(int i = 0; i < M; i++) {
            ArrayList<Integer> taken = new ArrayList<>();

            while(!courses.isEmpty() && taken.size() < K) {
                taken.add(courses.poll());
                returned++;
            }

            for(int u : taken) {
                for(int v : graph[u]) {
                    prereq[v]--;
                    if(prereq[v] == 0) courses.add(v);
                }
            }
        }

        return returned;
    }

    public static int dfs(int u, List<Integer>[] graph, int[] depth) {
        if(depth[u] != 0) return depth[u];

        int d = 1;
        for(int v : graph[u]) d = Math.max(d+1, dfs(v, graph, depth));

        depth[u] = d;
        return d;
    }

    static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    static PrintWriter out = new PrintWriter(System.out);

    public static void main(String[] args) throws IOException {
        int T = Integer.parseInt(in.readLine());
        while (T-- > 0) {
            String[] temp = in.readLine().split(" ");
            int N = Integer.parseInt(temp[0]);
            int M = Integer.parseInt(temp[1]);
            int K = Integer.parseInt(temp[2]);
            int[] P = new int[N];
            temp = in.readLine().split(" ");
            for (int i = 0; i < N; i++) {
                P[i] = Integer.parseInt(temp[i]);
            }
            out.println(solve(N, M, K, P));
        }
        out.flush();
    }
}