#include <stdio.h>
#include <stdlib.h>

int takecourse() {
	int classes, semesters, max;
	scanf("%d %d %d", &classes, &semesters, &max);
	int prereqs[classes];
	int completed[classes];
	int taking[classes];
	int isdependencyof[classes];
	int tfheight[classes];

	for (int i = 0; i < classes; i++) {
		scanf(" %d", &prereqs[i]);
		completed[i] = 0;
	}

	for (int i = 0; i < classes; i++) {
	    tfheight[i] = 0;
	}

	for (int j = 0; j < classes; j++) {
	    int checking = j;
	    int distance = 0;

	    while (prereqs[checking] != 0) {
		int sss = prereqs[checking] - 1;
		distance++;

		if (distance > tfheight[sss]) {
		    tfheight[sss] = distance;
		}

		checking = sss;
	    }
	}

	/*for (int i = 0; i < classes; i++) {
	    printf("%d ", tfheight[i]);
	}
	printf("\n");*/
	int tfdepth[classes];

	for (int i = 0; i < classes; i++) {
	    int dependencydepth = 0;
	    int nowchecking = i;

	    while (1 == 1) {
		if (prereqs[nowchecking] == 0)
		    break;

		nowchecking = prereqs[nowchecking] - 1;
		dependencydepth++;
	    }

	    tfdepth[i] = dependencydepth + 1;
	}
	
	/*
	for (int i = 0; i < classes; i++) {
		printf("%d ", tfdepth[i]);
	}
	*/

	// now is the take class loop
	
	int takenclasses = 0;

	for (int semester = 1; semester <= semesters && takenclasses < classes; semester++) {

	    for (int k = 0; k < classes; k++) {
		taking[k] = 0;
	    }

	    int slots = max;

	for (int seat = 0; seat < max; seat++) {
		int best = -1;

		for (int k = 0; k < classes; k++) {
			if (!completed[k] && !taking[k] && (prereqs[k] == 0 || completed[prereqs[k] - 1])) {
			    	if (best == -1 || tfheight[k] > tfheight[best]) {
					best = k;
			    	}
			}
		}

	    	if (best == -1)
			break;

	    	taking[best] = 1;
	}

	    	for (int k = 0; k < classes; k++) {
			if (taking[k]) {
		    		completed[k] = 1;
		    		takenclasses++;
			}
	    	}
	}

	return takenclasses;
}

int main() {
	// I am the lone contestant at this point, my teammates have entered hibernation
	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		printf("%d\n", takecourse());
	}
}
