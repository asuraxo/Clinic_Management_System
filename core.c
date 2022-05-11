/*
*****************************************************************************
                        Assignment 1 - Milestone 3
Full Name  : WAI CHUNG, SO 
Student ID#: 147446215
Email      : wso8@myseneca.ca
Section    : NFF

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "core.h"

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//
// Copy your work done from Milestone #2 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
//

//Get user input & check if integer
int inputInt(void)
{
    char newLine='x';
    int value=0;
    int check=1;

    do
    {
        scanf("%d%c", &value, &newLine);
        if(newLine=='\n')
        {
            return value;
            check=0;
        }

        else
        {
            printf("Error! Input a whole number: ");
            clearInputBuffer(); 
        }
    } while ( check==1 );
    return value;
}

//Get user input & check if positive integer
int inputIntPositive (void)
{
    int value=0;

    do
    {
        value=inputInt();
        if(value>=0)
        {
            return value;
            break;
        }
        else 
        {
            printf("ERROR! Value must be > 0: ");
        }
    } while (value<0);
    return value;
}

//Get user input & check if is integer in range
int inputIntRange(int lowerBound, int upperBound)
{
    int value;

    do
    {
        value=inputInt();

        if(lowerBound<=value && value<=upperBound)
        {
            return value;
            //clearInputBuffer(); //tobe deleted
            break;
        }

        else 
        {
            printf("ERROR! Value must be between %d and %d inclusive: ", lowerBound, upperBound);
        }
    } while (value<lowerBound || upperBound<value);
    return value;
}

//Get user input & check if is Char on list
// char inputCharOption(const char listOfChar[])
// {
//     char userInput;
//     int i=0;

//     do
//     {
//         scanf(" %c", &userInput);
//         clearInputBuffer(); 

//         i=0;
//         while (listOfChar[i]!='\0')
//         {
//             if (listOfChar[i]==userInput)
//             {
//                 return userInput;
//                 break;
//             }
//             i++;
//         }
//         printf("ERROR: Character must be one of [%s]: ", listOfChar);
//     } while (listOfChar[i]!=userInput);

//     return userInput;
// }

// char inputCharOption(const char listOfChar[])
// {
//     char userInput[5];
//     int i=0;

//     do
//     {
//         scanf(" %s", &*userInput);
//         clearInputBuffer(); 

//         i=0;
//         if (userInput[1]=='\0')
//         {
//             while (listOfChar[i]!='\0')
//             {
//                 if (listOfChar[i]==userInput[i])
//                 {
//                     return userInput[0];
//                     break;
//                 }
//                 i++;
//             }
//         }
//         else
//         {
//             i++;
//         }
//         printf("ERROR: Character must be one of [%s]: ", listOfChar);
//     } while (listOfChar[i]!=userInput[0]);

//     return userInput[0];
// }

char inputCharOption(const char listOfChar[])
{
    char userInput[5];
    int i=0;
    int checkValue=0;

    do
    {
        i=0;
        scanf(" %s", &*userInput);
        clearInputBuffer(); 
        if (userInput[1]=='\0')
        {
            while (listOfChar[i]!='\0')
            {
                if (listOfChar[i]==userInput[0])
                {
                    checkValue=1;
                    return userInput[0];
                    break;
                }
                i++;
            }
        }
        printf("ERROR: Character must be one of [%s]: ", listOfChar);
    } while (checkValue==0);

    return userInput[0];
}



//Get user input & check if fulfil String length
void inputCString(char charString[], int min, int max)
{
    int i, validity=1;
    do
    {
        scanf("%[^\n]", &*charString);
        clearInputBuffer();
    

        i=0;
        while(charString[i]!='\0')
        {
            i++;
        }

        if (min==max && i!=min)
        {
            printf("ERROR: String length must be exactly %d chars: ", min);
        }

        else if (i<min)
        {
            printf("ERROR: String length must be between %d and %d chars: ", min, max);
        }

        else if (i>max)
        {
            printf("ERROR: String length must be no more than %d chars: ", max);
        }

        else 
        {
            //printf("charString[%d]=%c\n", i, charString[i]);
            validity=0;
        }  
    }while(validity==1);
    
};

void inputCStringPhone(char charString[], int min, int max)
{
    int i, validity=1;
    do
    {
        scanf("%[^\n]", &*charString);
        clearInputBuffer();
    

        i=0;
        while(charString[i]!='\0')
        {
            i++;
        }

        if (min==max && i!=min)
        {
            printf("Invalid 10-digit number! Number: ");
        }

        // else if (i<min)
        // {
        //     printf("ERROR: String length must be between %d and %d chars: ", min, max);
        // }

        // else if (i>max)
        // {
        //     printf("ERROR: String length must be no more than %d chars: ", max);
        // }

        else 
        {
            //printf("charString[%d]=%c\n", i, charString[i]);
            validity=0;
        }  
    }while(validity==1);
    
};


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

//Get user input & isplay the phone numbers as formatted
void displayFormattedPhone(const char charString[])
{
    int i=0, counter=0;

    if(charString==NULL)
    {
        printf("(___)___-____");
    }

    else
    {
        while(charString[i]!='\0')
        {
            if(isdigit(charString[i]))
            {
                counter++;
            }
            i++;
        }

        if (counter==10)
        {
            printf("(");
            for(i=0;i<counter;i++)
            {
                if(i==2)
                {
                    printf("%c)", charString[i]);
                }

                else if(i==5)
                {
                    printf("%c-", charString[i]);
                }

                else
                {
                    printf("%c", charString[i]);
                }
            }
        }

        else
        {
            printf("(___)___-____");
        }
    }
};

int findLastDayOfMonth(int year, int month)
{
    int lastDayOfMonth=0;
    
    if (month==1||month==3||month==5||month==7||
        month==8||month==10||month==12)
        {
            lastDayOfMonth=31;
        }

    else if (month==2||month==4||month==6||month==9||month==11)
        {
            if (month==2)
            {
                if((year%4==0) && ((year%400==0) || (year%100!=0)))
                {
                    lastDayOfMonth=29;
                }
                else
                {
                    lastDayOfMonth=28;
                }
            }
            else
            {
                    lastDayOfMonth=30;
            }
        }
    
    return lastDayOfMonth;
}
