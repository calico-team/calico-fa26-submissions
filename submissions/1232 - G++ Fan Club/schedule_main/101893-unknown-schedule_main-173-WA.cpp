#include <bits/stdc++.h>

using namespace std;

struct course
{
    int i;
    int prqs;

    bool operator<(const course& c) const
    {
        return prqs < c.prqs;
    }
};

int getDepth(int i, vector<int>& prqs, vector<vector<int>>& courses)
{
    int depth{1};
    for (int course : courses[i])
    {
        depth = max(depth, getDepth(course, prqs, courses) + 1);
    }

    return depth;
}


int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        int n, m, k;
        cin >> n >> m >> k;

        vector<vector<int>> courses(n);
        vector<int> base;

        for (int i{}; i < n; i++)
        {
            int prq;
            cin >> prq;

            if (prq == 0)
            {
                base.push_back(i);
            }
            else
            {
                courses[prq - 1].push_back(i);
            }
        }

        vector<int> prqs(n, -1);
        for (int i{}; i < n; i++)
        {
            getDepth(i, prqs, courses);
        }

        priority_queue<course> priorityCourses;

        for (int i : base)
        {
            priorityCourses.push({i, prqs[i]});
        }

        int total{};

        for (int i{}; i < m; i++)
        {
            vector<course> available;
            for (int j{}; j < k && !priorityCourses.empty(); j++)
            {
                total++;

                for (int course : courses[priorityCourses.top().i])
                {
                    available.push_back({course, prqs[course]});
                }

                priorityCourses.pop();
            }

            for (course course : available)
            {
                priorityCourses.push(course);
            }
        }

        cout << total << endl;
    }

    return 0;
}