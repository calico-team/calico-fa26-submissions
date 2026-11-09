#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;
	cin >> T;
	while(T--){
		string s;
		cin >> s;
		bool t = false;
		cout << s;
		for(int i = 0; i < s.size(); i ++){
			if(s[i] == 'w'){
				if(s[i+1] == 'r'){
					if(s[i+2] == 'i'){
						if(s[i+3] == 't'){
							if(s[i+4] == 'e'){
								if(s[i+5] == '_'){
									if(s[i+6] == 'm'){
										if(s[i+7] == 'e'){
											t = true;
											cout << "make_it_sound_human";
										}
									}
								}
							}
						}
					}
				}
				else if(s[i+1] == 'h'){
					if(s[i+2] == 'a'){
						if(s[i+3] == 't'){
							if(s[i+4] == '_'){
								if(s[i+5] == 'i'){
									if(s[i+6] == 's'){
										t = true;
										cout << "do_not_hallucinate";
									}
								}
							}
						}
					}
				}
			}
			else if(s[i] == 's'){
				if(s[i+1] == 'o'){
					if(s[i+2] == 'l'){
						if(s[i+3] == 'v'){
							if(s[i+4] = 'e'){
								t = true;
								cout << "make_no_mistakes";
							}
						}
					}
				}
			}
		}
		if(t != true){
			cout << "thank_you";
		} 
		cout << endl;
	} 
}

