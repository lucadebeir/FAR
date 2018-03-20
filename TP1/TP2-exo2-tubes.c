#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
	pid_t pid;
	int p1[2]; /*création premier tube*/
   	int p2[2]; /*création du deuxième tube*/
    	pipe(p1);
    	pipe(p2);
    	pid=fork();


    	if (pid == 0) {
		close(p1[1]);
    		close(p2[0]);
    		int tableau[5];
		int i=0;
    		while (i<5) {
			read(p1[0], &tableau[i], sizeof(int));
    			tableau[i]=tableau[i]+1;
    			write(p2[1], &tableau[i], sizeof(int));
    			i=i+1;
    		}
		return EXIT_SUCCESS;
    	}


    	if (pid != 0) {
    		close(p1[0]);
		close(p2[1]);
    		int tableau[] = {2,8,3,9,5}; //création d'un tableau
		int i=0;
		while (i<5) {
    			write(p1[1], &tableau[i], sizeof(int));
			i=i+1;
		}
		while (wait(0) != -1) {} ;

		int j=0;
		while (j<5) {
			read(p2[0], &tableau[j], sizeof(int));
			printf("Entier incrémenté : %d\n", tableau[j]);
			j=j+1;
		}
    	}

}
