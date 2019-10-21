/*
 ============================================================================
 Name        : HW1.c
 Author      : Katie Lin
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tests.h"
#include "production.h"


int main(int argc, char*argv[]) {
	bool ok=false;
	printf("!!!Hello World We're doing HW1!!!\n");

	if(tests())
	{
		ok=production(argc, argv);
		if (ok)
		{
			printf("\nProduction seems to have worked.\n");
		}
		else
		{
			printf("\nProduction seems not to have worked.\n");
		}
	}
	else
	{
		printf("Something went wrong in the tests.\n");
	}

	return EXIT_SUCCESS;
}
