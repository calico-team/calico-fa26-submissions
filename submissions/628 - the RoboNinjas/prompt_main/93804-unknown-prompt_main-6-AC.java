import java.io.IOException;

public class p1 {
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
        int t=  readInt();
        for(int good=0;good<t;good++){
            String word = readNext();
            if(word.contains("write_me")){
                word = word+"make_it_sound_human";
            }
            else if(word.contains("what_is")){
                word = word+"do_not_hallucinate ";
            }
            else if(word.contains("solve")){
                word = word+"make_no_mistakes";
            }
            else{
                word = word+"thank_you";
            }
            System.out.println(word);
        }
    }
}
