import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        StreamTokenizer tok = new StreamTokenizer(new BufferedReader(new InputStreamReader(System.in)));
        tok.nextToken();
        int testCases = (int) tok.nval;

        StringBuilder output = new StringBuilder();

        while (testCases-- > 0) {
            tok.nextToken();
            int numCourses = (int) tok.nval;
            tok.nextToken();
            int numSemesters = (int) tok.nval;
            tok.nextToken();
            int maxCoursesPerSem = (int) tok.nval;
            int[] firstChild = new int[numCourses + 1];
            int[] nextSibling = new int[numCourses + 1];
            Arrays.fill(firstChild, -1);

            for (int i = 1; i <= numCourses; i++) {
                tok.nextToken();
                int prereq = (int) tok.nval;
                nextSibling[i] = firstChild[prereq];
                firstChild[prereq] = i;
            }
            int[] bfsOrder = new int[numCourses + 1];
            int head = 0, tail = 0;
            bfsOrder[tail++] = 0;

            while (head < tail) {
                int currCourse = bfsOrder[head++];
                for (int child = firstChild[currCourse]; child != -1; child = nextSibling[child]) {
                    bfsOrder[tail++] = child;
                }
            }

            int[] chainHeight = new int[numCourses + 1];
            for (int i = tail - 1; i >= 1; i--) {
                int currCourse = bfsOrder[i];
                int maxChain = 1;
                for (int child = firstChild[currCourse]; child != -1; child = nextSibling[child]) {
                    maxChain = Math.max(maxChain, chainHeight[child] + 1);
                }
                chainHeight[currCourse] = maxChain;
            }

            PriorityQueue<Integer> availableCourses = new PriorityQueue<>((a, b) -> chainHeight[b] - chainHeight[a]);
            for (int child = firstChild[0]; child != -1; child = nextSibling[child]) {
                availableCourses.add(child);
            }

            long totalCoursesTaken = 0;
            int[] selectedCourses = new int[maxCoursesPerSem];

            for (int semester = 0; semester < numSemesters && !availableCourses.isEmpty(); semester++) {
                int coursesTakenCount = 0;
                while (coursesTakenCount < maxCoursesPerSem && !availableCourses.isEmpty()) {
                    selectedCourses[coursesTakenCount++] = availableCourses.poll();
                }

                totalCoursesTaken += coursesTakenCount;

                for (int i = 0; i < coursesTakenCount; i++) {
                    int completedCourse = selectedCourses[i];
                    for (int child = firstChild[completedCourse]; child != -1; child = nextSibling[child]) {
                        availableCourses.add(child);
                    }
                }
            }

            output.append(totalCoursesTaken).append('\n');
        }

        System.out.print(output);
    }
}