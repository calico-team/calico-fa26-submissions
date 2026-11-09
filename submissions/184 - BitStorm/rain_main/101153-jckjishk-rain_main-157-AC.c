
#include <stdio.h>
#include <stdlib.h>

struct Drone
{
    int x;
    int sum;
    char direction;
};

// Sort drones by sum, then direction, then x-coordinate
int compare(const void *a, const void *b)
{
    struct Drone *d1 = (struct Drone *)a;
    struct Drone *d2 = (struct Drone *)b;

    if (d1->sum != d2->sum)
        return (d1->sum > d2->sum) - (d1->sum < d2->sum);

    if (d1->direction != d2->direction)
        return d1->direction == 'E' ? -1 : 1;

    return (d1->x > d2->x) - (d1->x < d2->x);
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int N;
        long long K;

        scanf("%d %lld", &N, &K);

        struct Drone drones[N];

        // Read all drones
        for (int i = 0; i < N; i++)
        {
            int x, y, z;
            char d;

            scanf("%d %d %d %c", &x, &y, &z, &d);

            drones[i].x = x;
            drones[i].sum = x + y;
            drones[i].direction = d;
        }

        // Maximum possible rainfall
        long long rain = (long long)N * K;

        // Sort the drones
        qsort(drones, N, sizeof(struct Drone), compare);

        int start = 0;

        while (start < N)
        {
            // Find drones with the same x + y
            int end = start;

            while (end < N &&
                   drones[end].sum == drones[start].sum)
            {
                end++;
            }

            // Find where North drones begin
            int north = start;

            while (north < end &&
                   drones[north].direction == 'E')
            {
                north++;
            }

            int left = north;
            int right = north;

            // Check East drones against North drones
            for (int i = start; i < north; i++)
            {
                int eastX = drones[i].x;

                // North drone must start to the right
                while (left < end &&
                       drones[left].x <= eastX)
                {
                    left++;
                }

                if (right < left)
                {
                    right = left;
                }

                // Meeting must happen within K nights
                while (right < end &&
                       (long long)drones[right].x < eastX + K)
                {
                    right++;
                }

                // These North drones meet this East drone
                rain -= right - left;
            }

            start = end;
        }

        printf("%lld\n", rain);
    }

    return 0;
}
