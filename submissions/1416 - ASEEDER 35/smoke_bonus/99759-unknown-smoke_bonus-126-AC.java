import java.io.*;

public class Main {
    private static final byte[] buffer = new byte[1 << 16];
    private static int ptr = 0;
    private static int len = 0;

    private static int readByte() throws IOException {
        if (ptr >= len) {
            len = System.in.read(buffer);
            ptr = 0;
            if (len <= 0) return -1;
        }
        return buffer[ptr++];
    }

    private static long nextLong() throws IOException {
        int c;
        do {
            c = readByte();
        } while (c <= ' ' && c != -1);
        boolean neg = false;
        if (c == '-') {
            neg = true;
            c = readByte();
        }
        long val = 0;
        while (c > ' ') {
            val = val * 10 + (c - '0');
            c = readByte();
        }
        return neg ? -val : val;
    }

    public static void main(String[] args) throws IOException {
        StringBuilder sb = new StringBuilder();
        int t = (int) nextLong();

        while (t-- > 0) {
            int n = (int) nextLong();
            long r = nextLong();

            int available = 2;
            long t1 = -1;
            long t2 = -1;
            boolean ok = true;

            for (int i = 0; i < n; i++) {
                long time = nextLong();

                while (t1 != -1 && t1 <= time) {
                    available++;
                    if (t2 != -1) {
                        t1 = t2;
                        t2 = -1;
                    } else {
                        t1 = -1;
                    }
                }

                if (available > 0) {
                    available--;
                    if (t1 == -1) {
                        t1 = time + r;
                    } else {
                        t2 = t1 + r;
                    }
                } else {
                    ok = false;
                }
            }

            sb.append(ok ? "YES" : "NO").append('\n');
        }

        System.out.print(sb);
    }
}