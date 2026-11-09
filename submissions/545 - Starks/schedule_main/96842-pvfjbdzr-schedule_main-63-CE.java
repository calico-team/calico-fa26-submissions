import java.io.BufferedReader;

import java.io.InputStreamReader;

import java.io.IOException;

import java.util.Arrays;

import java.util.StringTokenizer;

public class prob6 {

static void main(String[] args) throws IOException {

BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

StringTokenizer st = null;

String firstLine = br.readLine();

if (firstLine == null) return;

int T = Integer.parseInt(firstLine.trim());

StringBuilder out = StringBuilder();

for (int t = 0; t < T; t++) {

while (st == null || !st.hasMoreTokens()) {

st = StringTokenizer(br.readLine());

}

int N = Integer.parseInt(st.nextToken());

int M = Integer.parseInt(st.nextToken());

int K = Integer.parseInt(st.nextToken());

int[] P = new int[N + 1];

int[] inDegree = new int[N + 1];

// A flat adjacency list that keeps track of each courses children.

// headChild[u] is the child of u; nextSibling[v] is the next child after v

int[] headChild = new int[N + 1];

int[] nextSibling = new int[N + 1];

for (int i = 1; i <= N; i++) {

while (st == null || !st.hasMoreTokens()) {

st = StringTokenizer(br.readLine());

}

P[i] = Integer.parseInt(st.nextToken());

if (P[i] != 0) {

inDegree[P[i]]++;

// Link course 'i' as a child of its prerequisite P[i]

nextSibling[i] = headChild[P[i]];

headChild[P[i]] = i;

}

}

// STEP 1: Find the height of each course from the bottom up (starting at leaves)

int[] height = new int[N + 1];

Arrays.fill(height, 1);

int[] queue = new int[N + 1];

int qHead = 0 qTail = 0;

// Add all leaf courses (those that unlock no courses) to the queue

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

// STEP 2: Place currently unlocked courses into buckets based on their height

// bucketHead[h] holds the unlocked course that has height h

int[] bucketHead = new int[maxPossibleHeight. 1];

Int[] nextInBucket = new int[N + 1];

int availableCount = 0;

for (int i = 1; i <= N; i++) {

if (P[i] == 0) { // No prerequisite means the course is unlocked in Semester 1

int h = height[i];

nextInBucket[i] = bucketHead[h];

bucketHead[h] = i;

availableCount++;

}

}

// STEP 3: Run a simulation for up to M semesters always choosing courses in the chains

int totalCoursesTaken = 0;

int currentMaxH = maxPossibleHeight;

int[] pickedThisSemester = int[K];

for (int sem = 0; sem < M && availableCount > 0 && totalCoursesTaken < N; sem++) {

int pickedCount = 0;

// Take up to K unlocked courses beginning with the highest bucket

while (pickedCount < K && availableCount > 0) {

while (currentMaxH > 0 && bucketHead[currentMaxH] == 0) {

currentMaxH--;

}

if (currentMaxH == 0) break;

// Remove course 'u' from the bucket

while (pickedCount < K && availableCount > 0) {

int u = bucketHead[currentMaxH];

if (u == 0) {

break;

}

bucketHead[currentMaxH] = nextInBucket[u];

availableCount--;

// Mark the course as taken

pickedThisSemester[pickedCount++] = u;

totalCoursesTaken++;

// Unlock its child courses

, for (int child = headChild[u]; child != 0; child = nextSibling[child]) {

int h = height[child];

nextInBucket[child] = bucketHead[h];

bucketHead[h] = child;

availableCount++;

}

}

}

}

}

}

}

int u = bucketHead[currentMaxH]; // Get course

bucketHead[currentMaxH] = nextInBucket[u]; // Move to next in bucket

availableCount--; // Decrease available count

pickedThisSemester[pickedCount++] = u; // Store chosen course

totalCoursesTaken++; // Increment total count

}

// Unlock child courses of each taken course for the next semester

for (int i = 0; i < pickedCount; i++) { // Loop over taken courses

int u = pickedThisSemester[i]; // Current course

for (int child = headChild[u]; child != 0; child = nextSibling[child]) { // Loop, over child courses

int h = height[child]; // Height of child

nextInBucket[child] = bucketHead[h]; // Add child to bucket

bucketHead[h] = child; // Update bucket head

// Increase available count

} // End child loop

} // End taken courses loop

} // End outer block

out.append(totalCoursesTaken).append('\n'); // Append result

} // End if or loop

System.out.print(out); // Print output

} // End main

} // End class