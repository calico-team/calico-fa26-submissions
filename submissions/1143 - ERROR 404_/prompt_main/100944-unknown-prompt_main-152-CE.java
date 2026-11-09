import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        
        // Read the number of test cases
        int t = Integer.parseInt(br.readLine().trim());
        
        while (t-- > 0) {
            String s = br.readLine().trim();
            
            // Check containment and append matching strings
            if (s.contains("write_me")) {
                s += "make_it_sound_human";
            } else if (s.contains("what_is")) {
                s += "do_not_hallucinate";
            } else if (s.contains("solve")) {
                s += "make_no_mistakes";
            } else {
                s += "thank_you";
            }
            
            System.out.println(s);
        }
    }
}
public class Main {
    
}
