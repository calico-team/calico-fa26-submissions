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

        ArrayList<Integer> freeClasses = new ArrayList<>();
        ArrayList<ArrayList<Integer>> depth = new ArrayList<>();

        for(int i = 0; i < N; i++) {
            if(P[i] == 0) freeClasses.add(i);
            else {
                graph[P[i-1]].add(i);
            }
        }

        ArrayList<Integer> currentLevel = freeClasses;
        while (!currentLevel.isEmpty()) {
            depth.add(currentLevel);
            ArrayList<Integer> nextLevel = new ArrayList<>();
            
           for (int u : currentLevel) {
                for (int v : graph[u]) nextLevel.add(v);
            }
            currentLevel = nextLevel;
        }

        int returned = 0;
        int currentDepth = 0;

        for(int i = 0; i < M; i++) {
            for(int j = 0; j < K; j++) {
                if(currentDepth < depth.size() && currentDepth <= i) {
                    returned++;
                    depth.get(currentDepth).removeFirst();
                    if(depth.get(currentDepth).size() == 0) currentDepth++;
                }
            }
        }

        return returned;
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