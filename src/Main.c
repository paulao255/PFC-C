/* Importations: */
#include "C-Utils/cutils.h"
#include <stdio.h>
#include <string.h>


/* PFC version variables: */
#define PFC_FULL_VERSION  20260128 /* PFC full version variable (2026/01/28). */
#define PFC_MAJOR_VERSION 2026     /* PFC major version variable (2026).      */
#define PFC_MINOR_VERSION 1        /* PFC minor version variable (01).        */
#define PFC_PATCH_VERSION 28       /* PFC patch version variable (28).        */

/* Main code: */
int main(const int argc, const char *const argv[])
{
	/* Main variables: */
	int loop = 1; /* First loop variable. */

	while(loop == 1)
	{
		puts("=================================");
		printf("======== PFC v%.4d-%.2d-%.2d ========\n", PFC_MAJOR_VERSION, PFC_MINOR_VERSION, PFC_PATCH_VERSION);
		puts("=================================");
	}

	return 0;
}
