#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

const int BIT_COUNT = 30;
const int MAX_N = 200005;

static int trieChildren[MAX_N * 31 + 5][2];
static int subtreeCount[MAX_N * 31 + 5];

int totalTrieNodes;

int createTrieNode() {
    trieChildren[totalTrieNodes][0] = 0;
    trieChildren[totalTrieNodes][1] = 0;
    subtreeCount[totalTrieNodes] = 0;

    return totalTrieNodes++;
}

void initializeTrie() {
    totalTrieNodes = 0;
    createTrieNode();
}

void insertTrieValue(int value, int countChange) {
    int currentNode = 0;

    for (int bit = BIT_COUNT - 1; bit >= 0; bit--) {
        int currentBit = (value >> bit) & 1;

        if (!trieChildren[currentNode][currentBit]) {
            int newNode = createTrieNode();
            trieChildren[currentNode][currentBit] = newNode;
        }

        currentNode = trieChildren[currentNode][currentBit];
        subtreeCount[currentNode] += countChange;
    }
}

int getMaximumXor(int value) {
    int currentNode = 0;
    int maximumXor = 0;

    for (int bit = BIT_COUNT - 1; bit >= 0; bit--) {
        int oppositeBit = ((value >> bit) & 1) ^ 1;

        int nextNode = trieChildren[currentNode][oppositeBit];

        if (nextNode && subtreeCount[nextNode] > 0) {
            maximumXor |= (1 << bit);
            currentNode = nextNode;
        }
        else {
            currentNode = trieChildren[currentNode][oppositeBit ^ 1];
        }
    }
   return maximumXor;
}
vector<int> cycleXorCandidates;

// Maximum XOR query on sorted cycle candidates
int getMaximumCycleXor(int value) {

    int leftIndex = 0;
    int rightIndex = (int)cycleXorCandidates.size();

    int maximumXor = 0;

    for (int bitPosition = BIT_COUNT - 1;
         bitPosition >= 0;
         bitPosition--) {

        int middleIndex = partition_point(
            cycleXorCandidates.begin() + leftIndex,
            cycleXorCandidates.begin() + rightIndex,

            [&](int candidate) {
                return !((candidate >> bitPosition) & 1);
            }
        ) - cycleXorCandidates.begin();

        int desiredBit = ((value >> bitPosition) & 1) ^ 1;

        if (desiredBit == 1) {

            if (middleIndex < rightIndex) {
                leftIndex = middleIndex;
                maximumXor |= (1 << bitPosition);
            }
            else {
                rightIndex = middleIndex;
            }

        }
        else {

            if (leftIndex < middleIndex) {
                rightIndex = middleIndex;
                maximumXor |= (1 << bitPosition);
            }
            else {
                leftIndex = middleIndex;
            }
        }
    }

    return maximumXor;
}

int main() {

    // Fast input/output
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int testCases;
    cin >> testCases;

    while (testCases--) {

        int numberOfNodes;
        cin >> numberOfNodes;

        vector<int> nextNode(numberOfNodes);
        vector<int> nodeValue(numberOfNodes);

        // Read graph edges
        for (int i = 0; i < numberOfNodes; i++) {
            cin >> nextNode[i];
            nextNode[i]--;
        }

        // Read node values
        for (int i = 0; i < numberOfNodes; i++) {
            cin >> nodeValue[i];
        }

        // Step 1: Calculate incoming edge counts
        vector<int> incomingEdgeCount(numberOfNodes, 0);

        for (int i = 0; i < numberOfNodes; i++) {
            incomingEdgeCount[nextNode[i]]++;
        }

        // Step 2: Identify tree nodes using indegree peeling
        vector<int> removedNodes;

        for (int i = 0; i < numberOfNodes; i++) {
            if (incomingEdgeCount[i] == 0) {
                removedNodes.push_back(i);
            }
        }

        vector<char> isTreeNode(numberOfNodes, 0);

        for (size_t i = 0; i < removedNodes.size(); i++) {

            int currentNode = removedNodes[i];

            isTreeNode[currentNode] = 1;

            int destination = nextNode[currentNode];

            incomingEdgeCount[destination]--;

            if (incomingEdgeCount[destination] == 0) {
                removedNodes.push_back(destination);
            }
        }

        // Step 3: Construct reverse trees
        vector<int> firstChild(numberOfNodes, -1);
        vector<int> nextSibling(numberOfNodes, -1);

        for (int i = 0; i < numberOfNodes; i++) {

            if (isTreeNode[i]) {
                int parent = nextNode[i];

                nextSibling[i] = firstChild[parent];
                firstChild[parent] = i;
            }
        }

        // Step 4: Initialize answer arrays
        vector<int> answer(numberOfNodes, 0);
        vector<int> treePathXor(numberOfNodes, 0);

        vector<char> visited(numberOfNodes, 0);

        // Step 5: Process cycles
        for (int startNode = 0;
             startNode < numberOfNodes;
             startNode++) {

            if (isTreeNode[startNode] || visited[startNode]) {
                continue;
            }

            // Extract cycle
            vector<int> cycleNodes;

            int currentNode = startNode;

            while (!visited[currentNode]) {
                visited[currentNode] = 1;
                cycleNodes.push_back(currentNode);
                currentNode = nextNode[currentNode];
            }

            int cycleLength = (int)cycleNodes.size();

            // Step 6: Calculate prefix XOR
            vector<int> cyclePrefixXor(cycleLength + 1, 0);

            for (int i = 0; i < cycleLength; i++) {
                cyclePrefixXor[i + 1] =
                    cyclePrefixXor[i] ^
                    nodeValue[cycleNodes[i]];
            }

            int totalCycleXor = cyclePrefixXor[cycleLength];

            // Step 7: Generate cycle XOR candidates
            cycleXorCandidates.clear();

            for (int i = 0; i < cycleLength; i++) {
                cycleXorCandidates.push_back(cyclePrefixXor[i]);

                cycleXorCandidates.push_back(
                    cyclePrefixXor[i] ^ totalCycleXor
                );
            }

            sort(
                cycleXorCandidates.begin(),
                cycleXorCandidates.end()
            );

            // Step 8: Process each cycle root
            for (int cycleIndex = 0;
                 cycleIndex < cycleLength;
                 cycleIndex++) {

                int cycleRoot = cycleNodes[cycleIndex];

                answer[cycleRoot] =
                    getMaximumCycleXor(
                        cyclePrefixXor[cycleIndex]
                    );

                if (firstChild[cycleRoot] == -1) {
                    continue;
                }

                // Step 9: Initialize Trie
                initializeTrie();

                treePathXor[cycleRoot] = 0;

                insertTrieValue(0, 1);

                // Step 10: Iterative DFS
                vector<pair<int, int>> dfsStack;

                dfsStack.push_back({
                    cycleRoot,
                    firstChild[cycleRoot]
                });

                while (!dfsStack.empty()) {

                    auto &stackTop = dfsStack.back();

                    int childNode = stackTop.second;

                    // Backtracking
                    if (childNode == -1) {

                        int finishedNode = stackTop.first;

                        dfsStack.pop_back();

                        if (finishedNode != cycleRoot) {
                            insertTrieValue(
                                treePathXor[finishedNode],
                                -1
                            );
                        }

                        continue;
                    }

                    // Move to next sibling
                    stackTop.second = nextSibling[childNode];

                    // Calculate path XOR
                    treePathXor[childNode] =
                        nodeValue[childNode] ^
                        treePathXor[nextNode[childNode]];

                    // Calculate answer
                    answer[childNode] = max(
                        getMaximumXor(
                            treePathXor[childNode]
                        ),
                        getMaximumCycleXor(
                            treePathXor[childNode] ^
                            cyclePrefixXor[cycleIndex]
                        )
                    );

                    // Insert current path XOR
                    insertTrieValue(
                        treePathXor[childNode],
                        1
                    );

                    // Explore children
                    dfsStack.push_back({
                        childNode,
                        firstChild[childNode]
                    });
                }
            }
        }

        for (int i = 0; i < numberOfNodes; i++) {
            cout << answer[i];

            if (i + 1 < numberOfNodes) {
                cout << ' ';
            }
        }

        cout << '\n';
    }

    return 0;
}
