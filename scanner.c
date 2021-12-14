#include <stdio.h>
#include "token.h"
#include "scanner.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include "table.h"

/*Author:   	Haley Neeter
 *Class:    	CS4280 Hauschild
 *Assignment:   Project 1 re-do
 *Date:     	12/1/21 */

//new scanner, it scanners token by token, not by file line
struct Token newScanner(FILE *fp)
{
    struct Token tok;
    char c;
    char word [15];
    memset(word, 0, 15);
    int length = 0;
    int state;
    int next;
    int first = 0;
    if(isEOF)
    {
        tok.inputLine = lineCount;
        tok.type = End;
        strcpy(tok.literal,"EOF");
        return tok;
    }
    while(1)
    {
        c = getc(fp);//added this to FINALLY be able to properly deal with comments
        if(c == '&')
        {
             c = getc(fp);
             if(c != '&')
             {
                printf("Scanner Error\n");
                printf("Line: %d\n",lineCount);
                printf("Reason: Comments must start with &&\n"); //Note- only works with single line comments
                deleteFile();
                exit( EXIT_FAILURE );
             }
             while(1)
             {
                c = getc(fp);
                if(c == '&')
                {
                    c = getc(fp);
                    if(c == '&')
                    {
                        break;
                    }
             
                    printf("Scanner Error\n");
                    printf("Line: %d\n",lineCount);
                    printf("Reason: Comments must end with &&\n");
                    deleteFile();
                    exit( EXIT_FAILURE );
                }
                
             }
             continue;
        }
        if(c == '\n')
        {
            lineCount++;
        }
        if(c == EOF)
        {
            isEOF = true;
        }
        next = isCharacter(c);
        if(next == -1)
        {
            printf("Scanner Error for Character %c\n",c);
            printf("Line: %d\n",lineCount);
            printf("Reason: Character is not allowed in this language\n");
            deleteFile();
            exit( EXIT_FAILURE );
        }
        else
        {
            state = FSA[first][next];
            if(state == -1)
            {//only error issue in states is with $
                printf("Scanner Error for Token %s\n",word);
                printf("Line: %d\n",lineCount);
                printf("Reason: $ symbol must be followed by an alphanumeric\n");
                deleteFile();
                exit( EXIT_FAILURE );

            }
            else if(state > 1000)
            {
                tok.inputLine = lineCount;
                tok.type = getState(state);
                strcpy(tok.literal,word);
                memset(word, 0, 15);
                newErrorHandle(tok);
                if(tok.type == Identifier)
                {
                    tok.type = getKeyword(tok);   
                }
                ungetc(c,fp);
                break;
            }
            else
            {
                first = state;
                if(!isspace(c))
                {
                    word[length] = c;
                    length++;
                }
            }

        }

    }
    return tok;


}


int isCharacter(char c) {

    if(isspace(c) || c == '\n' || c == '\t' || c == EOF)
    {
        return 21;
    }
    if(isalpha(c)){
        return 0;
    }


    if(isdigit(c)){
        return 1;
    }
    if(c == '.'){
        return 2;
    }

    if(c == ','){
        return 3;
    }
    if(c == ';'){
        return 4;
    }

    if(c == ':') {
        return 5;
    }

    if(c == '='){
        return 6;
    }
    if(c == '<'){
        return 7;
    }


    if(c == '>'){
        return 8;
    }

    if(c == '+'){
        return 9;
    }

    if(c == '-'){
        return 10;
    }

    if(c == '*'){
        return 11;
    }


    if(c == '/'){
        return 12;
    }

    if(c == '%'){
        return 13;
    }
    if(c == '('){
        return 14;
    }

    if(c == ')'){
        return 15;
    }


    if(c == '['){
        return 16;
    }

    if(c == ']'){
        return 17;
    }


    if(c == '{'){
        return 18;
    }

    if(c == '}'){
        return 19;
    }
    if(c == '$'){
        return 20;
    }

    return -1;	//illegal characters
}

void newIsKeyword(struct Token t)
{
    int j = 0;
    char *keywords[] = {"start","stop","loop","while","for","label","exit","listen","talk","program","if","then","assign","declare","jump","else" };
    Enums x; //Found this on geeksforGeeks, you can use enumerations in for loops
    for (x = Start; x <= Else; x++)
    {
        if(strcmp(t.literal,keywords[j]) == 0)
        {
            t.type = x;
            break;
        }
        j++;
    }
}
Enums getState(int state)
{
    Enums x = 0; //0 is the value of 'Identifier' keyword
    int i;
    for(i = 1001; i <= 1022; i++)
    {
        if(state == i)
        {
            return x;
        }
        x++;  //can also increase enums same as ints
    }
}


void newErrorHandle(struct Token t)
{
    int len = strlen(t.literal);
    if (len >= 8)
    {
        printf("Scanner Error for Token %s\n",t.literal);
        printf("Line: %d\n",t.inputLine);
        printf("Reason: Tokens cannot be longer than 8 characters\n");
        deleteFile();
        exit( EXIT_FAILURE );

    }


    if(t.type == Identifier)
    {

        if(!islower(t.literal[0]))
        {
            printf("Scanner Error for Token %s\n",t.literal);
            printf("Line: %d\n",t.inputLine);
            printf("Reason: Identifier must start with either a lowercase letter or a $\n");
            deleteFile();
            exit( EXIT_FAILURE );
        }
    }
}

char * enumToString(int i)
{
    char *enumWords[] = {"IDENTIFIER_TOKEN","INTEGER_TOKEN", "PERIOD_TOKEN", "COMMA_TOKEN", "SEMICOLON_TOKEN","COLON_TOKEN","EQUAL_TOKEN","LT_CARROT_TOKEN",
                         "RT_CARROT_TOKEN", "PLUS_TOKEN","MINUS_TOKEN","STAR_TOKEN","SLASH_TOKEN","PERCENT_TOKEN","LT_PARA_TOKEN","RT_PARA_TOKEN","LT_BRACKET_TOKEN",
                         "RT_BRACKET_TOKEN", "LT_CURL_TOKEN","RT_CURL_TOKEN","EQUAL_EQUAL_TOKEN","COLON_EQUAL_TOKEN","START_KEYWORD","STOP_KEYWORD","LOOP_KEYWORD",
                         "WHILE_KEYWORD","FOR_KEYWORD","LABEL_KEYWORD","EXIT_KEYWORD","LISTEN_KEYWORD","TALK_KEYWORD","PROGRAM_KEYWORD","IF_KEYWORD","THEN_KEYWORD",
                         "ASSIGN_KEYWORD","DECLARE_KEYWORD","JUMP_KEYWORD","ELSE_KEYWORD","EOF_TOKEN"};
    char* typeString = enumWords[i];
    return typeString;
}

Enums getKeyword(struct Token t)
{
    Enums x = 22; //22 is the value of first keyword enum 
    char *keywords[] = {"start","stop","loop","while","for","label","exit","listen","talk","program","if","then","assign","declare","jump","else" };
    int i;
    for(i = 0; i <= 15; i++)
    {
        if(strcmp(t.literal,keywords[i]) == 0)
        {
            return x;
        }
        x++;  //can also increase enums same as ints
    }
    return t.type;
}
void deleteFile()
{
    if(isKB)
    {
        remove("temp.txt");
    }
}
