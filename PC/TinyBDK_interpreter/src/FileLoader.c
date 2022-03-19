/*
 * FileLoader.c
 *
 *  Created on: Mar 11, 2022
 *      Author: wrcooke
 */

#include "FileLoader.h"
#include <stdio.h>
#include "Scanner.h"

#define MAX_LINE_LENGTH    255

FILE* inputFile;
uint8_t line[MAX_LINE_LENGTH + 1];

/////////////////////////////////////////////////////////////////////////////
/// @fn getLine
/// @brief Read a line from the input file into line[] array
/// @return Number of chars read, negative if end of file is reached
/////////////////////////////////////////////////////////////////////////////
static int getLine()
{
  int rtn = 0;
  int index = 0;
  int ch;
  do
  {
    ch = fgetc(inputFile);
    if(ch == '\n')
    {
  //   printf("\nGOT NL\n");
    }

    // Filter out illegal characters
    if(ch == '\r')
    {
      ch = '\n';
    }
    else if(ch == '\t')
    {
      // don't do anything
    }
    else if(ch == '\n')
    {
      // Keep newline from getting erased below
    }
    else if(ch < ' ' && ch > 0 || ch > 126)
    {
      ch = ' ';
    }

    if(index < MAX_LINE_LENGTH && ch != EOF)
    {
      line[index++] = (uint8_t) ch;
    }

    // Exit loop on end of line
    if(ch == '\n')
    {
 //     printf("\n Got NEWLINE\n");
      break;
    }
  }while(ch != EOF);

  line[index] = 0;
  if(ch == EOF)
  {
    rtn = -index;
    printf("rtn is %d \n", rtn);
  //  while(1);
  }
  else
  {
    rtn = index;
  }

  return rtn;
}

/////////////////////////////////////////////////////////////////////////////
///  @fn file_load
///  @brief Load a file into memory
/// @param[in] filename Name (and path) of file to load
/// @param[in] mem Array to store file text into
/// @return Number of characters read
/////////////////////////////////////////////////////////////////////////////
int file_load(char* filename, uint8_t* mem)
{
  int rtn = 0;
  inputFile = fopen(filename, "r");
  int nextLine = 0;
  int MAX = 65535;

  if(inputFile != NULL)
  {
    printf("Opened %s, reading now...\n", filename);
    int lineLength;
    do
    {
      lineLength = getLine();
      printf("%3d: %s \n", lineLength, line);
      int actualLineLength = lineLength;
      if(actualLineLength < 0)
      {
        actualLineLength = -actualLineLength;
      }
      strcpy(&mem[nextLine], line);

      // Get first token
      int res = scan(line);
      printf("First TOK: %d\n", res);
      do
      {
        res = scan(NULL);
        printf("TOK: %d, VAL: %d\n", res, scan_getValue());
      } while(res != '\n');

      nextLine += actualLineLength;
 //     printf("Read %d characters\n", lineLength);
    } while(lineLength > 0);
    printf("...Done\n");
    printf("Here are the contents(%d):\n\n", nextLine);
    for(int i = 0; i < nextLine; i++)
    {
      int ch = mem[i];
      printf("%c", ch);
    }
    printf("<<<That's all, folks!\n");

  }
  else
  {
    printf("Could not open %s \n", filename);
  }


  fclose(inputFile);
  return rtn;
}
