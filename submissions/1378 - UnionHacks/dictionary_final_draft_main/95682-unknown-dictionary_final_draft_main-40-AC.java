import java.io.BufferedInputStream;
import java.io.IOException;
import java.util.Arrays;

public class Dictionary {
    static class FastScanner {
        private final BufferedInputStream in = new BufferedInputStream(System.in);
        int nextInt() throws IOException {
            int c = in.read();
            while (c<= ' ' && c != -1) {
                c = in.read();
            }
            int number = 0;
            while (c > ' ') {
                number = number * 10 + c - '0';
                c = in.read();
            }
            return number;
        }
    }

    static class XorTrie {
        int[] zero;
        int[] one;
        int[] path = new int[31];
        int nodes = 1;
        int free = 0;
        XorTrie(int maxValues) {
            int size = 2;
            for (int depth = 1; depth<=30; depth++) {
                size += (int) Math.min(1L << depth, maxValues);
            }
            zero = new int[size];
            one = new int[size];
        }
        void clear() {
            nodes = 1;
            free = 0;
            zero[1] = 0;
            one[1] = 0;
        }
        int newNode() {
            int node;
            if (free != 0) {
                node = free;
                free = zero[node];
            }
            else {
                node = ++nodes;
            }
            zero[node] = 0;
            one[node] = 0;
            return node;
        }
        void add(int value) {
            int node = 1;
            for (int bit = 29; bit>=0; bit--) {
                if (((value >>> bit) & 1) == 0) {
                    if (zero[node] == 0) {
                        zero[node] = newNode();
                    }
                    node = zero[node];
                }
                else {
                    if (one[node] == 0) {
                        one[node] = newNode();
                    }
                    node = one[node];
                }
            }
            zero[node]++;
        }

        void remove(int value) {
            int node = 1;
            path[0] = node;
            for (int bit = 29; bit >= 0; bit--) {
                if (((value >>> bit) & 1) == 0) {
                    node = zero[node];
                }
                else {
                    node = one[node];
                }
                path[30 - bit] = node;
            }
            zero[node]--;
            if (zero[node] > 0) {
                return;
            }
            for (int depth = 29; depth>=0; depth--) {
                int child = path[depth + 1];
                int parent = path[depth];
                if (((value >>> (29 - depth)) & 1) == 0) {
                    zero[parent] = 0;
                }
                else {
                    one[parent] = 0;
                }
                zero[child] = free;
                one[child] = 0;
                free = child;
                if (zero[parent] != 0 || one[parent] != 0) {
                    break;
                }
            }
        }
        int maxXor(int value) {
            int node = 1;
            int answer = 0;
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
        int[] first = new int[n];
        int[] sibling = new int[n];
        int[] stack = new int[n];
        Arrays.fill(first, -1);
        for (int i = 0; i < n; i++) {
            int to = next[i];
            degree[to]++;
            sibling[i] = first[to];
            first[to] = i;
        }
        int head = 0;
        int tail= 0;
        for (int i = 0; i < n; i++) {
            if (degree[i] == 0) {
                stack[tail++] = i;
            }
        }
        while (head<tail) {
            int word = stack[head++];
            int to = next[word];
            degree[to]--;
            if (degree[to] == 0) {
                stack[tail++] = to;
            }
        }

        XorTrie trie = new XorTrie(2 * n - tail);
        int[] prefix = new int[n];
        int[] answer = new int[n];
        for (int start = 0; start<n; start++) {
            if (degree[start] <= 0) {
                continue;
            }
            trie.clear();
            int word = start;
            int cycleXor = 0;
            do {
                degree[word] = -1;
                prefix[word] = cycleXor;
                trie.add(cycleXor);
                cycleXor ^= value[word];
                word = next[word];
            }
            while (word != start);
            if (cycleXor!= 0) {
                word = start;
                do {
                    trie.add(prefix[word] ^ cycleXor);
                    word = next[word];
                }
                while (word != start);
            }
            word = start;
            do {
                answer[word] = trie.maxXor(prefix[word]);
                int child = first[word];
                while (child != -1) {
                    if (degree[child] == 0) {
                        int top = 0;
                        prefix[child] = value[child] ^ prefix[word];
                        trie.add(prefix[word]);
                        answer[child] = trie.maxXor(prefix[child]);
                        stack[top++] = child;
                        while (top > 0) {
                            int current = stack[top - 1];
                            int branch = first[current];
                            if (branch == -1) {
                                trie.remove(prefix[next[current]]);
                                top--;
                            }
                            else {
                                first[current] = sibling[branch];
                                prefix[branch] = value[branch] ^ prefix[current];
                                trie.add(prefix[current]);
                                answer[branch] = trie.maxXor(prefix[branch]);
                                stack[top++] = branch;
                            }
                        }
                    }
                    child = sibling[child];
                }
                word = next[word];
            }
            while (word != start);
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