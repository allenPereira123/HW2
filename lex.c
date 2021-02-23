#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define SYMBOL_COUNT 17
#define RESERVED_WORDS_COUNT 15
#define IDENTIFIER_TOKEN 2
#define NUMBER_TOKEN 3



typedef struct TokenType{
    int token;
    char symbol [20];
}TokenType;

void initSymbols(TokenType *symbolsArray)
{
    int tokenVal = 1;
    int i = 0;

    while (i < SYMBOL_COUNT)
    {
      // token 8 is for reserved word odd
      if (tokenVal == 8)
          tokenVal++;
      // token 2 and 3 are for identifier or numbers
      else if (tokenVal == 2)
          tokenVal = 4;
      else
      {
          symbolsArray[i].token = tokenVal;
          tokenVal++;
          i++;
      }
    }

    strcpy(symbolsArray[0].symbol,"%");
    strcpy(symbolsArray[1].symbol,"+");
    strcpy(symbolsArray[2].symbol,"-");
    strcpy(symbolsArray[3].symbol,"*");
    strcpy(symbolsArray[4].symbol,"/");
    strcpy(symbolsArray[5].symbol,"=");
    strcpy(symbolsArray[6].symbol,"<>");
    strcpy(symbolsArray[7].symbol,"<");
    strcpy(symbolsArray[8].symbol,"<=");
    strcpy(symbolsArray[9].symbol,">");
    strcpy(symbolsArray[10].symbol,">=");
    strcpy(symbolsArray[11].symbol,"(");
    strcpy(symbolsArray[12].symbol,")");
    strcpy(symbolsArray[13].symbol,",");
    strcpy(symbolsArray[14].symbol,";");
    strcpy(symbolsArray[15].symbol,".");
    strcpy(symbolsArray[16].symbol,":=");

    //for (int i = 0; i < SYMBOL_COUNT; i++)
        //printf("id: %s symbol: %s token %d\n",symbolsArray[i].id,symbolsArray[i].symbol,symbolsArray[i].token);
}

void initReserved(TokenType * reservedWords)
{
    int i = 0, tokenVal = 8; // token vals 21 - 31

    while (i < RESERVED_WORDS_COUNT)
    {
        if (tokenVal == 8) // odd starts at 8, jump to 21 after
        {
            reservedWords[i].token = tokenVal;
            tokenVal = 21;
        }
        else
        {
            reservedWords[i].token = tokenVal;
            tokenVal++;
        }
        i++;
    }

    strcpy(reservedWords[0].symbol,"odd");
    strcpy(reservedWords[1].symbol,"begin");
    strcpy(reservedWords[2].symbol,"end");
    strcpy(reservedWords[3].symbol,"if");
    strcpy(reservedWords[4].symbol,"then");
    strcpy(reservedWords[5].symbol,"while");
    strcpy(reservedWords[6].symbol,"do");
    strcpy(reservedWords[7].symbol,"call");
    strcpy(reservedWords[8].symbol,"const");
    strcpy(reservedWords[9].symbol,"var");
    strcpy(reservedWords[10].symbol,"procedure");
    strcpy(reservedWords[11].symbol,"write");
    strcpy(reservedWords[12].symbol,"read");
    strcpy(reservedWords[13].symbol,"else");
    strcpy(reservedWords[14].symbol,"return");

    //for (int i = 0; i < RESERVED_WORDS_COUNT; i++)
        //printf("symbol: %s  token: %d\n",reservedWords[i].symbol,reservedWords[i].token);
}

int findReservedToken(char *word, TokenType *reservedWords)
{
  for (int i = 0; i < RESERVED_WORDS_COUNT; i++)
  {
      if (strcmp(reservedWords[i].symbol,word) == 0)
          return reservedWords[i].token;
  }

  return -1;
}

int checkSymbol(TokenType * symbols, char *str)
{
    for (int i = 0; i < SYMBOL_COUNT; i++)
    {
        if (strcmp(symbols[i].symbol,str) == 0)
            return 1;
    }

    return 0;
}

int checkIfReservedWord(char *word, TokenType *reservedWords)
{
  for (int i = 0; i < RESERVED_WORDS_COUNT; i++)
  {
      if (strcmp(reservedWords[i].symbol,word) == 0)
          return 1;
  }

  return 0;
}

int main(int argc, char **argv)
{
    TokenType * symbols = (malloc(sizeof(TokenType) * SYMBOL_COUNT));
    TokenType * reservedWords = (malloc(sizeof(TokenType) * RESERVED_WORDS_COUNT));
    FILE * file_ptr = fopen("testertest.txt", "r");
    char buffer [500];
    int count = 0;

    initSymbols(symbols);
    initReserved(reservedWords);


   while (1)
   {
     char c = fgetc(file_ptr) ; // reading the file
     if ( c == EOF )
      break ;

      buffer[count] = c;
      count++;
   }

   buffer[count] = '\0';
   int pos = 0;
   int category = 0;

   while (pos != count)
   {
     if (isalpha(buffer[pos]))
     {
       category = 1;
     }
     else
     {
       pos++;
       continue;
     }


     switch(category)
     {
       case 1:
       {
         char temp_buffer[12];
         int temp_pos = 0;

         temp_buffer[temp_pos] = buffer[pos];
         pos++;
         temp_pos++;
         int more_than_11 = 0;
         int print_message = 0;

         while (1)
         {

           if (temp_pos < 11 && (isdigit(buffer[pos]) ||  isalpha(buffer[pos])))
           {
             temp_buffer[temp_pos] = buffer[pos];
             pos++;
             temp_pos++;
           }
           else if (temp_pos >= 11 && (isalpha(buffer[pos]) || isdigit(buffer[pos])))
           {


             pos++;

             if (print_message == 0)
             {
               more_than_11 =1;
               printf("Error : Identifier names cannot exceed 11 characters\n");
               print_message = 1;
             }
           }
           else if (!isalpha(buffer[pos]) && !isdigit(buffer[pos]) &&  more_than_11 == 1)
           {
             break;
           }
           else if (!isalpha(buffer[pos]) && !isdigit(buffer[pos]) &&  more_than_11 == 0)
           {
             temp_buffer[temp_pos] = '\0';
             if (checkIfReservedWord(temp_buffer,reservedWords))
             {
               printf("%s     %d\n", temp_buffer, findReservedToken(temp_buffer, reservedWords));
               break;
             }
             else
             {
               printf("%s       %d\n", temp_buffer, IDENTIFIER_TOKEN);
               break;
             }
           }
         }
       }
     }
   }
  return 0;
}
