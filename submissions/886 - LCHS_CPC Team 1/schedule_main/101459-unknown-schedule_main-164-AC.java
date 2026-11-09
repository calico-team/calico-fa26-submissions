import java.util.*;

class Solution {
    /**
     * Return the maximum number of classes that can be taken across M semesters.
     *
     * N: the number of classes
     * M: the number of semesters
     * K: the maximum number of classes you can take per semester
     * P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
     */
    public static int solve(int N, int M, int K, int[] P) {
        int numCourses = N;
        int numSemesters = M;
        int maxPerSemester = K;
        int[] prerequisite = P;

        int[] courseDepth = new int[numCourses + 1];
        for (int course = 1; course <= numCourses; course++) {
            int chainLength = 0;
            int currentCourse = course;
            while (currentCourse != 0) {
                chainLength++;
                currentCourse = prerequisite[currentCourse - 1];
            }
            courseDepth[course] = chainLength;
        }

        int maxChainLength = 1000;
        int[] coursesAtDepth = new int[maxChainLength + 2];
        for (int course = 1; course <= numCourses; course++) {
            coursesAtDepth[courseDepth[course]]++;
        }

        int totalTaken = 0;
        for (int currentDepth = 1;
             currentDepth <= maxChainLength && currentDepth <= numSemesters && coursesAtDepth[currentDepth] > 0;
             currentDepth++) {

            long canTakeAtThisDepth = coursesAtDepth[currentDepth];
            long takenBetween = 0; 

            for (int startDepth = currentDepth; startDepth >= 1; startDepth--) {
                long availableSlots = (long) maxPerSemester * (numSemesters - startDepth + 1);
                canTakeAtThisDepth = Math.min(canTakeAtThisDepth, availableSlots - takenBetween);
                if (startDepth > 1) {
                    takenBetween += coursesAtDepth[startDepth - 1];
                }
            }

            if (canTakeAtThisDepth <= 0) break;
            totalTaken += canTakeAtThisDepth;

            if (canTakeAtThisDepth < coursesAtDepth[currentDepth]) break;
        }

        return totalTaken;
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        if (sc.hasNextInt()) {
            int T = sc.nextInt();
            while (T-- > 0) {
                int N = sc.nextInt();
                int M = sc.nextInt();
                int K = sc.nextInt();
                int[] P = new int[N];
                for (int i = 0; i < N; i++) {
                    P[i] = sc.nextInt();
                }
                System.out.println(solve(N, M, K, P));
            }
        }
        sc.close();
    }
}