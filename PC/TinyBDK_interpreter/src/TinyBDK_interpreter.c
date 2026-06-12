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
#include "Editor.h"


char RAM[65536];
char testline[255];

int main(void) {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	edit_getLine(testline, 100);

	int res = file_load("testfile1.bas", RAM);
	printf("file_load() result = %d\n", res);
	Program(RAM);
	return EXIT_SUCCESS;
}
