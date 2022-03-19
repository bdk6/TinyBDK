/*
 * Parser.c
 *
 *  Created on: Mar 18, 2022
 *      Author: wrcooke
 */

#include <stddef.h>
#include "Parser.h"
#include "Scanner.h"


static int currentLine = -1;
static int nextLine = -1;

static int currentTok = TOK_UNDEFINED;




int do_line(void);
int do_line_number(void);
int do_statement(void);
int do_let_st(void);
int do_print_st(void);
int do_input_st(void);
int do_goto_st(void);
int do_gosub_st(void);
int do_rem_st(void);
int do_return_st(void);
int do_run_st(void);
int do_if_st(void);
int do_end_st(void);
int do_expression(void);
int do_relation(void);
int do_term(void);
int do_factor(void);



//////////////////////////////////////////////////////////////////////////////
/// @fn Program
/// @brief Top level parser entry function
/// @param[inout] memory  Pointer to the program storage area
/// @return 0 on success, error code if unsuccesful
/// //////////////////////////////////////////////////////////////////////////
int Program(char* memory)
{
  int rtn = 0;
  currentTok = scan(memory);
  printf("Parser: Program\n");
  do_line();


  return rtn;
}

/////////////////////////////////////////////////////////////////////////////
/// @fn do_line
/// @brief Parse a line of the program
/// @return 0 on success or error code
/// /////////////////////////////////////////////////////////////////////////
int do_line(void)
{
  int rtn = 0;

  do_line_number();
  do_statement();
  // TODO: End of line

  return rtn;
}

//////////////////////////////////////////////////////////////////////////////
/// @fn do_line_number
/// @brief Parse a line number
/// @return 0 on success or error code
/// //////////////////////////////////////////////////////////////////////////
int do_line_number(void)
{
  int rtn = 0;

  if(currentTok == TOK_INTEGER)
  {
    // all is good
    printf("Line number is %d \n", scan_getValue());
  }
  else
  {
    // ? error
    rtn = -1;
  }

  currentTok = scan(NULL);

  return rtn;
}

/////////////////////////////////////////////////////////////////////////////
/// @fn do_statement
/// @brief Parse a generic statement and call appropriate function
/// @return 0 on success or error code
/// /////////////////////////////////////////////////////////////////////////
int do_statement(void)
{
  int rtn = 0;

  switch(currentTok)
  {
  case TOK_END:
    currentTok = scan(NULL);
    printf("END statement\n");
    break;
  case TOK_GOSUB:
    currentTok = scan(NULL);
    printf("GOSUB statement\n");
    break;
  case TOK_GOTO:
    currentTok = scan(NULL);
    printf("GOTO statement\n");
    break;
  case TOK_IF:
    currentTok = scan(NULL);
    printf("IF statement\n");
    break;
  case TOK_INPUT:
    currentTok = scan(NULL);
    printf("INPUT statement\n");
    break;
  case TOK_LET:
    currentTok = scan(NULL);
    printf("LET statement\n");
    do_let_st();
    break;
  case TOK_PRINT:
    currentTok = scan(NULL);
    printf("PRINT statement\n");
    break;
  case TOK_REM:
    currentTok = scan(NULL);
    printf("REM statement\n");
    break;
  case TOK_RETURN:
    currentTok = scan(NULL);
    printf("RETURN statement\n");
    break;
  case TOK_RUN:
    currentTok = scan(NULL);
    printf("RUN statement\n");
    break;
  default:
    printf("PARSE ERROR!");
    rtn = -1;
    break;
  }

  return rtn;
}

/////////////////////////////////////////////////////////////////////////////
/// @fn do_let_st
/// @brief Parses a LET (assignment) statement
/// @return 0 on success or error code
/// /////////////////////////////////////////////////////////////////////////
int do_let_st(void)
{
  int rtn = 0;
  int varTok = TOK_UNDEFINED;

  switch(currentTok)
  {
  case 'A':
  case 'B':
  case 'C':
  case 'D':
  case 'E':
  case 'F':
  case 'G':
  case 'H':
  case 'I':
  case 'J':
  case 'K':
  case 'L':
  case 'M':
  case 'N':
  case 'O':
  case 'P':
  case 'Q':
  case 'R':
  case 'S':
  case 'T':
  case 'U':
  case 'V':
  case 'W':
  case 'X':
  case 'Y':
  case 'Z':
    varTok = currentTok;  // save it for later
    currentTok = scan(NULL);
    printf("Found variable \"%c\" \n", varTok);
    if(currentTok == '=')
    {
      // all is good
      printf("Found =\n");
      currentTok = scan(NULL);
      // do expression now
    }
    else
    {
      rtn = -1;
      printf("PARSE ERROR: expect \"=\" here \n");
    }
    break;
  default:
    rtn = -1;
    printf("PARSE ERROR expected variable\n");
    break;
  }

  return rtn;
}

/////////////////////////////////////////////////////////////////////////////
/// @fn do_print_st
/// @brief Parse a PRINT statement
/// @return 0 on success or error code
/// /////////////////////////////////////////////////////////////////////////
int do_print_st(void)
{
  int rtn = 0;

  return rtn;
}

int do_input_st(void)
{
  int rtn = 0;

  return rtn;
}

int do_goto_st(void)
{
  int rtn = 0;

  return rtn;
}

int do_gosub_st(void)
{
  int rtn = 0;

  return rtn;
}

int do_rem_st(void)
{
  int rtn = 0;


  return rtn;

}

int do_return_st(void)
{
  int rtn = 0;

  return rtn;
}

int do_run_st(void)
{
  int rtn = 0;

  return rtn;
}

int do_if_st(void)
{
  int rtn = 0;

  return rtn;
}

int do_end_st(void)
{
  int rtn = 0;

  return rtn;
}


int do_expression(void)
{
  int rtn = 0;

  return rtn;
}

int do_relation(void)
{
  int rtn = 0;

  return rtn;
}

int do_term(void)
{
  int rtn = 0;

  return rtn;
}

int do_factor(void)
{
  int rtn = 0;

  return rtn;
}







