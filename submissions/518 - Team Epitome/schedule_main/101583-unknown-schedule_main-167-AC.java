import java.util.*;

class Solution
{
    public static int solve(int N, int M, int K, int[] P)
    {
        @SuppressWarnings("unchecked")
        List<Integer>[] nextCourses = (List<Integer>[]) new ArrayList[N + 1];
        for (int idx = 1; idx <= N; idx++)
        {
            nextCourses[idx] = new ArrayList<>();
        }

        int[] prereqCount = new int[N + 1];
        for (int idx = 0; idx < N; idx++)
        {
            int current = idx + 1;
            int required = P[idx];
            if (required != 0)
            {
                nextCourses[required].add(current);
                prereqCount[current]++;
            }
        }

        int[] chainLen = new int[N + 1];
        for (int idx = 1; idx <= N; idx++)
        {
            computeChain(idx, nextCourses, chainLen);
        }

        PriorityQueue<Integer> readyQueue = new PriorityQueue<>((p, q) -> Integer.compare(chainLen[q], chainLen[p]));
        for (int idx = 1; idx <= N; idx++)
        {
            if (prereqCount[idx] == 0)
            {
                readyQueue.add(idx);
            }
        }

        int answer = 0;
        List<Integer> picked = new ArrayList<>();
        for (int term = 0; term < M; term++)
        {
            if (readyQueue.isEmpty())
                break;

            int howMany = Math.min(K, readyQueue.size());
            answer += howMany;

            picked.clear();
            for (int j = 0; j < howMany; j++)
            {
                picked.add(readyQueue.poll());
            }

            for (int done : picked)
            {
                for (int unlocked : nextCourses[done])
                {
                    readyQueue.add(unlocked);
                }
            }
        }
        return answer;
    }

    private static int computeChain(int node, List<Integer>[] nextCourses, int[] chainLen)
    {
        if (chainLen[node] > 0)
        {
            return chainLen[node];
        }
        int longest = 0;
        for (int child : nextCourses[node])
            longest = Math.max(longest, computeChain(child, nextCourses, chainLen));
        chainLen[node] = 1 + longest;
        return chainLen[node];
    }

    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        while (T-- > 0)
        {
            int N = sc.nextInt();
            int M = sc.nextInt();
            int K = sc.nextInt();
            int[] P = new int[N];
            for (int i = 0; i < N; i++)
            {
                P[i] = sc.nextInt();
            }
            System.out.println(solve(N, M, K, P));
        }
        sc.close();
    }
}