import java.util.*;

class Schedule {
    /**
     * Return the maximum number of classes that can be taken across M semesters.
     *
     * N: the number of classes
     * M: the number of semesters
     * K: the maximum number of classes you can take per semester
     * P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
     */
    public static int solve(int N, int M, int K, int[] P) {
        int n = 0;
        int z = 0;
        List<Integer> k = new ArrayList<>();
        k.add(0);
        List<Integer> k2 = new ArrayList<>();
        for(int i = 0; i<M; i++){
            for(int j = 0; j<N; j++){
                if(z<K){
                    if(k.contains(P[j])){
                        n += 1;
                        k2.add(j);
                    }
                }
            }
            k.addAll(k2);
        }
        return n;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        for(int f = 0; f<T; f++){
            int N = sc.nextInt();
            int M = sc.nextInt();
            int K = sc.nextInt();
            int[] P = new int[N];
            for (int i = 0; i < N; i++) {
                P[i] = sc.nextInt();
            }
            System.out.println();
            System.out.println(solve(N,M,K,P));
        }
        sc.close();
    }
}
