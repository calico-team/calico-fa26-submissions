import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {

    public static void main(String[] args) {
        int T = 5;
        String S = "can_you_write_me_a_rank_1_";
        out(S);
    }

    public static void out(String a) {
        int b = a.length();
        
        // 模拟 Processing 的 match(a, "write_me")
        // Processing 的 match 返回 String[]，如果没找到返回 null
        String[] A = match(a, "write_me");
        
        if (A != null) {
            StringBuilder output1 = new StringBuilder();
            for (int i = 0; i < b; i++) {
                output1.append(a.charAt(i));
            }
            output1.append("make_it_sound_human");
            System.out.println(output1.toString());
        }

        String[] B = match(a, "what_is");
        if (B != null) {
            StringBuilder output2 = new StringBuilder();
            for (int i = 0; i < b; i++) {
                output2.append(a.charAt(i));
            }
            output2.append("do_not_hallucinate");
            System.out.println(output2.toString());
        }

        String[] C = match(a, "solve");
        if (C != null) {
            StringBuilder output3 = new StringBuilder();
            for (int i = 0; i < b; i++) {
                output3.append(a.charAt(i));
            }
            output3.append("make_no_mistakes");
            System.out.println(output3.toString());
        }

        if (A == null && B == null && C == null) {
            StringBuilder output4 = new StringBuilder();
            for (int i = 0; i < b; i++) {
                output4.append(a.charAt(i));
            }
            output4.append("thank_you");
            System.out.println(output4.toString());
        }
    }

    /**
     * 模拟 Processing 的 match() 函数
     * 如果找到匹配项，返回包含匹配结果的字符串数组；否则返回 null
     */
    public static String[] match(String input, String regex) {
        if (input == null || regex == null) {
            return null;
        }
        try {
            Pattern pattern = Pattern.compile(regex);
            Matcher matcher = pattern.matcher(input);
            if (matcher.find()) {
                // Processing 的 match 返回第一个完整匹配及捕获组
                // 这里简化处理，只要找到匹配就返回一个非空数组，模拟不为 null 的行为
                return new String[]{matcher.group()};
            }
        } catch (Exception e) {
            // 正则表达式错误等异常
            return null;
        }
        return null;
    }
}
