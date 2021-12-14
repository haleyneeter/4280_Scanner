#include "stdio.h"
#include "errno.h"
#include "ctype.h"
#include "token.h"
#include "scanner.h"
#include "string.h"
#include "stdlib.h"


/*Author:   	Haley Neeter
 *Class:    	CS4280 Hauschild
 *Assignment:   Project 1 redo
 *Date:     	12/06/21 */

FILE *myFile = NULL;
int lineCount = 1;
bool isEOF = false;
bool isKB = false;
int main(int argc, char *argv[]) {

    char filename[20];
    char inputStream [500];


    if (argc >2) 
    {
        printf("Main Error: incorrect arguments\n");
        printf("To call scanner:\n");
        printf("FOR KEYBOARD INPUT:\t ./scanner\n");
        printf("FOR FILE INPUT:\t ./scanner [filename]\n");
        return 1;
    }
    else if(argc == 2)
    {
        strcat(argv[1], ".fall2021");
        strcpy(filename,argv[1]);
        myFile = fopen(filename,"r");
        if(myFile == NULL)
        {
            	printf("Main Error: fopen\n");
            	return 1;
       }   
    }
    else if(argc == 1)
    {
	char flag;
	isKB = true;
    	printf("KEYBOARD INPUT: USE @ KEY (SHIFT + 2) TO STOP WRITING\n");
	FILE * fp = fopen("temp.txt","w");
        flag = getc(stdin);
        while (flag != '@') 
    	  {
       		  fprintf(fp,"%c",flag);
       		  flag = getc(stdin);
    	  }

    	fclose(fp);
        myFile = fopen("temp.txt","r");
        if(myFile == NULL)
        {
            printf("Main Error: fopen\n");
            return 1;
        } 
    }


    while(1) 
    {
        struct Token t = newScanner(myFile); 
        printf("Token:\t%s\n",t.literal);
        printf("Type:\t%s\n",enumToString(t.type));
        printf("Line:\t%d\n",t.inputLine);
        if(t.type == End)
        {
            break;
        }
    }

    fclose(myFile);
    if(isKB)
    {
        remove("temp.txt");
    }
    return 0;
}
