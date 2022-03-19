/*
 * Scanner.c
 *
 *  Created on: Mar 14, 2022
 *      Author: wrcooke
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include "Scanner.h"


static int integerValue = -1;

//////////////////////////////////////////////////////////////////////////////
/// @fn scan
/// @brief Scan the next token from a line.
/// @param[in] line Pointer to line to scan.  NULL to keep scanning previous.
/// @return Integer representing the token. Single char tokens return char.
/// //////////////////////////////////////////////////////////////////////////
int scan(char* line)
{
  static char* linePtr = NULL;
  static int lineIndex = 0;
  static int lineLength = 0;

  int tok = TOK_UNDEFINED;
  integerValue = -1;

  if(line != NULL)   // Did we get a new line?
  {
    linePtr = line;
    lineIndex = 0;
    lineLength = strlen(line);
  }
  else
  {
    printf("NULL line ptr\n");
    printf("lineIndex = %d, lineLength = %d \n", lineIndex, lineLength);
  }

  char ch = linePtr[lineIndex];
  printf("ch = %d\n", ch);

  // skip whitespace (spaces and tabs)
  while((ch == ' ' || ch == '\t') && lineIndex < lineLength)
  {
    lineIndex++;
    printf("WH: idx = %d\n", lineIndex);
    ch = linePtr[lineIndex];
    printf("WH: %d, %d\n", ch, lineIndex);
  }

  // ch should be the first character of the next token
  switch(ch)
  {
  // Integer
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
    tok = TOK_INTEGER;
    integerValue = 0;
    printf("FND:INT: ");
    do
    {
      integerValue = integerValue * 10 + ch - '0';
      lineIndex++;
      ch = linePtr[lineIndex];
    } while(isdigit(ch));
    printf("%d\n", integerValue);
    break;

    // Variables
  case 'A':
  case 'B':
  case 'C':
  case 'D':
  //case 'E':  // END
  case 'F':
  //case 'G':  // GOTO, GOSUB
  case 'H':
  //case 'I':  // IF
  case 'J':
  case 'K':
  //case 'L':  // LET
  case 'M':
  case 'N':
  case 'O':
  case 'P':
  case 'Q':
  //case 'R':  // RETURN, REM
  case 'S':
  //case 'T':  // THEN
  case 'U':
  case 'V':
  case 'W':
  case 'X':
  case 'Y':
  case 'Z':
    // Variable
    tok = ch;     // For all these the token is simply the letter
    lineIndex++;  // move to next character
    break;

  case 'E':  // All tokens starting with "E": E, END
    // Start by assuming variable "E"
    tok = ch;
    lineIndex++;
    // Now see if it is actually "END"
    if(lineIndex + 1 < lineLength && linePtr[lineIndex] == 'N'
        && linePtr[lineIndex + 1] == 'D')
    {
      tok = TOK_END;
      lineIndex += 2;  // skip N and D
    }
    break;

  case 'G':  // All tokens starting with "G": G, GOSUB, GOTO
    // Start by assuming variable "G"
    tok = ch;
    lineIndex++;
    // Now see if it is actually "GOTO"
    if(lineIndex + 2 < lineLength && linePtr[lineIndex] == 'O'
       && linePtr[lineIndex + 1] == 'T' && linePtr[lineIndex + 2] == 'O')
    {
      tok = TOK_GOTO;
      lineIndex += 3;  // skip O and T and O
    }
    // Now see if it is actually "GOSUB
    else if(lineIndex + 4 < lineLength && linePtr[lineIndex] == 'O'
            && linePtr[lineIndex + 1] == 'S' && linePtr[lineIndex + 2] == 'U'
            && linePtr[lineIndex + 3] == 'B' )
    {
      tok = TOK_GOSUB;
      lineIndex += 4;  // Skip O,S,U, and B
    }
    break;
  case 'I':  // All tokens starting with "I": I, IF
    // Start by assuming variable "I"
    tok = ch;
    lineIndex++;
    // Now see if it is actually "IF"
    if(lineIndex < lineLength && linePtr[lineIndex] == 'F')
    {
      tok = TOK_IF;
      lineIndex++;  // Skip the F
    }
    break;

  case 'L':  // All tokens starting with "L": L, LET
    // Start by assuming variable "L"
    tok = ch;
    lineIndex++;
    // Now see if it is actually "LET"
    if(lineIndex + 1 < lineLength && linePtr[lineIndex] == 'E'
       && linePtr[lineIndex + 1] == 'T')
    {
      tok = TOK_LET;
      lineIndex += 2;  // skip E and T
    }
    break;

  case 'R':  // All tokens starting with "R": R, REM, RETURN
    // Start by assuming variable "R"
    tok = ch;
    lineIndex++;
    // Now see if it is actually "REM"
    if(lineIndex + 1 < lineLength && linePtr[lineIndex] == 'E'
       && linePtr[lineIndex + 1] == 'M')
    {
      tok = TOK_REM;
      lineIndex += 2;  // skip E and M
    }
    // Now see if it is "RETURN"
    else if(lineIndex + 4 < lineLength && linePtr[lineIndex] == 'E'
            && linePtr[lineIndex + 1] == 'T' && linePtr[lineIndex + 2] == 'U'
            && linePtr[lineIndex + 3] == 'R' && linePtr[lineIndex + 4] == 'n')
    {
      tok = TOK_RETURN;
      lineIndex += 5;
    }
    break;

  case 'T':  // All tokens starting with "T": T, THEN
    // Start by assuming it is variable "T"
    tok = ch;
    lineIndex++;
    // Now see if it is actually "THEN"
    if(lineIndex + 2 < lineLength && linePtr[lineIndex] == 'H'
       && linePtr[lineIndex + 1] == 'E' && linePtr[lineIndex + 2] == 'N')
    {
      tok = TOK_THEN;
      lineIndex += 3;
    }
    break;


  // Single char operators that don't start other tokens
  case '+':
  case '-':
  case '*':
  case '/':
  case '(':
  case ')':
  case '=':
  case ',':
  case '\n':
    // Single character operators
    tok = ch;    // For all these, too, the token is simply the character
    lineIndex++;
    break;

  case '<':  // All tokens starting with "<": <, <=, <>
    // Start by assuming it is "<"
    tok = ch;
    lineIndex++;
    if(lineIndex < lineLength )
    {
      // Check for "<="
      if(linePtr[lineIndex] == '=')
      {
        tok = TOK_LESS_EQ;
        lineIndex++;
      }
      // Check for "<>"
      else if(linePtr[lineIndex] == '>')
      {
        tok = TOK_NOT_EQ;
        lineIndex++;
      }
    }
    break;

  case '>':  // All tokens that start with ">": >, >=, ><
    // Start by assuming it is ">"
    tok = ch;
    lineIndex++;
    if(lineIndex < lineLength)
    {
      // Check for ">="
      if(linePtr[lineIndex] == '=')
      {
        tok = TOK_GREATER_EQ;
        lineIndex++;
      }
      // Check for "><"  (alt version of not equal
      else if(linePtr[lineIndex] == '<')
      {
        tok = TOK_NOT_EQ;
        lineIndex++;
      }
    }

    break;


  default:
    // Error
    printf("\nDefault: tok value is %d\n", tok);
    printf("Char is %d\n", linePtr[lineIndex]);
    printf("Line Length is %d\n", lineLength);

    tok = TOK_UNDEFINED;
    // Skip bad character
    lineIndex++;
    printf("Scanning error in line at position %d\n", lineIndex);
    printf("%s", linePtr);
    for(int i = 0; i < lineIndex; i++)
    {
      putchar(' ');
    }
    putchar('^');
    break;
  }
  return tok;
}

int scan_getValue(void)
{
  return integerValue;
}
