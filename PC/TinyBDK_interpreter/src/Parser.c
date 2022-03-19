/*
 * Parser.c
 *
 *  Created on: Mar 18, 2022
 *      Author: wrcooke
 */

#include <stdio.h>
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
      do_expression();
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
  // PRINT_ST = "PRINT" [EXPRESSION { "," EXPRESSION } ] .
  // TODO revisit!
  do_expression();
  while(currentTok == ',')
  {
    currentTok = scan(NULL);
    do_expression();
  }

  return rtn;
}

/////////////////////////////////////////////////////////////////////////////
/// @fn do_input_st
/// @brief Parse an INPUT statement
/// @return 0 on success or error code
/// /////////////////////////////////////////////////////////////////////////
int do_input_st(void)
{
  int rtn = 0;
  // INPUT_ST = "INPUT" VAR { "," VAR }.
  do
  {
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
      // do whatever
      printf("INPUT variable %c\n", currentTok);
      scan(NULL);
      break;
    default:
      // Error
      printf("Parse ERROR: expected a variable here\n");
      scan(NULL);
    }
  }while(currentTok == ',');

  return rtn;
}

/////////////////////////////////////////////////////////////////////////////
/// @fn do_goto_st
/// @brief Parses a GOTO statement
/// @return 0 on success or error code
/// /////////////////////////////////////////////////////////////////////////
int do_goto_st(void)
{
  int rtn = 0;
  // GOTO_ST = "GOTO" LINE_NUMBER .
  do_line_number();

  return rtn;
}

/////////////////////////////////////////////////////////////////////////////
/// @fn do_gosub_st
/// @brief Parses a GOSUB statement
/// @return 0 on success or error code
/// /////////////////////////////////////////////////////////////////////////
int do_gosub_st(void)
{
  int rtn = 0;
  // GOSUB_ST = "GOSUB" LINE_NUMBER .
  do_line_number();

  return rtn;
}

/////////////////////////////////////////////////////////////////////////////
/// @fn do_rem_st
/// @brief Parses a REM statement
/// @return 0 on success or error code
/// /////////////////////////////////////////////////////////////////////////
int do_rem_st(void)
{
  int rtn = 0;
  // REM_ST = "REM" chars .
  // We don't do anything here except skip to end of the line

  return rtn;
}

/////////////////////////////////////////////////////////////////////////////
/// @fn do_return_st
/// @brief Parses a RETURN statement
/// @return 0 on success or error code
/// /////////////////////////////////////////////////////////////////////////
int do_return_st(void)
{
  int rtn = 0;
  // RETURN_ST = "RETURN" .

  return rtn;
}

/////////////////////////////////////////////////////////////////////////////
/// @fn do_run_st
/// @brief Parses a RUN statement
/// @return 0 on success or error code
/// /////////////////////////////////////////////////////////////////////////
int do_run_st(void)
{
  int rtn = 0;
  // RUN_ST = "RUN" .
  //

  return rtn;
}

/////////////////////////////////////////////////////////////////////////////
/// @fn do_if_st
/// @brief Parses an "IF" statement
/// @return 0 on success or error code
/// /////////////////////////////////////////////////////////////////////////
int do_if_st(void)
{
  int rtn = 0;
  // IF_ST = "IF" EXPRESSION [ "THEN" ] STATEMENT .
  do_expression();
  if(currentTok == "TOK_THEN")
  {
    // THEN is optional so skip over it
    currentTok = scan(NULL);
  }
  do_statement();

  return rtn;
}

/////////////////////////////////////////////////////////////////////////////
/// @fn do_end_st
/// @brief Parses an END statement
/// @return 0 on success or error code
/// /////////////////////////////////////////////////////////////////////////
int do_end_st(void)
{
  int rtn = 0;
  // END_ST = "END" .

  return rtn;
}

/////////////////////////////////////////////////////////////////////////////
/// @fn do_expression
/// @brief Parses an EXPRESSION
/// @return 0 on success or error code
/// /////////////////////////////////////////////////////////////////////////
int do_expression(void)
{
  int rtn = 0;
  printf("EXPRESSION \n");
  // EXPRESSION = RELATION { RELOP RELATION } .
  do_relation();
  while(currentTok == '<' || currentTok == '>' || currentTok == '='
      || currentTok == TOK_LESS_EQ || currentTok == TOK_GREATER_EQ
      || currentTok == TOK_NOT_EQ)
  {
    currentTok = scan(NULL);
    do_relation();
  }

  return rtn;
}

/////////////////////////////////////////////////////////////////////////////
/// @fn do_relation
/// @brief Parses a RELATION
/// @return  0 on success or error code
/// /////////////////////////////////////////////////////////////////////////
int do_relation(void)
{
  int rtn = 0;
  printf("RELATION \n");
  // RELATION = TERM { ADDOP TERM }
  do_term();
  while(currentTok == '+' || currentTok == '-')
  {
    currentTok = scan(NULL);
    do_term();
  }

  return rtn;
}

/////////////////////////////////////////////////////////////////////////////
/// @fn do_term
/// @brief Parses a TERM
/// @return 0 on success or error code
/// /////////////////////////////////////////////////////////////////////////
int do_term(void)
{
  int rtn = 0;
  printf("TERM \n");
  // TERM = FACTOR { MULOP FACTOR } .
  do_factor();
  while(currentTok == '*' || currentTok == '/')
  {
    currentTok = scan(NULL);
    do_factor();
  }

  return rtn;
}

/////////////////////////////////////////////////////////////////////////////
/// @fn do_factor
/// @brief Parses a FACTOR
/// @return 0 on success or error code
/// /////////////////////////////////////////////////////////////////////////
int do_factor(void)
{
  int rtn = 0;
  printf("FACTOR \n");
  // FACTOR = VAR
  //        || INTEGER
  //        || "(" EXPRESSION ")"
  //        || "-" FACTOR .

  if(currentTok == 'A' || currentTok == 'B' || currentTok == 'C'
      || currentTok == 'D' || currentTok == 'E' || currentTok == 'F'
      || currentTok == 'G' || currentTok == 'F' || currentTok == 'H'
      || currentTok == 'I' || currentTok == 'J' || currentTok == 'K'
      || currentTok == 'L' || currentTok == 'M' || currentTok == 'N'
      || currentTok == 'O' || currentTok == 'P' || currentTok == 'Q'
      || currentTok == 'R' || currentTok == 'S' || currentTok == 'T'
      || currentTok == 'U' || currentTok == 'V' || currentTok == 'W'
      || currentTok == 'X' || currentTok == 'Y' || currentTok == 'Z')
  {
    currentTok == scan(NULL);
    printf("Factor is a var\n");
  }
  else if(currentTok == TOK_INTEGER)
  {
    currentTok == scan(NULL);
    printf("Factor is an integer\n");
  }
  else if(currentTok == '(')
  {
    currentTok = scan(NULL);
    printf("Factor is recursive ( \"(expression)\" \n");
    do_expression();
    if(currentTok != ')')
    {
      printf("Parse Error: expected \"(\" here \n");
      rtn = -1;
    }
  }
  else if(currentTok == '-')
  {
    currentTok = scan(NULL);
    printf("Factor is a negation \"-factor\"\n");
    do_factor();
  }

  return rtn;
}







