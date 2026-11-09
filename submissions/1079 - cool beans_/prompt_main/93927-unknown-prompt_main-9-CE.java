
public class Problem_1 {
	public static String main (String s) {
		if (s.contains("write_me")) {
			s = s + "make_it_sound_human";
		} else if (s.contains("what_is")) {
			s = s + "do_not_hallucinate";
		} else if (s.contains("solve")) {
			s = s + "make_no_mistakes";
		} else {
			s = s + "thank_you";
		}
		return s;
	}
}
