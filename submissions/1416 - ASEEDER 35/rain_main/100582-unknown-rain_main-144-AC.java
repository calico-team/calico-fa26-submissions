import java.io.BufferedOutputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Arrays;
public final class ProblemFourSli {

    private static final int MAXX = 100000;  
        private static final int MAXS = 200000;   
        
    private static final int[] headE = new int[MAXX + 1];
    private static final int[] headN = new int[MAXX + 1];
    private static final int[] nextE = new int[MAXX + 1];
    private static final int[] nextN = new int[MAXX + 1];
    private static final int[] keyE = new int[MAXX + 1];
    private static final int[] keyN = new int[MAXX + 1];

    private static final int[] inWindow = new int[MAXS + 1];  
        public static void main(String[] args) throws IOException {
        byte[] in = readAll(System.in);
        int[] pos = {0};

        int t = nextInt(in, pos);
        OutputStream out = new BufferedOutputStream(System.out, 1 << 16);
        StringBuilder sb = new StringBuilder();

        for (int tc = 0; tc < t; tc++) {
            int n = nextInt(in, pos);
            long k = nextInt(in, pos);

            Arrays.fill(headE, -1);
            Arrays.fill(headN, -1);
            int ne = 0, nn = 0, maxX = 0;

            for (int i = 0; i < n; i++) {
                int x = nextInt(in, pos);
                int y = nextInt(in, pos);
                nextInt(in, pos);                       
                char d = nextDir(in, pos);
                int s = x + y;
                if (x > maxX) maxX = x;
                if (d == 'E') { nextE[ne] = headE[x]; keyE[ne] = s; headE[x] = ne++; }
                else          { nextN[nn] = headN[x]; keyN[nn] = s; headN[x] = nn++; }
            }

            long meetings = 0;
            int add = 0, rem = 0;     
            
                       for (int bx = 0; bx <= maxX; bx++) {
                while (add <= bx) {
                    for (int p = headE[add]; p != -1; p = nextE[p]) inWindow[keyE[p]]++;
                    add++;
                }
                long tooOld = bx - k;                   
                while (rem <= tooOld) {
                    for (int p = headE[rem]; p != -1; p = nextE[p]) inWindow[keyE[p]]--;
                    rem++;
                }
                for (int p = headN[bx]; p != -1; p = nextN[p]) meetings += inWindow[keyN[p]];
            }

            for (int i = 0; i < ne; i++) inWindow[keyE[i]] = 0;   
            sb.append(k * n - meetings).append('\n');
        }

        out.write(sb.toString().getBytes());
        out.flush();
    }


    private static byte[] readAll(InputStream in) throws IOException {
        ByteArrayOutputStream bo = new ByteArrayOutputStream(1 << 16);
        byte[] buf = new byte[1 << 16];
        int r;
        while ((r = in.read(buf)) > 0) bo.write(buf, 0, r);
        return Arrays.copyOf(bo.toByteArray(), bo.size() + 8);
    }

    private static int nextInt(byte[] in, int[] pos) {
        int p = pos[0];
        while (in[p] < '0') p++;                      
                int v = 0;
        while (in[p] >= '0') v = v * 10 + (in[p++] - '0');
        pos[0] = p;
        return v;
    }

    private static char nextDir(byte[] in, int[] pos) {
        int p = pos[0];
        while (in[p] != 'E' && in[p] != 'N') p++;
        pos[0] = p + 1;
        return (char) in[p];
    }
}