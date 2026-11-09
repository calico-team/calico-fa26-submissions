import java.io.*;
import java.util.*;

public class Calicoforgor {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
        String phase = br.readLine();
        int n = Integer.parseInt(br.readLine().trim());
        int[] a = new int[n];
        if (phase.equals("FIRST")) {
            ArrayList<Integer>[] graph = new ArrayList[n];
            for (int i = 0; i < n; i++) {
                graph[i] = new ArrayList<>();
            }
            for (int i = 0; i < n - 1; i++) {
                StringTokenizer st = new StringTokenizer(br.readLine());
                int u = Integer.parseInt(st.nextToken()) - 1;
                int v = Integer.parseInt(st.nextToken()) - 1;
                graph[u].add(v);
                graph[v].add(u);
            }

            int[] queue = new int[n];
            boolean[] visited = new boolean[n];
            int a1 = 0;
            int a2 = 0;
            queue[a2++] = 0;
            visited[0] = true;
            a[0] = 1;
            while (a1 < a2) {
                int u = queue[a1++];
                for (int v : graph[u]) {
                    if (!visited[v]) {
                        visited[v] = true;
                        a[v] = u + 1;
                        queue[a2++] = v;
                    }
                }
            }

        } 
        else {
            StringTokenizer st = new StringTokenizer("");
            for (int i = 0; i < n; i++) {
                while (!st.hasMoreTokens()) {
                    st = new StringTokenizer(br.readLine());
                }
                a[i] = Integer.parseInt(st.nextToken());
            }
        }

        int bits = 32 - Integer.numberOfLeadingZeros(n);
        //
        int[] used = new int[n];
        int[] s1 = new int[bits];
        int[] s2 = new int[bits];
        for (int j = 0; j < bits; j++) {
            int p1 = j;
            int p2 = (j + bits) % n;

            s1[j] = used[p1]++;
            s2[j] = used[p2]++;
        }

        if (phase.equals("FIRST")) {
            long sum = 0;
            for (int i = 0; i < n; i++) {
                sum += a[i];
            }
            int modsum = (int)(sum % n);
            int[] encode = new int[n];
            for (int j = 0; j < bits; j++) {
                int bit = (modsum >> j) & 1;
                int p1 = j;
                int p2 = (j + bits) % n;

                encode[p1] |= bit << s1[j];
                encode[p2] |= bit << s2[j];
                //System.out.println(encode[p1]);
                //System.out.println(encode[p2]);
            }

            for (int i = 0; i < n; i++) {
                a[i] += n * encode[i];
            }
            for (int i = 0; i < n; i++) {
                if (i > 0) out.print(" ");
                out.print(a[i]);
            }
            out.println();
        } 
        else if (phase.equals("SECOND")){
            int gone = -1;
            for (int i = 0; i < n; i++) {
                if (a[i] == -1) {
                    gone = i;
                    break;
                }
            }
            int modsum = 0;
            for (int j = 0; j < bits; j++) {
                int p1 = j;
                int p2 = (j + bits) % n;
                int shift = 0;
                int index = 0;          
                if (p1 != gone) {
                    index = p1;
                    shift = s1[j];
                } else {
                    index = p2;
                    shift = s2[j];
                }
                int encode = (a[index] - 1) / n;
                int bit = (encode >> shift) & 1;
                modsum |= bit << j;
            }
            long sum = 0;
            for (int i = 0; i < n; i++) {
                if (i == gone){
                  continue;
                }
                a[i] = (a[i] - 1) % n + 1;
                sum += a[i];
            }
            int value = (int)((modsum - sum % n +n) % n);
            if (value == 0) {
                value = n;
            }
            a[gone] = value;
            for (int i = 1; i < n; i++) {
                out.println((i + 1) + " " + a[i]);
            }
        }
        out.flush();
    }
}