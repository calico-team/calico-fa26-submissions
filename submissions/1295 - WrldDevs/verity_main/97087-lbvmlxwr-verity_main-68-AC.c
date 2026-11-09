#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void guess() {
	int charno;
	int verityno;
	scanf("%d %d", &charno, &verityno);
	char verities[verityno + 1];
	for (int i = 0; i < verityno; i++) {
		scanf(" %c", &verities[i]);
	}

	verities[verityno] = '\0';

	int currentstate[charno];

	for (int i = 0; i < charno; i++) {
		currentstate[i] = 0;
	}

	for (int i = 0; i < 100; i++) {
		for (int k = 0; k < charno; k++) {
			printf("%c", verities[currentstate[k]]);
		}
		printf("\n");
		fflush(stdout);

		// look for bro's result
		char result[100];
		scanf("%s", result);

		// if guessed correct
		if (strcmp(result, "CORRECT") == 0) break;

		// if wrong
		for (int i = 0; i < charno; i++) {
			if (result[i] != '_') {
				char *ptr = strchr(verities, result[i]);
				int index = ptr - verities;
				currentstate[i] = index;
			} else {
				currentstate[i]++;
			}
		}
	}
}

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++){
	guess();
	}
}
