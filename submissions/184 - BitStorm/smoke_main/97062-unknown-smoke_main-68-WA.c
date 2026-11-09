
#include <stdio.h>

int main()
{
    int T;

    if (scanf("%d", &T) != 1)
    {
        return 0;
    }

    while (T--)
    {
        int N, R;

        if (scanf("%d %d", &N, &R) != 2)
        {
            return 0;
        }

        int time[N];

        for (int i = 0; i < N; i++)
        {
            if (scanf("%d", &time[i]) != 1)
            {
                return 0;
            }
        }

        int result = 1;
        int available = 2;
        long long nextRecharge = 0;

        for (int i = 0; i < N; i++)
        {
            if (available < 2 && time[i] >= nextRecharge)
            {
                available++;

                if (available < 2)
                {
                    nextRecharge += R;
                }
            }

            if (available == 0)
            {
                result = 0;
                break;
            }
            else
            {
                available--;

                if (available == 1)
                {
                    nextRecharge = time[i] + R;
                }
            }
        }

        if (result)
        {
            printf("YES\n");
        }
        else
        {
            printf("NO\n");
        }
    }

    return 0;
}
