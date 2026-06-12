/*
 * Editor.c
 *
 *  Created on: Mar 19, 2022
 *      Author: wrcooke
 */

#include <stdio.h>

#define BACKSPACE        8
#define NEWLINE         10
#define RETURN          13
#define TAB              9


/////////////////////////////////////////////////////////////////////////////
/// @fn edit_getLine
/// @brief Gets an input line typed at the terminal.
/// @param[out] buff Place to put the characters.
/// @param[in] maxLength The maximum number of chars we can store.
/// @return Number of characters read or -1 on error.
/// /////////////////////////////////////////////////////////////////////////
int edit_getLine(char* buff, int maxLength)
{
  int rtn = 0;
  if(buff == NULL)
  {
    rtn = -1;  // No place to put it!
  }
  else
  {
    int idx = 0;
    int ch = 0;
    int endOfLine = 0;

    do
    {
      ch = getchar();
      if(ch == BACKSPACE)
      {

      }
      else if(ch == TAB)
      {

      }
      else if(ch == RETURN)
      {
        endOfLine = 1;
      }
      else if(ch == NEWLINE)
      {
        endOfLine = 1;
      }
      else if(ch < ' ')
      {

      }
      else
      {

      }

    }while(!endOfLine);
    printf("End of Line: %d \n", ch);

  }

  return rtn;
}
