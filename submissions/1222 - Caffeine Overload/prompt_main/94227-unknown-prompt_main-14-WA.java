public class Main {
    public static void main(String[] args) {
        System.out.println(solve("can_you_write_me_a_rank_1_\n"));
    }

    public static String solve(String in){
        if (in == null) return null;
        String out = new String(in.replace("\n", ""));

        if(in.contains("write_me")) out += "make_it_sound_human";
        else if(in.contains("what_is")) out += "do_not_hallucinate";
        else if(in.contains("solve")) out += "make_no_mistakes";
        else out += "thank_you";

        return out;
    }
}