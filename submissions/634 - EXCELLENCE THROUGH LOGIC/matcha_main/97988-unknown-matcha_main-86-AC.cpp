#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int mergeLimits(int a, int b)
{
    if (a < b)
        swap(a, b);
    int out = 0;
    while (a > 0)
    {
        int topPow = 1 << (31 - __builtin_clz(a));
        if (b >= topPow)
            return out | (2 * topPow - 1);
        out |= topPow;
        a -= topPow;
        if (a < b)
            swap(a, b);
    }
    return out;
}

int main()
{
    int tests;
    scanf("%d", &tests);
    vector<int> bigLim[30], smallLim[30];

    while (tests--)
    {
        int days;
        scanf("%d", &days);
        vector<int> lo(days), hi(days);
        for (int i = 0; i < days; i++)
            scanf("%d", &lo[i]);
        for (int i = 0; i < days; i++)
            scanf("%d", &hi[i]);

        for (int lvl = 0; lvl < 30; lvl++)
        {
            bigLim[lvl].clear();
            smallLim[lvl].clear();
        }

        int baseXor = 0;
        for (int i = 0; i < days; i++)
        {

            if (lo[i] == hi[i])
            {
                baseXor ^= lo[i];
                continue;
            }

            int diffBit = 31 - __builtin_clz(lo[i] ^ hi[i]);
            int lowMask = (1 << diffBit) - 1;

            int limitA = lowMask - (lo[i] & lowMask);
            int limitB = hi[i] & lowMask;
            int constA = lo[i] | lowMask;
            int constB = hi[i] & ~lowMask;

            if (limitB >= limitA)
            {
                baseXor ^= constB;
                bigLim[diffBit].push_back(limitB);
                smallLim[diffBit].push_back(limitA);
            }
            else
            {
                baseXor ^= constA;
                bigLim[diffBit].push_back(limitA);
                smallLim[diffBit].push_back(limitB);
            }
        }

        int levelFold[30];
        for (int lvl = 0; lvl < 30; lvl++)
        {
            int acc = 0;
            for (int v : bigLim[lvl])
                acc = mergeLimits(acc, v);
            levelFold[lvl] = acc;
        }

        int reach = 0, ans = 0;
        bool restFree = false;

        for (int bit = 29; bit >= 0; bit--)
        {
            if (restFree)
            {
                ans |= (1 << (bit + 1)) - 1;
                break;
            }

            int reachBit = (reach >> bit) & 1;
            int baseBit = (baseXor >> bit) & 1;
            int cnt = bigLim[bit].size();

            if (cnt > 0)
            {
                int usedFold;
                if (baseBit == 0)
                {

                    vector<int> before(cnt + 1, 0), after(cnt + 1, 0);
                    for (int i = 0; i < cnt; i++)
                        before[i + 1] = mergeLimits(before[i], bigLim[bit][i]);
                    for (int i = cnt - 1; i >= 0; i--)
                        after[i] = mergeLimits(after[i + 1], bigLim[bit][i]);

                    int bestFold = -1;
                    for (int i = 0; i < cnt; i++)
                    {
                        int cur = mergeLimits(mergeLimits(before[i], after[i + 1]), smallLim[bit][i]);
                        if (cur > bestFold)
                            bestFold = cur;
                    }
                    usedFold = bestFold;
                    baseXor ^= (1 << (bit + 1)) - 1;
                    baseBit = 1;
                }
                else
                {
                    usedFold = levelFold[bit];
                }
                reach = mergeLimits(reach, usedFold);
            }

            if (reachBit)
            {
                ans |= 1 << bit;
                if (baseBit)
                    restFree = true;
            }
            else if (baseBit)
            {
                ans |= 1 << bit;
            }
        }

        printf("%d\n", ans);
    }
    return 0;
}