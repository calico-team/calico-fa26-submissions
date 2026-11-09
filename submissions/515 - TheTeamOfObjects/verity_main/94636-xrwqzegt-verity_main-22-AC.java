import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;

public class prob3 {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);
        int testcases = Integer.parseInt(br.readLine());
        for (int i = 0; i < testcases; i++) {
            String[] s = br.readLine().split(" ");
            int length_of_sequence = Integer.parseInt(s[0]);
            int num_of_choices = Integer.parseInt(s[1]);
            String[] choices = br.readLine().split(" ");
            boolean[] correctChoices = new boolean[length_of_sequence];
            String[] guessedThings = new String[length_of_sequence];
            for (int j = 0; j < 100; j++){
                for (int k = 0; k < length_of_sequence; k++) {
                    if (!correctChoices[k])
                    guessedThings[k] = choices[j];
                }
                String result = "";
                for (int k = 0; k < length_of_sequence; k++){
                    result += guessedThings[k];
                }
                pw.println(result);
                pw.flush();
                String thing = br.readLine();
                if (thing.equals("CORRECT")) {
                    break;
                } else {
                    for (int k = 0; k < length_of_sequence; k++) {
                        correctChoices[k] = thing.charAt(k) != '_';
                    }
                }
            }
        }
    }
}
