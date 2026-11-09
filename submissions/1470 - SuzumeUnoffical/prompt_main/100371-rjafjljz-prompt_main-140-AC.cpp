#include<bits/stdc++.h>
using namespace std;
int main()
{
	int T;
	cin>>T;
	char s[115];
	while(T--)
	{
		scanf("%s",s);
		printf("%s",s);
		if(strstr(s,"write_me"))
			puts("make_it_sound_human");
		else if(strstr(s,"what_is"))
			puts("do_not_hallucinate");
		else if(strstr(s,"solve"))
			puts("make_no_mistakes");
		else puts("thank_you");
	}
	return 0;
}