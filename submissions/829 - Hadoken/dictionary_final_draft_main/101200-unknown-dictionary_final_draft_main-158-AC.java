import java.util.*;
import java.io.*;

public class Main {
    static int[] child0, child1, trieCount;
    static int totalNodes;

    static void reset() {
        totalNodes = 1;
        child0[0] = 0; child1[0] = 0; trieCount[0] = 0;
    }

    static void insert(int value) {
        int currentNode = 0;
        for (int bitPos = 29; bitPos >= 0; bitPos--) {
            int currentBit = (value >> bitPos) & 1;
            int childNode = currentBit == 0 ? child0[currentNode] : child1[currentNode];
            if (childNode == 0) {
                childNode = totalNodes++;
                child0[childNode] = 0; child1[childNode] = 0; trieCount[childNode] = 0;
                if (currentBit == 0) child0[currentNode] = childNode; else child1[currentNode] = childNode;
            }
            currentNode = childNode;
            trieCount[currentNode]++;
        }
    }

    static void remove(int value) {
        int currentNode = 0;
        for (int bitPos = 29; bitPos >= 0; bitPos--) {
            int currentBit = (value >> bitPos) & 1;
            currentNode = currentBit == 0 ? child0[currentNode] : child1[currentNode];
            trieCount[currentNode]--;
        }
    }

    static int query(int queryVal) {
        int currentNode = 0, maxResult = 0;
        for (int bitPos = 29; bitPos >= 0; bitPos--) {
            int currentBit = (queryVal >> bitPos) & 1;
            int wantedChild = currentBit == 0 ? child1[currentNode] : child0[currentNode];
            if (wantedChild != 0 && trieCount[wantedChild] > 0) {
                maxResult |= 1 << bitPos;
                currentNode = wantedChild;
            } else {
                int otherChild = currentBit == 0 ? child0[currentNode] : child1[currentNode];
                if (otherChild != 0 && trieCount[otherChild] > 0) currentNode = otherChild;
                else return -1;
            }
        }
        return maxResult;
    }

    public static void main(String[] args) throws IOException {
        int maxTrieSize = 30 * 200000 + 64;
        child0 = new int[maxTrieSize];
        child1 = new int[maxTrieSize];
        trieCount = new int[maxTrieSize];

        int testCases = nextInt();
        StringBuilder outBuilder = new StringBuilder();
        while (testCases-- > 0) {
            int numNodes = nextInt();
            int[] parent = new int[numNodes];
            int[] nodeValues = new int[numNodes];
            for (int i = 0; i < numNodes; i++) parent[i] = nextInt() - 1;
            for (int i = 0; i < numNodes; i++) nodeValues[i] = nextInt();

            int[] headEdge = new int[numNodes];
            int[] nextEdge = new int[numNodes];
            Arrays.fill(headEdge, -1);
            for (int node = 0; node < numNodes; node++) {
                nextEdge[node] = headEdge[parent[node]];
                headEdge[parent[node]] = node;
            }

            int[] visitStamp = new int[numNodes];
            Arrays.fill(visitStamp, -1);
            boolean[] isCycleNode = new boolean[numNodes];
            List<int[]> cycleList = new ArrayList<>();
            for (int idx = 0; idx < numNodes; idx++) {
                if (visitStamp[idx] != -1) continue;
                int currNode = idx;
                while (visitStamp[currNode] == -1) {
                    visitStamp[currNode] = idx;
                    currNode = parent[currNode];
                }
                if (visitStamp[currNode] == idx) {
                    int cycleLen = 0;
                    int runner = currNode;
                    do { cycleLen++; runner = parent[runner]; } while (runner != currNode);
                    int[] cycleNodes = new int[cycleLen];
                    runner = currNode;
                    for (int step = 0; step < cycleLen; step++) {
                        cycleNodes[step] = runner;
                        isCycleNode[runner] = true;
                        runner = parent[runner];
                    }
                    cycleList.add(cycleNodes);
                }
            }

            int[] treeXor = new int[numNodes];
            int[] rootPrefix = new int[numNodes];
            int[] cycleBest = new int[numNodes];
            int[] bfsQueue = new int[numNodes];

            // phase 1: cycle contributions
            for (int[] cycle : cycleList) {
                int cycleLen = cycle.length;
                int[] prefixXor = new int[cycleLen + 1];
                for (int k = 0; k < cycleLen; k++) prefixXor[k + 1] = prefixXor[k] ^ nodeValues[cycle[k]];
                int totalCycleXor = prefixXor[cycleLen];
                reset();
                for (int k = 0; k < cycleLen; k++) insert(prefixXor[k]);
                int headIdx = 0, tailIdx = 0;
                for (int k = 0; k < cycleLen; k++) {
                    int cycleVertex = cycle[k];
                    treeXor[cycleVertex] = 0;
                    rootPrefix[cycleVertex] = prefixXor[k];
                    cycleBest[cycleVertex] = Math.max(query(prefixXor[k]), query(prefixXor[k] ^ totalCycleXor));
                    bfsQueue[tailIdx++] = cycleVertex;
                }
                while (headIdx < tailIdx) {
                    int currVertex = bfsQueue[headIdx++];
                    for (int neighbor = headEdge[currVertex]; neighbor != -1; neighbor = nextEdge[neighbor]) {
                        if (isCycleNode[neighbor]) continue;
                        treeXor[neighbor] = nodeValues[neighbor] ^ treeXor[currVertex];
                        rootPrefix[neighbor] = rootPrefix[currVertex];
                        int computedQuery = treeXor[neighbor] ^ rootPrefix[neighbor];
                        cycleBest[neighbor] = Math.max(query(computedQuery), query(computedQuery ^ totalCycleXor));
                        bfsQueue[tailIdx++] = neighbor;
                    }
                }
            }

            int[] finalAns = new int[numNodes];
            reset();
            int[] dfsStack = new int[numNodes];
            int[] edgeIter = new int[numNodes];
            for (int[] cycle : cycleList) {
                for (int cycleRoot : cycle) {
                    finalAns[cycleRoot] = cycleBest[cycleRoot];
                    int stackPtr = 0;
                    dfsStack[stackPtr++] = cycleRoot;
                    edgeIter[cycleRoot] = headEdge[cycleRoot];
                    while (stackPtr > 0) {
                        int curr = dfsStack[stackPtr - 1];
                        int currEdge = edgeIter[curr];
                        while (currEdge != -1 && isCycleNode[currEdge]) currEdge = nextEdge[currEdge];
                        if (currEdge == -1) {
                            stackPtr--;
                            if (curr != cycleRoot) remove(treeXor[curr]);
                        } else {
                            edgeIter[curr] = nextEdge[currEdge];
                            int nxtNode = currEdge;
                            int ancestorResult = query(treeXor[nxtNode]);
                            finalAns[nxtNode] = Math.max(cycleBest[nxtNode], ancestorResult);
                            insert(treeXor[nxtNode]);
                            edgeIter[nxtNode] = headEdge[nxtNode];
                            dfsStack[stackPtr++] = nxtNode;
                        }
                    }
                }
            }

            for (int i = 0; i < numNodes; i++) {
                if (i > 0) outBuilder.append(' ');
                outBuilder.append(finalAns[i]);
            }
            outBuilder.append('\n');
        }
        System.out.print(outBuilder);
    }

    static DataInputStream inputStream = new DataInputStream(new BufferedInputStream(System.in, 1 << 16));

    static int nextInt() throws IOException {
        int number = 0;
        int currByte = inputStream.read();
        while (currByte < '0') currByte = inputStream.read();
        while (currByte >= '0') {
            number = number * 10 + (currByte - '0');
            currByte = inputStream.read();
        }
        return number;
    }
}