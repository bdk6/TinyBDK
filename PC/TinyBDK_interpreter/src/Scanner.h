/*
 * Scanner.h
 *
 *  Created on: Mar 14, 2022
 *      Author: wrcooke
 */

#ifndef SCANNER_H_
#define SCANNER_H_

enum Tokens
{
  TOK_UNDEFINED  = 0,
  TOK_INTEGER = 256,
  TOK_END,
  TOK_GOSUB,
  TOK_GOTO,
  TOK_IF,
  TOK_INPUT,
  TOK_LET,
  TOK_PRINT,
  TOK_REM,
  TOK_RETURN,
  TOK_RUN,
  TOK_THEN,
  TOK_LESS_EQ,
  TOK_GREATER_EQ,
  TOK_NOT_EQ,

 // TOK_NEWLINE,

  TOK_LAST
};

int scan(char* line);
int scan_getValue(void);


#endif /* SCANNER_H_ */
