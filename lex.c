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

// if word is a reserved word, return token number, else return -1
int findReservedToken(char *word, TokenType *reservedWords)
{
  for (int i = 0; i < RESERVED_WORDS_COUNT; i++)
  {
      if (strcmp(reservedWords[i].symbol,word) == 0)
          return reservedWords[i].token;
  }

  return -1;
}

// if symbol is valid return 1, else return 0
int checkSymbol(TokenType * symbols, char *str)
{
    for (int i = 0; i < SYMBOL_COUNT; i++)
    {
        if (strcmp(symbols[i].symbol,str) == 0)
            return 1;
    }

    return 0;
}

// if word is a valid reserved word, return 1, else return 0;
int checkIfReservedWord(char *word, TokenType *reservedWords)
{
  for (int i = 0; i < RESERVED_WORDS_COUNT; i++)
  {
      if (strcmp(reservedWords[i].symbol,word) == 0)
          return 1;
  }

  return 0;
}

// finds if token number is a single or double digit number
int find_token_digits(int token)
{
  if (token / 10 == 0)
    return 1;
  else return 2;
}

// places token in list
void place_token_in_list(char *token_list, int token, int *token_position, char *temp_buffer)
{
  int token_digits = find_token_digits(token);
  char nums[10]= "0123456789";
  char c;
  int first_digit, second_digit;

  first_digit = token % 10;

  if (token_digits == 2)
    second_digit = (token /10) % 10;

  if (token_digits == 1)
  {
  token_list[token_position[0]] = nums[0+first_digit];
  token_position[0]++;
  }

  else if (token_digits == 2)
  {
    token_list[token_position[0]] = nums[0+second_digit];
    token_position[0]++;
    token_list[token_position[0]] = nums[0+first_digit];
    token_position[0]++;
  }

  token_list[token_position[0]] = ' ';
  token_position[0]++;

  // for inserting identifiers
  if (temp_buffer != NULL)
  {
    for (int i = 0; i < strlen(temp_buffer); i++)
    {
      token_list[token_position[0]] = temp_buffer[i];
      token_position[0]++;
    }

    token_list[token_position[0]] = ' ';
    token_position[0]++;
  }


  return;
}

int main(int argc, char **argv)
{
    TokenType * symbols = (malloc(sizeof(TokenType) * SYMBOL_COUNT));
    TokenType * reservedWords = (malloc(sizeof(TokenType) * RESERVED_WORDS_COUNT));
    FILE * file_ptr = fopen("testertest.txt", "r");
    char buffer [500];
    char token_list[500];
    int count = 0;
    int token_position[1];

    token_position[0] = 0;
    initSymbols(symbols);
    initReserved(reservedWords);

  // read in file into buffer array
   while (1)
   {
     char c = fgetc(file_ptr) ;
     if ( c == EOF )
      break ;

      buffer[count] = c;
      count++;
   }

   buffer[count] = '\0';
   int pos = 0;
   int category = 0;

   // Continue iterating through array until null value is encountered
   while (pos != count)
   {
     // if first character of unit is alphabetic
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
       // first character of unit is a letter
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
           // current word is valid length and next character is digit or alpha
           if (temp_pos < 11 && (isdigit(buffer[pos]) ||  isalpha(buffer[pos])))
           {
             temp_buffer[temp_pos] = buffer[pos];
             pos++;
             temp_pos++;
           }
           // current word is of invalid length
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
           // a character is encountered which marks the end of the unit
           else if (!isalpha(buffer[pos]) && !isdigit(buffer[pos]) &&  more_than_11 == 0)
           {

             temp_buffer[temp_pos] = '\0';
             if (checkIfReservedWord(temp_buffer,reservedWords))
             {
               int token = findReservedToken(temp_buffer, reservedWords);
               place_token_in_list(token_list, token, token_position, NULL);

               printf("%s     %d\n", temp_buffer, token );
               break;
             }
             else
             {
               place_token_in_list(token_list, IDENTIFIER_TOKEN, token_position,temp_buffer);
               printf("%s       %d\n", temp_buffer, IDENTIFIER_TOKEN);
               break;
             }
           }
         }
       }
     }
   }

  printf("Token List:\n");
  token_list[token_position[0]-1] = '\0';
  printf("%s", token_list);


  return 0;
}
