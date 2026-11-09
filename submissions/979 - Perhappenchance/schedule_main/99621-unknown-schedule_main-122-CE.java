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
        int answer = 0;
        // make list of prerequisites
        int prenum = P.length;
        /*
        ArrayList<Integer> pres = new ArrayList<Integer>();
        for (int i = 0; i < P.length; i++){
            if (!pres.contains(P[i])){
                pres.add(P[i]);
            }
        }
        */
        // count prerequisites
        int nonpres = N - prenum;
        int presems = prenum / K;
        int extrapres = prenum % K;
        int extrasems = (nonpres + extrapres) / K;
        int extras = (nonpres + extrapres) % K;
        int add;
        if (extras == 0){
            add = 0;
        }
        else {
            add = 1;
        }
        int totalsems = presems + extrasems + add;


        System.out.println(Math.min(totalsems, M));
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