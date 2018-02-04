/* -----------------------------------------------------------------------
 * Author: Jonathan Grocott
 * Description: Random tester for quiz.
 * File Name: testme.c
 * Date Created: 2/3/2018
 * -----------------------------------------------------------------------*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define CHAR_MAX 95
#define STRING_MAX 5

char *randomString; 

char inputChar()
{
    // TODO: rewrite this function
	// Return an ASCII char from 32 (space) to 126 (~) 
    return (char)((rand()%CHAR_MAX) + 32);

}

char *inputString()
{
    // TODO: rewrite this function
    // Generate a string of 5 chars and null terminator
    randomString = malloc(5);
	char wordToScramble[5] = "reset";

	// Loop the length of the word reset and scramble them 
	int i;
	for(i = 0; i < 5; i++){
		randomString[i] = wordToScramble[rand() % 5];
	}
	randomString[5] = '\0'; // null terminator 

	return randomString;

}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) 
		state = 1;
    if (c == '(' && state == 1) 
		state = 2;
    if (c == '{' && state == 2) 
		state = 3;
    if (c == ' '&& state == 3) 
		state = 4;
    if (c == 'a' && state == 4) 
		state = 5;
    if (c == 'x' && state == 5) 
		state = 6;
    if (c == '}' && state == 6) 
		state = 7;
    if (c == ')' && state == 7) 
		state = 8;
    if (c == ']' && state == 8) 
		state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
	  free(randomString); 
      exit(200);
    }
	 free(randomString); 
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
