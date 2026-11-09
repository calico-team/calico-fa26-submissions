import java.io.*;
import java.util.*;

public class Main {
    @SuppressWarnings("unchecked")
    public static void main(String[] args) throws IOException {
        StreamTokenizer tok = new StreamTokenizer(new BufferedReader(new InputStreamReader(System.in)));
        tok.nextToken();
        int testCases = (int) tok.nval;

        StringBuilder sb = new StringBuilder();

        while (testCases-- > 0) {
            tok.nextToken();
            int numCourses = (int) tok.nval;
            tok.nextToken();
            int numSemesters = (int) tok.nval;
            tok.nextToken();
            int maxPerSem = (int) tok.nval;

            int[] prereq = new int[numCourses + 1];
            List<Integer>[] dependents = new ArrayList[numCourses + 1];
            for (int i = 0; i <= numCourses; i++) {
                dependents[i] = new ArrayList<>();
            }

            for (int i = 1; i <= numCourses; i++) {
                tok.nextToken();
                prereq[i] = (int) tok.nval;
                dependents[prereq[i]].add(i);
            }

            int[] bfsOrder = new int[numCourses + 1];
            int head = 0, tail = 0;
            bfsOrder[tail++] = 0;

            while (head < tail) {
                int currCourse = bfsOrder[head++];
                for (int nextCourse : dependents[currCourse]) {
                    bfsOrder[tail++] = nextCourse;
                }
            }

            int[] chainHeight = new int[numCourses + 1];
            for (int i = tail - 1; i >= 1; i--) {
                int currCourse = bfsOrder[i];
                int maxChain = 1;
                for (int nextCourse : dependents[currCourse]) {
                    maxChain = Math.max(maxChain, chainHeight[nextCourse] + 1);
                }
                chainHeight[currCourse] = maxChain;
            }

            PriorityQueue<Integer> availableCourses = new PriorityQueue<>((a, b) -> chainHeight[b] - chainHeight[a]);
            for (int nextCourse : dependents[0]) {
                availableCourses.add(nextCourse);
            }

            long totalTaken = 0;
            List<Integer> takenThisSemester = new ArrayList<>();

            for (int semester = 0; semester < numSemesters && !availableCourses.isEmpty(); semester++) {
                takenThisSemester.clear();
                for (int slot = 0; slot < maxPerSem && !availableCourses.isEmpty(); slot++) {
                    takenThisSemester.add(availableCourses.poll());
                }
                totalTaken += takenThisSemester.size();

                for (int completedCourse : takenThisSemester) {
                    for (int unlockedCourse : dependents[completedCourse]) {
                        availableCourses.add(unlockedCourse);
                    }
                }
            }

            sb.append(totalTaken).append('\n');
        }

        System.out.print(sb);
    }
}