import java.io.IOException;

public class p2 {
    static final int BUFFER_SIZE = 1 << 16; // 65536 bytes
    static byte[] buffer = new byte[BUFFER_SIZE];
    static int bufferPointer = 0, bytesRead = 0;

    static int readByte() throws IOException {
        if (bufferPointer == bytesRead) {
            bytesRead = System.in.read(buffer, 0, BUFFER_SIZE);
            bufferPointer = 0;
        }
        return (bytesRead == -1) ? -1 : buffer[bufferPointer++];
    }

    static int readInt() throws IOException {
        int b = readByte();
        while (b <= ' ') b = readByte(); // skip whitespace

        boolean negative = (b == '-');
        if (negative) b = readByte();

        int n = 0;
        while (b >= '0' && b <= '9') {
            n = n * 10 + (b - '0');
            b = readByte();
        }
        return negative ? -n : n;
    }

    static String readNext() throws IOException {
        int b = readByte();
        while (b <= ' ') {
            b = readByte();
        }

        StringBuilder sb = new StringBuilder();
        while (b > ' ') {
            sb.append((char) b);
            b = readByte();
        }

        return sb.toString();
    }

    public static void main(String[] args) throws IOException {
        int t = readInt();

        for(int goob=0;goob<t;goob++){
//            System.out.println("START____");
            int n = readInt();
            int r = readInt();
            boolean canFufill = true;
            int smokes = 2;
            int timeForNextSmoke = 0;
            int[] requests = new int[n];
            for(int i=0;i<n;i++){
                requests[i] = readInt();
            }
            for(int i=0;i<n;i++){
                if(i>0) {

                    timeForNextSmoke += (requests[i] - requests[i - 1]);
                    smokes += (timeForNextSmoke / r);
                    timeForNextSmoke -= r * (timeForNextSmoke / r);
                }
                    if(smokes>=2){
                        timeForNextSmoke=0;
                        smokes=2;
                    }
//                    System.out.println(smokes+" "+timeForNextSmoke);
                    if(smokes==0){
                        canFufill = false;
                        break;
                    }
                    smokes-=1;


            }
            if(canFufill){
                System.out.println("YES");
            }
            else{
                System.out.println("NO");
            }
        }
    }
}
