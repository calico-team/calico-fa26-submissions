import java.io.BufferedInputStream;
import java.io.IOException;

public class Dictionary {
    static class FastScanner {
        private final BufferedInputStream in = new BufferedInputStream(System.in);
        int nextInt() throws IOException {
            int c = in.read();
            while (c<= ' ' && c != -1) {
                c = in.read();
            }
            int number= 0;
            while (c > ' ') {
                number = number * 10 + c - '0';
                c = in.read();
            }
            return number;
        }
    }

    static class XorTrie {
        private final int[] zero;
        private final int[] one;
        private int nodes = 0;
        XorTrie(int maxValues) {
            int size = maxValues * 31 + 1;
            zero = new int[size];
            one = new int[size];
        }
        int copy(int node) {
            nodes++;
            zero[nodes] = zero[node];
            one[nodes] = one[node];
            return nodes;
        }

        int add(int root, int value) {
            int newRoot = copy(root);
            int oldNode= root;
            int newNode = newRoot;
            for (int bit = 29; bit>=0; bit--) {
                if (((value >>> bit) & 1) == 0) {
                    int child = copy(zero[oldNode]);
                    zero[newNode] = child;
                    oldNode = zero[oldNode];
                    newNode = child;
                }
                else {
                    int child = copy(one[oldNode]);
                    one[newNode] = child;
                    oldNode = one[oldNode];
                    newNode = child;
                }
            }
            return newRoot;
        }
        int maxXor(int root, int value) {
            int answer = 0;
            int node = root;
            for (int bit = 29; bit >= 0; bit--) {
                int same;
                int opposite;
                if (((value >>> bit) & 1) == 0) {
                    same = zero[node];
                    opposite = one[node];
                }
                else {
                    same = one[node];
                    opposite = zero[node];
                }
                if (opposite!= 0) {
                    answer |= 1 << bit;
                    node = opposite;
                }
                else {
                    node = same;
                }
            }
            return answer;
        }
    }
    static int[] solve(int[] next, int[] value) {
        int n = next.length;
        int[] degree = new int[n];
        int[] order = new int[n];
        for (int i = 0; i < n; i++) {
            degree[next[i]]++;
        }

        int head = 0;
        int tail= 0;
        for (int i = 0; i < n; i++) {
            if (degree[i] == 0) {
                order[tail++] = i;
            }
        }
        while (head<tail) {
            int word = order[head++];
            int to = next[word];
            degree[to]--;
            if (degree[to] == 0) {
                order[tail++] = to;
            }
        }

        XorTrie trie = new XorTrie(2 * n - tail);
        int[] prefix = new int[n];
        int[] root = new int[n];
        for (int start = 0; start<n; start++) {
            if (degree[start] == 0) {
                continue;
            }
            int word = start;
            int cycleXor = 0;
            int cycleRoot = 0;
            do {
                prefix[word] = cycleXor;
                cycleRoot = trie.add(cycleRoot, prefix[word]);
                cycleXor ^= value[word];
                word = next[word];
            }
            while (word != start);
            if (cycleXor!= 0) {
                word = start;
                do {
                    cycleRoot = trie.add(cycleRoot, prefix[word] ^ cycleXor);
                    word = next[word];
                }
                while (word != start);
            }
            word = start;
            do {
                root[word] = cycleRoot;
                degree[word] = 0;
                word = next[word];
            }
            while (word != start);
        }
        for (int i = tail - 1; i>=0; i--) {
            int word = order[i];
            int to = next[word];
            prefix[word] = value[word] ^ prefix[to];
            root[word] = trie.add(root[to], prefix[to]);
        }
        int[] answer = new int[n];
        for (int i = 0; i < n; i++) {
            answer[i] = trie.maxXor(root[i], prefix[i]);
        }
        return answer;
    }

    public static void main(String[] args) throws IOException {
        FastScanner in = new FastScanner();
        StringBuilder output = new StringBuilder();
        int t = in.nextInt();
        for (int test = 0; test < t; test++) {
            int n = in.nextInt();
            int[] next = new int[n];
            int[] value = new int[n];
            for (int i = 0; i < n; i++) {
                next[i] = in.nextInt() - 1;
            }
            for (int i = 0; i < n; i++) {
                value[i] = in.nextInt();
            }
            int[] answer = solve(next, value);
            for (int i = 0; i < n; i++) {
                if (i> 0) {
                    output.append(' ');
                }
                output.append(answer[i]);
            }
            output.append('\n');
        }
        System.out.print(output);
    }
}