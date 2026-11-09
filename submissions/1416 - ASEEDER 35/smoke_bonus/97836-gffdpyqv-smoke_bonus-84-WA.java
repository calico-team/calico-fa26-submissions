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
        } while (c <= ' ');
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
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        int t = (int) nextLong();

        while (t-- > 0) {
            int n = (int) nextLong();
            long r = nextLong();

            int available = 2;
            long nextFinish = -1;
            int waiting = 0;
            boolean ok = true;

            for (int i = 0; i < n; i++) {
                long time = nextLong();

                if (!ok) continue;

                if (nextFinish != -1 && nextFinish <= time) {
                    available++;
                    if (waiting > 0) {
                        waiting--;
                        nextFinish = time + r;
                    } else {
                        nextFinish = -1;
                    }
                }

                if (available > 0) {
                    available--;
                    if (nextFinish == -1) {
                        nextFinish = time + r;
                    } else {
                        waiting++;
                    }
                } else {
                    ok = false;
                }
            }

            out.println(ok ? "YES" : "NO");
        }

        out.flush();
    }
}