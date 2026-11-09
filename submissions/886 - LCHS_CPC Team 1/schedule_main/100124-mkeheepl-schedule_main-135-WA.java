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
        int[] first = new int[N + 1];
        int[] second = new int[N + 1];
        int[] third = new int[N + 1];
        Arrays.fill(first, -1);
        int count = 0;

        int[] availableClasses = new int[N + 1];
        int qfirst = 0;
        int qlast = 0;

        for (int p = 0; p < N; p++) 
        {
            int courseId = p + 1;
            int prerequisite = P[p];

            if (prerequisite == 0)
            {
                availableClasses[qlast++] = courseId;
            } 
            else 
            {
                second[count] = courseId;
                third[count] = first[prerequisite];
                first[prerequisite] = count++;
            }
        }

        int totalCoursesTaken = 0;

        int[] nextSemesterTemp = new int[N + 1];
        
        for (int sem = 1; sem <= M; sem++)
        {
            int availableCount = qlast - qfirst;
            if (availableCount == 0) 
            {
                break;
            }

            int takeThisSemester = Math.min(K, availableCount);
            totalCoursesTaken += takeThisSemester;

            int nextCount = 0;

            for (int i = 0; i < takeThisSemester; i++)
            {
                int currentCourse = availableClasses[qfirst++];

                int edge = first[currentCourse];
                while (edge != -1)
                {
                    int studentCourse = second[edge];
                    nextSemesterTemp[nextCount++] = studentCourse;
                    edge = third[edge];
                }
            }
            
            for (int i = 0; i < nextCount; i++)
            {
                availableClasses[qlast++] = nextSemesterTemp[i];
            }
        }

        return totalCoursesTaken;
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