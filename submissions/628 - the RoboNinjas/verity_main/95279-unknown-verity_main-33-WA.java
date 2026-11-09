import java.io.IOException;

public class P3 {
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
    static char readChar() throws IOException {
        int b = readByte();
        while (b <= ' ') b = readByte();
        return (char) b;
    }

    public static void main(String[] args) throws IOException {
        int t = readInt();
        for(int goob=0;goob<t;goob++){
            int length = readInt();
            int numOfChars = readInt();
            char[] charcters = new char[numOfChars];
            char[] correctChars = new char[length];

            String output = "";
            int index = 0;
            boolean correct = false;

            for(int i=0;i<numOfChars;i++){
                charcters[i] = readChar();
            }
            for(int i=0;i<charcters.length;i++){
                System.out.println(String.valueOf(charcters[i]).repeat(length));
                output = readNext();
                if(output.equals("CORRECT")){
                    correct = true;
                    break;
                }
                for(int ii=0;ii<output.length();ii++){
                    if(output.charAt(ii)==charcters[i]){
                        correctChars[ii] = charcters[i];
                    }
                }

            }
            if(!correct){
                System.out.println(correctChars);
            }
        }
    }
}
