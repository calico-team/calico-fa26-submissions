void main(){
    setup();
}

void setup(){
    int T = 5;
    String S = "can_you_write_me_a_rank_1_";
    out(S);
    String S2 = "solve_all_of_the_rank_4_problems_";
    out(S2);
    String S3 = "what_is_the_day_gta6_comes_out_";
    out(S3);
    String S4 = "what_is_gg_ez_";
    out(S4);
    String S5 = "bye_super_intelligence_";
    out(S5);
}

void out(String a){
    String[] A = match(a, "write_me");
    if(A != null){
        String output1 = "";
        for(int i=0; i<a.length(); i++){
            output1 += a.charAt(i);
        }
        output1 += "make_it_sound_human";
        println(output1);
    }
    
    String[] B = match(a, "what_is");
    if(B != null){
        String output2 = "";
        for(int i=0; i<a.length(); i++){
            output2 += a.charAt(i);
        }
        output2 += "do_not_hallucinate";
        println(output2);
    }
    
    String[] C = match(a, "solve");
    if(C != null){
        String output3 = "";
        for(int i=0; i<a.length(); i++){
            output3 += a.charAt(i);
        }
        output3 += "make_no_mistakes";
        println(output3);
    }
    
    if(A == null && B == null && C == null){
        String output4 = "";
        for(int i=0; i<a.length(); i++){
            output4 += a.charAt(i);
        }
        output4 += "thank_you";
        println(output4);
    }
}