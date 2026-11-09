import java.io.*;
import java.util.*;

public class Main {
    static class FastScanner {
        private final InputStream in = System.in;
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0, len = 0;

        int read() throws IOException {
            if (ptr >= len) {
                len = in.read(buffer);
                ptr = 0;
                if (len <= 0) return -1;
            }
            return buffer[ptr++];
        }

        int nextInt() throws IOException {
            int c;
            do { c = read(); } while (c <= 32 && c != -1);

            int value = 0;
            while (c > 32) {
                value = value * 10 + c - '0';
                c = read();
            }
            return value;
        }
    }

    public static void main(String[] args) throws Exception {
        FastScanner input = new FastScanner();
        StringBuilder out = new StringBuilder();

        int T = input.nextInt();

        while (T-- > 0) {
            int rows = input.nextInt();
            int cols = input.nextInt();
            int q = input.nextInt();

            int[][] events = new int[q][3];

            for (int i = 0; i < q; i++) {
                events[i][0] = input.nextInt();
                events[i][1] = input.nextInt();
                events[i][2] = input.nextInt();
            }

            int[][] grid = new int[rows][cols];
            BitSet[] pending = new BitSet[rows];

            for (int y = 0; y < rows; y++) {
                pending[y] = new BitSet(cols);
                pending[y].set(0, cols);
            }

            int remaining = rows * cols;

            for (int i = q - 1; i >= 0 && remaining > 0; i--) {
                int cy = events[i][0];
                int cx = events[i][1];
                int power = events[i][2];

                int radius2 = power * power;

                for (int y = cy - power; y <= cy + power; y++) {
                    int dy = y - cy;
                    int dx = (int) Math.sqrt(radius2 - dy * dy);

                    int left = cx - dx;
                    int right = cx + dx;

                    for (int x = pending[y].nextSetBit(left);
                         x >= 0 && x <= right;
                         x = pending[y].nextSetBit(x + 1)) {

                        int distance2 =
                                dy * dy + (x - cx) * (x - cx);

                        grid[y][x] = radius2 - distance2 + 1;

                        pending[y].clear(x);
                        remaining--;
                    }
                }
            }

            for (int[] line : grid) {
                for (int j = 0; j < cols; j++) {
                    if (j > 0) out.append(' ');
                    out.append(line[j]);
                }
                out.append('\n');
            }
        }

        System.out.print(out);
    }
}
