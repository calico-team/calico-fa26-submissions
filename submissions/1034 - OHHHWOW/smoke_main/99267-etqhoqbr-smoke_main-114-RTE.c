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
    	for (j=1;j<N;j++){
    		if ((request[j]-request[j-1])<R){
    			printf("NO");
    			wrong =1;
    			j=N;
			}
		}
		if (wrong!=1){
			printf("YES");
		}
	}
	return 0;
}
