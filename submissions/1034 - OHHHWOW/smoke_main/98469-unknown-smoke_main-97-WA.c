#include<stdio.h>


int main (void){
	int N,R,j;
	int T,i;
	int request[N];
	int wrong;
	scanf("%d", &T);
	for (i=0;i<T;i++){
		j=0;
		scanf("%d %d", &N, &R);
		do {
       		scanf("%d ", &request[j++]);
    	} while (getchar() != '\n' && j < N);
    	for (i=1;i<N;i++){
    		if ((request[i]-request[i-1])!=R){
    			printf("NO");
    			wrong =1;
    			i=N;
			}
		}
		if (wrong!=1){
			printf("YES");
		}
	}
	return 0;
}
