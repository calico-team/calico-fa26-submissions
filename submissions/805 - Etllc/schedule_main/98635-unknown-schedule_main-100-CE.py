#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int testCases;
    cin >> testCases;

    while (testCases--) {
        int n, semesters, limit;
        cin >> n >> semesters >> limit;

        vector<int> prerequisite(n + 1);
        vector<vector<int>> nextCourse(n + 1);

        for (int course = 1; course <= n; ++course) {
            cin >> prerequisite[course];
            if (prerequisite[course] != 0) {
                nextCourse[prerequisite[course]].push_back(course);
            }
        }

        queue<int> available;
        for (int course = 1; course <= n; ++course) {
            if (prerequisite[course] == 0) {
                available.push(course);
            }
        }

        int completed = 0;

        for (int semester = 0;
             semester < semesters && !available.empty();
             ++semester) {
            int coursesThisSemester = min(limit, static_cast<int>(available.size()));
            vector<int> taken;

            for (int i = 0; i < coursesThisSemester; ++i) {
                taken.push_back(available.front());
                available.pop();
            }

            completed += coursesThisSemester;

            for (int course : taken) {
                for (int following : nextCourse[course]) {
                    available.push(following);
                }
            }
        }

        cout << completed << '\n';
    }

    return 0;
}