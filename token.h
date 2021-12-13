#ifndef TOKEN_H
#define TOKEN_H

/*Author:   	Haley Neeter
  Class:    	CS4280 Hauschild
  Assignment:   Project 1 re-do
  Date:     	12/1/21 */

#include <stdbool.h>

typedef enum {Identifier,Integer,Period,Comma,
              Semicolon,Colon,Equal,Left_Carrot,
              Right_Carrot,Plus,Minus,Star,
              Slash,Percent,Left_Para,Right_Para,
              Left_Bracket,Right_Bracket,Left_Curl,Right_Curl,
              Equal_Equal,Colon_Equal,Start,Stop,
              Loop,While,For,Label,
              Exit,Listen,Talk,Program,
              If,Then,Assign,Declare,
              Jump,Else,End} Enums;

struct Token {
    Enums type;
    char literal[100];
    int inputLine;
} ;


extern FILE *myFile;
extern int lineCount;
extern bool isEOF;
#endif
