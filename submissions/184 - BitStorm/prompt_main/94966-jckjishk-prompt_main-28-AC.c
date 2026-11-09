#include <stdio.h>
#include <string.h>

int main()
{
    int T;
    if (scanf("%d", &T) != 1){
        return 0;
    }

    while (T--)
    {
        char S[105];
        scanf("%s", S);

        if (strstr(S, "write_me") != NULL)
        {
            printf("%smake_it_sound_human\n", S);
        }
        else if (strstr(S, "what_is") != NULL)
        {
            printf("%sdo_not_hallucinate\n", S);
        }
        else if (strstr(S, "solve") != NULL)
        {
            printf("%smake_no_mistakes\n", S);
        }
        else
        {
            printf("%sthank_you\n", S);
        }
    }
    return 0;
}