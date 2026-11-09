import java.io.DataInputStream;
import java.io.IOException;

public class Main {
    public static void main(String[] args) throws IOException {
        
    }

    private static final int BUFFER_SIZE = 1 << 16;
    private static int LENGTH = -1;
    private static DataInputStream din = new DataInputStream(System.in);
    private static byte[] buffer = new byte[BUFFER_SIZE], buf = new byte[BUFFER_SIZE];
    private static int bufferPointer = 0, bytesRead = 0;

    public static int readInt() throws IOException {
        int ret = 0;
        byte c;
        do {
            c = read();
        } while (c <= ' ');
        boolean neg = (c == '-');
        if (neg)
            c = read();
        do {
            ret = ret * 10 + c - '0';
        } while ((c = read()) >= '0');
        if (neg)
            return -ret;
        return ret;
    }

    public static long readLong() throws IOException {
        long ret = 0;
        byte c;
        do {
            c = read();
        } while (c <= ' ');
        boolean neg = (c == '-');
        if (neg)
            c = read();
        do {
            ret = ret * 10 + c - '0';
        } while ((c = read()) >= '0');
        if (neg)
            return -ret;
        return ret;
    }

    public static double readDouble() throws IOException {
        double ret = 0, div = 1;
        byte c;
        do {
            c = read();
        } while (c <= ' ');
        boolean neg = (c == '-');
        if (neg)
            c = read();
        do {
            ret = ret * 10 + c - '0';
        } while ((c = read()) >= '0');
        if (c == '.')
            while ((c = read()) >= '0')
                ret += (c - '0') / (div *= 10);
        if (neg)
            return -ret;
        return ret;
    }

    public static char readCharacter() throws IOException {
        byte c;
        do {
            c = read();
        } while (c <= ' ');
        return (char) c;
    }

    public static String next() throws IOException {
        int cnt = 0;
        byte c;
        do {
            c = read();
        } while (c <= ' ');
        do {
            buf[cnt++] = c;
        } while ((c = read()) > ' ');
        return new String(buf, 0, cnt);
    }

    public static String readLine() throws IOException {
        while (bufferPointer > 0 && buffer[bufferPointer - 1] == '\r')
            read();
        int cnt = 0;
        byte c;
        while ((c = read()) != '\n' && c != '\0')
            if (c != '\r')
                buf[cnt++] = c;
        return new String(buf, 0, cnt);
    }

    public static void setLength(int len) {
        LENGTH = len;
        buf = new byte[len];
    }

    public static boolean hasNext() throws IOException {
        while (peek() != -1 && peek() <= ' ')
            read();
        return peek() != -1;
    }

    public static boolean hasNextLine() throws IOException {
        while (peek() == '\r')
            read();
        return peek() != -1;
    }

    private static void fillBuffer() throws IOException {
        bytesRead = din.read(buffer, bufferPointer = 0, BUFFER_SIZE);
        if (bytesRead == -1)
            buffer[0] = -1;
    }

    private static byte read() throws IOException {
        if (bufferPointer == bytesRead)
            fillBuffer();
        return buffer[bufferPointer++];
    }

    private static byte peek() throws IOException {
        if (bufferPointer == bytesRead)
            fillBuffer();
        return buffer[bufferPointer];
    }

    public static void close() throws IOException {
        if (din == null)
            return;
        din.close();
    }
}