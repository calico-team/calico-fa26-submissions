#include <bits/stdc++.h>
using namespace std;

int main() {
    int testCases;
    scanf("%d", &testCases);

    while (testCases--) {
        int numberOfNodes, numberOfSemesters, dailyLimit;
        scanf("%d %d %d", &numberOfNodes, &numberOfSemesters, &dailyLimit);

        vector<int> parent(numberOfNodes + 1);
        vector<vector<int>> children(numberOfNodes + 1);
        vector<int> rootNodes;

        for (int node = 1; node <= numberOfNodes; node++) {
            scanf("%d", &parent[node]);

            if (parent[node] == 0)
                rootNodes.push_back(node);
            else
                children[parent[node]].push_back(node);
        }

        vector<int> traversalOrder = rootNodes;

        for (size_t index = 0; index < traversalOrder.size(); index++)
            for (int child : children[traversalOrder[index]])
                traversalOrder.push_back(child);

        vector<int> height(numberOfNodes + 1, 1);

        for (int index = (int)traversalOrder.size() - 1; index >= 0; index--) {
            int node = traversalOrder[index];

            for (int child : children[node])
                height[node] = max(height[node], height[child] + 1);
        }

        priority_queue<pair<int, int>> availableNodes;

        for (int root : rootNodes)
            availableNodes.push({height[root], root});

        long long totalTaken = 0;

        for (int semester = 0;
             semester < numberOfSemesters && !availableNodes.empty();
             semester++) {

            vector<int> selectedToday;

            while ((int)selectedToday.size() < dailyLimit &&
                   !availableNodes.empty()) {

                selectedToday.push_back(availableNodes.top().second);
                availableNodes.pop();
            }

            totalTaken += selectedToday.size();

            for (int node : selectedToday)
                for (int child : children[node])
                    availableNodes.push({height[child], child});
        }

        printf("%lld\n", totalTaken);
    }

    return 0;
}
