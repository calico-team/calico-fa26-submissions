import java.util.Scanner;
import java.util.ArrayList;
public class calico_2026_2 {
    public static void main (String[] args) {
        Scanner scan = new Scanner (System.in);
        if (!scan.hasNextInt()) {
            scan.close();
            return;
        }
        int t = scan.nextInt();
        for (int i = 0; i < t; i++) {
            int n = scan.nextInt();
            int m = scan.nextInt();
            int k = scan.nextInt();
            int[] p = new int [n + 1];
            int [] c = new int [n + 1];
            ArrayList<Integer>[] child = new ArrayList [n + 1];
            for (int j = 0; j <= n; j++) {
                child[j] = new ArrayList<>();
            }
            for (int j = 1; j <= n; j++) {
                p[j] = scan.nextInt();
                if (p[j] > 0) {
                    child[p[j]].add(i);
                    c[p[j]]++;
                }
            }
            int[] size = new int [n+1];
            for (int j = 1; j <= n; j++) {
                size[j] = 1;
            }
            int[]q = new int [n+1];
            int head = 0;
            int tail = 0;
            int[] temp = new int [n + 1];
            for (int j = 1; j <= n; j++) {
                temp[j] = c[j];
                if (temp[j] == 0) {
                    q[tail++] = j;
                }
            }
            while (head < tail) {
                int u = q[head++];
                int p1 = p[u];
                if (p1 > 0) {
                    size[p1] = size[p1] + size[u];
                    temp[p1]--;
                    if(temp[p1] == 0) {
                        q[tail++] = p1;
                    }
                }
            }

            ArrayList<Integer> avail = new ArrayList<>();
            for (int j = 1; j <= n; j++) {
                if (p[i] == 0) {
                    avail.add(i);
                }
            }
            int tot = 0;

            for (int s = 0; s < m; s++) {
                if (avail.isEmpty()) {
                    break;
                }
                ArrayList<Integer> taken = new ArrayList<>();
                int take = Math.min(k, avail.size());
                for (int k1 = 0; k1 < take; k1++) {
                    int maxIndex = 0;
                    int max = size[avail.get(0)];
                    for (int index = 1; index < avail.size(); index++) {
                        int course = avail.get(index);
                        if (size[course] > max) {
                            max = size[course];
                            maxIndex = index;
                        }
                    }
                    taken.add(avail.remove(maxIndex));
                }
                tot = tot + taken.size();
                for (int u1 : taken) {
                    for (int v1 : child[u1]) {
                        avail.add(v1);

                    }
                }
            }
            System.out.println(tot);

        }
        scan.close();
    }
}
