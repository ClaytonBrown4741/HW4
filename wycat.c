/*
* wycat.c
* Author: Clayton Brown
* Date: Feb 15, 2023
*
* COSC 3750, Homework 4
*
* This is an altered version of that cat utility, and behaves
* in a similar way. This code takes any number of files and
* then prints out the contents to stdout for the user to read.
* Additionally, it also allows the user to input their own
* text using stdin should the wish to do so.
*
*/

// Include necessary packages
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//Begin the main class
int main(int argc, char **argv, char **envp)
{
  // Define/initialize my variables
  int i;
  char inputptr[4000];
  int rtn=0;
  FILE *fileptr;
  int closingValue;
  int rtnChecker;

  //  If there are no arguments given, then just take input from stdin
  if(argc==1)
  {
    rtn=fread(inputptr,1,4096,stdin);
    rtnChecker=fwrite(inputptr,1,rtn,stdout);
    // Check to make sure the function wrote correctly to stdout
    if(rtnChecker!=rtn)
    {
      fprintf(stderr, "error occured while writing from stdin");
    }
  }

  // Declare a for loop which will go through all arguments
  for(i=1; i < argc; i++)
  {
    // If the argument is a dash, read from stdin
    if(strcmp(argv[i], "-") == 0)
    {
      rtn=fread(inputptr,1,4096,stdin);
      rtnChecker=fwrite(inputptr,1,rtn,stdout);
      // Check to make sure fwrite  worked correctly
      if(rtnChecker!=rtn)
      {
        fprintf(stderr, "error occured while writing from stdin");
      }
    } 
    // If the input is not a dash, check to see if it's a file
    else
    {
      fileptr=fopen(argv[i], "r");
      // If the file does not exist, notify the user and continue
      if(fileptr==NULL)
      {
        printf("wycat: %s: No such file exists.\n", argv[i]);
      }
      // If the file does exist, then read from it
      else
      {
      rtn=fread(inputptr,1,4096,fileptr);
        // If there is an error, notify the user
        if(rtn<4096)
	{
	  if(ferror(fileptr)){
	    fprintf(stderr, "error occured while reading %s \n", argv[i]);
	  }
	}
	
      // Close the file, and then see if it closed correctly
      closingValue=fclose(fileptr);
      if(closingValue!=0)
      {
        fprintf(stderr, "error occured while closing %s \n", argv[i]);
      }

      // Write the file to stdout and make sure no errors occured
      rtnChecker=fwrite(inputptr,1,rtn,stdout);
      if(rtnChecker!=rtn)
      {
	fprintf(stderr, "error occured while writing for %s \n", argv[i]);
      }
      }
    }
  }
}
