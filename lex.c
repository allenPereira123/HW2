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

int findSymbolToken(char *s, TokenType *symbols)
{
  for (int i = 0; i < SYMBOL_COUNT; i++)
  {
      if (strcmp(symbols[i].symbol,s) == 0)
          return symbols[i].token;
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
     else if (isdigit(buffer[pos]))
     {
       category = 2;
     }
     else if (iscntrl(buffer[pos]) != 0 || isspace(buffer[pos]) != 0)
     {
       pos++;
       continue;
     }
     else
     {
        category = 3;
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
         break;
       }

       case 2 :
       {
         char temp_buffer [6];
         int temp_pos = 0;
         int length = 0, length_error = 0, alpha_error = 0;

         temp_buffer[temp_pos] = buffer[pos];
         pos++;
         temp_pos++;
         length++;

         while (1)
         {
          // breaks out of loop when a non numeric character is scanned
          if (!isalpha(buffer[pos]) && !isdigit(buffer[pos]))
          {
            break;
          }
          /* if the length of the temp_buffer is already 5 and we are here in the loop,
             it means that we are going to read in a 6th char which means it will encounter length error
          */
          else if (length == 5 && !length_error && !alpha_error)
          {
            length_error = 1;
            printf("Error : Numbers cannot exceed 5 digits\n");
          }
          // non digit error occurs if a supposed number contains a alphabetic character
          else if (isalpha(buffer[pos]) && !alpha_error && !length_error)
          {
            alpha_error = 1;
            printf("Error : Identifiers cannot begin with a digit\n");
          }

          // no error has occured, therefore copy into temp buffer
          if (!length_error && !alpha_error)
            temp_buffer[temp_pos] = buffer[pos];

          temp_pos++;
          pos++;
          length++;
         }

          temp_buffer[temp_pos] = '\0';

          if (length_error || alpha_error)
            ;
          else
            printf("%d %s\n",NUMBER_TOKEN,temp_buffer);

          break;
       }

       case 3 :
       {
         char temp_buffer [3];
         int issue_detected = 0;
         int comment_detected = 0;

         if (buffer[pos] == '<')
         {
          if (buffer[pos + 1] == '>')
          {
            strcpy(temp_buffer,"<>");
            pos += 2;
          }
          else if (buffer[pos + 1] == '=')
          {
            pos += 2;
            strcpy(temp_buffer,"<=");
          }
          else
          {
            strcpy(temp_buffer,"<");
            pos++;
          }
         }
        else if (buffer[pos] == '/')
        {
           if (buffer[pos + 1] != '*')
           {
             strcpy(temp_buffer,"/");
             pos++;
           }
           else
           {
             pos += 2;
             comment_detected = 1;
             while (1)
             {
              if (buffer[pos] == '*' && buffer[pos + 1] == '/')
              {
                pos += 2;
                break;
              }
              pos++;
            }
          }
        }
        else if (buffer[pos] == '>')
        {
          if (buffer[pos + 1] != '=')
          {
            pos++;
            strcpy(temp_buffer,">");
          }
          else
          {
            strcpy(temp_buffer,">=");
            pos += 2;
          }
        }
        else if (buffer[pos] == ':')
        {
          if (buffer[pos + 1] != '=')
          {
            issue_detected = 1;
            pos++;
          }
          else
          {
            strcpy(temp_buffer,":=");
            pos += 2;
          }
        }
        else
        {
          temp_buffer[0] = buffer[pos];
          temp_buffer[1] = '\0';
          pos++;

          if (!checkSymbol(symbols,temp_buffer))
              issue_detected = 1;
        }

        if (!issue_detected && !comment_detected )
            printf("%s %d\n",temp_buffer,findSymbolToken(temp_buffer,symbols));
        if (issue_detected)
            printf("Error : Invalid Symbol\n");


        break;
     }
    }
 }
   return 0;
}
