/*
 ============================================================================
 Name        : TinyBDK_interpreter.c
 Author      : Will Cooke
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>


#include "FileLoader.h"
#include "Parser.h"


char RAM[65536];

int main(void) {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	int res = file_load("testfile1.bas", RAM);
	printf("file_load() result = %d\n", res);
	Program(RAM);
	return EXIT_SUCCESS;
}
