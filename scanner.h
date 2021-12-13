#ifndef SCANNER_H
#define SCANNER_H

/*Author:   	Haley Neeter
 *Class:    	CS4280 Hauschild
 *Assignment:   Project 1 re-do
 *Date:     	12/1/21 */

char * enumToString(int i);
int isCharacter(char c);
Enums getState(int state);
struct Token newScanner(FILE *fp);
void newErrorHandle(struct Token t);
Enums getKeyword(struct Token t);

#endif

