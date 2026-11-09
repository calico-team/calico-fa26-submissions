#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
   int T;

   char * S = malloc(100 * sizeof(char));

   scanf("%d", &T);
   if(T >= 1 && T <= 100){
        for (int i = 0; i < T; i++) {
            scanf("%s", S);

            if (strstr(S, "write_me") != NULL) {
                strncat(S, "make_it_sound_human", 100 - strlen(S) - 1);
            } else if (strstr(S, "what_is") != NULL) {
                strncat(S, "do_not_hallucinate", 100 - strlen(S) - 1);
            } else if (strstr(S, "solve") != NULL) {
                strncat(S, "make_no_mistakes", 100 - strlen(S) - 1);
            } else {
                strncat(S, "thank_you", 100 - strlen(S) - 1);
            }

            printf("%s\n", S);
        }

        free(S);
   }
   
   return 0;
}