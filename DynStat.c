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
    char * buf;
	
	printf(argv[1]);
	
	buf = (char*)malloc(sizeof(char)*size + 1);
	
	strncpy(buf, argv[2],  sizeof(buf));
	printf("buffer : %s\n", buf);
	
	/* ----------------------------------------------------- */
	/* On ne touche pas au contenu "testdubuffer"            */
    /* mais on peut créer une variable reprenant ce contenu  */
	/* ----------------------------------------------------- */
	strncpy(buf, "testdubuffer", sizeof(buf));	
	
	length = strlen(buf);
    if(length != 0)
        printf("buffer : %s\n", buf);
    else
        free(buf);
		
	return 0;
}
