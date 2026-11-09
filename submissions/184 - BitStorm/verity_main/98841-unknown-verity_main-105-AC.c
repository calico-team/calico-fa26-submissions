
#include <stdio.h>
#include <string.h>

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int N, K;
        scanf("%d %d", &N, &K);

        char chars[27];

        for (int i = 0; i < K; i++)
        {
            scanf(" %c", &chars[i]);
        }

        char guess[101];
        char response[110];

        int solved[100] = {0};

        // Initialize guess
        for (int i = 0; i < N; i++)
        {
            guess[i] = chars[0];
        }

        guess[N] = '\0';

        for (int c = 0; c < K; c++)
        {
            for (int i = 0; i < N; i++)
            {
                if (solved[i] == 0)
                {
                    guess[i] = chars[c];
                }
            }


            printf("%s\n", guess);
            fflush(stdout);

            if (scanf("%109s", response) != 1)
            {
                return 0;
            }

            if (strcmp(response, "CORRECT") == 0)
            {
                break;
            }

            for (int i = 0; i < N; i++)
            {
                if (response[i] != '_')
                {
                    guess[i] = response[i];
                    solved[i] = 1;
                }
            }
        }
    }

    return 0;
}
