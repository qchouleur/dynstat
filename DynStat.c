/* --------------------------------------------------------- */
/* Objectif : Corriger les erreurs statiques et dynamiques   */
/*            de ce programme                                */
/* --------------------------------------------------------- */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[])
{
	/* On ne touche pas à la variable "size" */
    int size = 16;
    int length = 0;
    char * buf = NULL;
	
	
	/* Verification du nombre d'argument 
	   passer lors de l'appel de la fonction */
	if(argc != 3) {
		printf("usage : dynstat arg1 arg2\n");
		return -1;
	}

	/* utilisation du format de chaine de caracteres 
	   pour eviter une format string attack */
	printf("%s\n", argv[1]);

	/* allocation et initialisation de la memoire allouee a zero 
	   erreur valgrind : Uninitialised value was created by a heap allocation */
	buf = (char*)calloc(sizeof(char)*(size + 1), 1);

	/* verification que l'allocation memoire a bien ete effectuee */
	if(buf == NULL) {
		printf("could not allocate space for buffer\n");
		return -1;
	}

	/* changement de sizeof(buf) a size danger potentiel CWE-467*/	
	strncpy(buf, argv[2], size);

	/* assure que la chaine se termine bien par le caractere 
	   de fin de chaine */
	buf[size] = '\0';

	/* verifie que la chaine copier correspond bien a celle
	   passee en argument */
	if(strcmp(buf, argv[2]) != 0) {
		printf("arg2 length exceed the limit of %d", size);
		free(buf);
		return -1;
	}

	printf("buffer : %s\n", buf);
	
	/* ----------------------------------------------------- */
	/* On ne touche pas au contenu "testdubuffer"            */
	/* mais on peut créer une variable reprenant ce contenu  */
	/* ----------------------------------------------------- */
	
	/* CWE-467, pas besoin de verification etant sur de notre utilisation */
	strncpy(buf, "testdubuffer", size);	
	
	length = strlen(buf);
    	if(length != 0) {
        	printf("buffer : %s\n", buf);
        }

	/* libere la memoire dynamiquement allouee quoi qu'il arrive
	   et evite donc la fuite memoire reperee par valgrind */
	free(buf);
		
	return 0;
}
