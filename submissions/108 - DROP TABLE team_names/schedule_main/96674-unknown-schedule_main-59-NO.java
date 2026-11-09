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

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        while (T-- > 0) {
            int N = sc.nextInt();
            int M = sc.nextInt();
            int K = sc.nextInt();
            int[] P = new int[N];
            for (int i = 0; i < N; i++) {
                P[i] = sc.nextInt();
            }
            solve(N, M, K, P);
        }
        sc.close();
    }
}