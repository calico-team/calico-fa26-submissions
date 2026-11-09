import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.Arrays;
import java.util.StringTokenizer;

public class prob6sol{
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = null;

        String firstLine = br.readLine();
        if (firstLine == null) return;
        int T = Integer.parseInt(firstLine.trim());

        StringBuilder out = new StringBuilder();

        for (int t = 0; t < T; t++) {
            while (st == null || !st.hasMoreTokens()) {
                st = new StringTokenizer(br.readLine());
            }
            int N = Integer.parseInt(st.nextToken());
            int M = Integer.parseInt(st.nextToken());
            int K = Integer.parseInt(st.nextToken());

            int[] P = new int[N + 1];
            int[] inDegree = new int[N + 1];

            // Flat adjacency list to store the children of each course:
            // headChild[u] holds the first child of u; nextSibling[v] holds the next child of u
            int[] headChild = new int[N + 1];
            int[] nextSibling = new int[N + 1];

            for (int i = 1; i <= N; i++) {
                while (st == null || !st.hasMoreTokens()) {
                    st = new StringTokenizer(br.readLine());
                }
                P[i] = Integer.parseInt(st.nextToken());
                if (P[i] != 0) {
                    inDegree[P[i]]++;
                    // Attach course 'i' to the linked list of children for P[i]
                    nextSibling[i] = headChild[P[i]];
                    headChild[P[i]] = i;
                }
            }

            // STEP 1: Compute the chain height of every course bottom-up (leaves -> roots)
            int[] height = new int[N + 1];
            Arrays.fill(height, 1);

            int[] queue = new int[N + 1];
            int qHead = 0, qTail = 0;

            // Push all leaf courses (courses that unlock nothing else) into the queue
            for (int i = 1; i <= N; i++) {
                if (inDegree[i] == 0) {
                    queue[qTail++] = i;
                }
            }

            int maxPossibleHeight = 1;
            while (qHead < qTail) {
                int u = queue[qHead++];
                int p = P[u];
                if (p != 0) {
                    if (height[u] + 1 > height[p]) {
                        height[p] = height[u] + 1;
                        if (height[p] > maxPossibleHeight) {
                            maxPossibleHeight = height[p];
                        }
                    }
                    inDegree[p]--;
                    if (inDegree[p] == 0) {
                        queue[qTail++] = p;
                    }
                }
            }

            // STEP 2: Group currently unlocked courses into buckets by their height
            // bucketHead[h] stores the first unlocked course of height h
            int[] bucketHead = new int[maxPossibleHeight + 1];
            int[] nextInBucket = new int[N + 1];
            int availableCount = 0;

            for (int i = 1; i <= N; i++) {
                if (P[i] == 0) { // No prerequisite = unlocked in Semester 1
                    int h = height[i];
                    nextInBucket[i] = bucketHead[h];
                    bucketHead[h] = i;
                    availableCount++;
                }
            }

            // STEP 3: Simulate up to M semesters, greedily picking the tallest chains first
            int totalCoursesTaken = 0;
            int currentMaxH = maxPossibleHeight;
            int[] pickedThisSemester = new int[K];

            for (int sem = 0; sem < M && availableCount > 0 && totalCoursesTaken < N; sem++) {
                int pickedCount = 0;

                // Pick up to K unlocked courses starting from the highest bucket
                while (pickedCount < K && availableCount > 0) {
                    while (currentMaxH > 0 && bucketHead[currentMaxH] == 0) {
                        currentMaxH--;
                    }
                    if (currentMaxH == 0) break;

                    // Pop course 'u' from bucketHead[currentMaxH]
                    int u = bucketHead[currentMaxH];
                    bucketHead[currentMaxH] = nextInBucket[u];
                    availableCount--;

                    pickedThisSemester[pickedCount++] = u;
                    totalCoursesTaken++;
                }

                // Unlock the children of all courses taken in this semester for the NEXT semester
                for (int i = 0; i < pickedCount; i++) {
                    int u = pickedThisSemester[i];
                    for (int child = headChild[u]; child != 0; child = nextSibling[child]) {
                        int h = height[child];
                        nextInBucket[child] = bucketHead[h];
                        bucketHead[h] = child;
                        availableCount++;
                    }
                }
            }

            out.append(totalCoursesTaken).append('\n');
        }

        System.out.print(out);
    }
}