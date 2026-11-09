import java.util.*;

class Solution {

    static class Drone {
        int X, Y, Z;
        char D;

        Drone(int X, int Y, int Z, char D) {
            this.X = X;
            this.Y = Y;
            this.Z = Z;
            this.D = D;
        }
    }

    static long solve(int N, int K, List<Drone> L) {
        long answer = 0;

        Collections.sort(L, new Comparator<Drone>() {
            public int compare(Drone p, Drone q) {
                int s1 = p.X + p.Y;
                int s2 = q.X + q.Y;
                if (s1 != s2) {
                    return s1 - s2;
                }
                return p.X - q.X;
            }
        });

        int[] qx = new int[N];
        for (int i = 0; i < N; ) {
            int sum = L.get(i).X + L.get(i).Y;
            int j = i;
            while (j < N && L.get(j).X + L.get(j).Y == sum) j++;

            int head = 0, tail = 0;
            for (int t = i; t < j; t++) {
                Drone d = L.get(t);
                if (d.D == 'E') {
                    qx[tail++] = d.X;
                } else {
                    long low = (long) d.X - K + 1;
                    while (head < tail && qx[head] < low) head++;
                    answer += tail - head;
                }
            }
            i = j;
        }

        answer = (long) N * K - answer;
        return answer;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        if (!sc.hasNextInt()) return;

        int T = sc.nextInt();
        while (T-- > 0) {
            int N = sc.nextInt();
            int K = sc.nextInt();

            List<Drone> L = new ArrayList<>();
            for (int i = 0; i < N; i++) {
                int X = sc.nextInt();
                int Y = sc.nextInt();
                int Z = sc.nextInt();
                char D = sc.next().charAt(0);
                L.add(new Drone(X, Y, Z, D));
            }

            System.out.println(solve(N, K, L));
        }
    }
}
