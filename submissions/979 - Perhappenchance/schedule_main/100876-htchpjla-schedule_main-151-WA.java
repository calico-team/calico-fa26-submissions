import java.util.*;

class SolutionSchedule {
    /**
     * Return the maximum number of classes that can be taken across M semesters.
     *
     * N: the number of classes
     * M: the number of semesters
     * K: the maximum number of classes you can take per semester
     * P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
     */
    public static int solve(int N, int M, int K, int[] P) {
        // YOUR CODE HERE
        int count = 0;
        ArrayList<Integer> taken = new ArrayList<Integer>();
        ArrayList<Integer> options = new ArrayList<Integer>();
        for (int i = 0; i < M; i++){
            //get possible classes
            options = new ArrayList<Integer>();
            for (int j = 0; j < P.length; j++){
                if (P[j] == 0 || taken.contains(P[j])){
                    options.add(j);
                }
            }
            // sort possibles by amount unlocked
            options.sort((a, b) -> {
                int c = 0;
                for (int p = 0; p < P.length; p++){
                    if (P[p] == a){
                        c++;
                    } else if (P[p] == b){
                        c--;
                    }
                }
                if (c < 0){
                    return -1;
                } else if (c > 0){
                    return 1;
                } else {
                    return 0;
                }
            });
            // take classes
            for (int j = 0; j < K && options.size() > 0; j++){
                taken.add(options.remove(0));
                count++;
            }
        }
        System.out.println(count);
        return -1;
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