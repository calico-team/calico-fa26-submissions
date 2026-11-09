
#include <stdio.h>

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int N;
        scanf("%d", &N);

        int R;
        scanf("%d", &R);

        int time[N];

        for (int i = 0; i < N; i++)
        {
            scanf("%d", &time[i]);
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
