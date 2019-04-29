/*
- R E A D  M E -

This program uses a .txt file to read/write data. Each type of data is stored in an array or char.
The task selection is then performed by a switch statement and the appropriate function is run. Each function converts the message (and key if appropriate) to ASCII for computation, and back to text before printing.
NOTE:
Every function is a pointer which returns a static char array in order for the input/output to be read/printed.
The output is then both printed to the terminal and appended to the .txt file, then the file is closed and the program ends.

- INPUTTING TASK, KEY, AND MESSAGE IN THE .TXT FILE -

  o Line 1 = the task: Enter a 'T' followed by the task number you wish to use.
    E.g: "T1"

  o Line 2 = the key: No format specifier is needed before the key. Simply enter the key as-is. The key can be a number (rotation cipher), or a string of letters (substitution cipher)
    E.g: "1"
    E.g: "QWERTYUIOPASDFGHJKLZXCVBNM"
    If doing rotation cipher attack, simply leave line 2 empty

  o Line 3 = the message: Enter a '#' followed by the message you wish to encrypt/decrypt.
    E.g: "#PLEASE GET MILK AT THE SHOPS"

  o NOTE: Ensure you manually clear the output of the .txt file between each task.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

///////////////// F U N C T I O N  D E F I N I T I O N S ////////////////////

/*
  - Rotation cipher encryption
  - Recieves the key (key[]) and the message to be encrypted (rotEnc[])
  - Returns static char array encMsg[]
  - Message can only be a max of 1001 chars long
*/
char *taskOne(char key[], char rotEnc[]);

/*
  - Rotation cipher decryption
  - Recieves the key (key[]) and the message to be decrypted (rotDec[])
  - Returns static char array encMsg[]
  - Message can only be a max of 1001 chars long
*/
char *taskTwo(char key[], char rotDec[]);

/*
  - Substitution cipher encryption
  - Recieves alphabet key (key[]) and message to be encrypted (subEnc[])
  - Returns static char array encMsg[]
  - Mssage can only be a max of 1001 chars long
*/
char *taskThree(char key[], char subEnc[]);

/*
  - Substitution cipher decryption
  - Recieves alphabet key (key[]) and message to be decrypted (subEnc[])
  - Returns static char array decMsg[]
  - Message can only be a max of 1001 chars long
*/
char *taskFour(char key[], char subDec[]);

/*
  - Rotation cipher attack (brute force)
  - Recieves message to be decrypted (subDec[])
  - Returns static char array decMsg[]
  - Message can only be a max of 1001 chars long
  - For some reason if the last char is not a letter, sometimes it prints junk chars after
*/
char *taskFive(char rotDecTxt[]);

////////////////////////////////////////////////////////////////////////////////////////////////

FILE *file; //Assigns a pointer to the file. Global so all functions can write output to it

int main()
{
  //fileMsg: Stores the message to encrypt/Decrypt from .txt file
  //fileKey: Stores the key from .txt file
  //menu: Stores number of what task to perform as a char
  //whiteTest: Checks if a new line is reached
  char fileMsg[1000], fileKey[25], menu, whiteTest;
  int l = 0, m = 0, o = 0; //For if/else condition - selects which variable to store data in
  int c; //Var to check if end of file is reached
  char *one, *two, *three, *four, *five, *six; //Pointers will be asssigned for each task function in order to return the result
  file = fopen("input.txt", "a+"); //Names the file and opens it for reading and appending ("+a")

  //This block of code reads from the .txt file and stores it in each appropriate variable
  if (file != NULL) //Checking to see if the .txt file actually contains any data
  {
  while ((c = fgetc(file)) != EOF) //Loops until it has reached the end of the file
    {
      if (l == 0)
      {
        menu = fgetc(file);
        l = 1; //Increments l so the if() statement does not run again
      }

      else if(m == 0)
      {
        for(int x = 0; x < 25; x++)
        {
          whiteTest = fgetc(file);
          if (whiteTest == '\n' || whiteTest == '\0') //If the char is a new line or terminator...
          {
            x = 26; //Increments x so loop exits
            m = 1; //Increments m so the if() statement does not run again
          }
          else
          {
            fileKey[x] = whiteTest;
          }
        }
      }
      else if (o == 0)
      {
        for (int x = 0; x < 1001; x++)
        {
          whiteTest = fgetc(file);
          if (whiteTest == '\n' || whiteTest == '\0')
          {
            x = 1001; //Increments x so loop exits
            o = 1; //Increments o so the if() statement does not run again
          }
          else
          {
            fileMsg[x] = whiteTest;

          }
        }
      }
    }
  }
  else
  {
    printf("ERROR: File cannot be read"); //Prints this error if no data is present in the .txt file
  }

  printf("Message is:\n\n");
  for (int x = 0; x < strlen(fileMsg); x++) //Loop prints the message from the .txt file to terminal
  {
        printf("%c", fileMsg[x]);
  }

  //This block is the task selection menu
  int task = menu - '0'; //Converts a char (in this case task) to an integer. We need this to then use as the switch statement below
  switch(task) //Determines what task to run based on the first line in the .txt file
  {
    case 1 :
      printf("\n\nRunning task 1 - Rotation Encryption...\n");
      one = taskOne(fileKey, fileMsg); //Runs task 1 as a function and returns corresponding message... The same goes for every other case
      break;
    case 2 :
      printf("\n\nRunning task 2 - Rotation Decryption...\n");
      two = taskTwo(fileKey, fileMsg);
      break;
    case 3 :
      printf("\n\nRunning task 3 - Substitution Encryption...\n");
      three = taskThree(fileKey, fileMsg);
      break;
    case 4 :
      printf("\n\nRunning task 4 - Substitution Decryption...\n");
      four = taskFour(fileKey, fileMsg);
      break;
    case 5 :
      printf("\n\nRunning task 5 - Rotation Attack (brute force)...\n");
      five = taskFive(fileMsg);
      break;
    default :
      printf("\n\nERROR: Please enter a number between 1-5 to select a task");
  }

  fclose(file); //closes .txt file
  return 0;
}

///////////////////////////// F U N C T I O N  B O D Y S //////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

char *taskOne(char key[], char rotEnc[])
{
  static char encMsg[1000]; //Array that final message is stored in for return
  //i: Initialised at 65 for ASCII filling
  //ascMsg[]: Stores ASCII version of meessage
  //ascKey[]: Stores ASCII version of key
  //eX: Encryption var for calculation
  int i = 65, ascMsg[1000], ascKey[25], eX;
  int numKey = atoi(key); //Converts char to int
  for (int x = 0; x <= 24; x++) //Fills an array with ASCII values for A-Z
  {
    ascKey[x] = i;
    i++;
  }
  printf("Encrypted message is:\n\n");
  fprintf(file, "\nEncrypted message is:\n\n"); //Prints to .txt file

  for (int x = 0; x < strlen(rotEnc); x++) //Loops through the length of the message with strlen()
  {
    ascMsg[x] = rotEnc[x]; //Converts char to ASCII and stores in ascMsg[]
    if(ascMsg[x] < 65 || ascMsg[x] > 90) //If the message contains white space, do nothing and keep it
    {
      printf("%c", rotEnc[x]);
      fprintf(file, "%c", rotEnc[x]);
    }
    else
    {
    if ((ascMsg[x] + ascKey[numKey]) < 0) //If the calculation is negative...
    {
      eX = (((ascMsg[x] + ascKey[numKey] + 26)) %26) + 65; //... Add 26 to make +ve without impacting result
    }
    else //Otherwise just compute normally
    {
      eX = ((ascMsg[x] + ascKey[numKey]) %26) + 65; //Encryption for each letter in ASCII
    }
    encMsg[x] = eX; //Converts ASCII to char and stores it in encMsg[]
    printf("%c", encMsg[x]); //Prints the encrypted message to the terminal
    fprintf(file, "%c", encMsg[x]);
    }
  }
  return encMsg;
}

char *taskTwo(char key[], char rotDec[])
{
  static char decMsg[1000]; //Array that final message is stored in for return
  //i: Initialised at 65 for ASCII filling
  //ascMsg[]: Stores ASCII version of meessage
  //ascKey[]: Stores ASCII version of key
  //dC: Decryption var for calculation
  int i = 65, ascMsg[1000], ascKey[25], dC;
  int numKey = atoi(key); //Converts char to int
  for (int x = 0; x <= 24; x++) //Fills an array with ASCII values for A-Z
  {
    ascKey[x] = i;
    i++;
  }
  printf("Decrypted message is: \n\n");
  fprintf(file, "\nDecrypted message is:\n\n"); //Prints to .txt file

  for (int x = 0; x < strlen(rotDec); x++)
  {
    ascMsg[x] = rotDec[x]; //Converts char to ASCII and stores in ascMsg[]
    if (ascMsg[x] < 65 || ascMsg[x] > 90) //If the message contains white space, do nothing and keep it
    {
      printf("%c", rotDec[x]);
      fprintf(file, "%c", rotDec[x]);
    }
    else
    {
      if ((ascMsg[x] - ascKey[numKey]) < 0) //If the calculation is negative...
      {
        dC = (((ascMsg[x] - ascKey[numKey] + 26)) %26) + 65; //... Add 26 to make +ve without impacting result
      }
      else //Otherwise just compute normally
        {
              dC = ((ascMsg[x] - ascKey[numKey])%26) + 65;
        }
        decMsg[x] = dC;
        printf("%c", decMsg[x]);
        fprintf(file, "%c", decMsg[x]);
    }
  }
  return decMsg;
}

char *taskThree(char key[], char subEnc[])
{
  static char encMsg[1000];
  int ascMsg[1000], ascKey[25]; //Arrays to store ASCII versions of the message and key from subEnc[] and key[] respectively
  printf("Encrypted message is:\n\n");
  fprintf(file, "\nEncrypted message is:\n\n");

  for (int x = 0; x <= 24; x++) //Loop converts key[] (char data type) into ASCII and fills the array
  {
    ascKey[x] = key[x];
  }
  for (int x = 0; x < strlen(subEnc); x++) //Encrypts each ASCII char one-by-one. Loops until the end of the array is reached using streln()
  {
    ascMsg[x] = subEnc[x]; //Loop converts subEnc[] (char data type) into ASCII and fills the array
    int keyIndex = subEnc[x] - 'A'; // Gets the index of the char to encrypt
    if (ascMsg[x] < 65 || ascMsg[x] > 90) //If the char is not a letter...
    {
      printf("%c", subEnc[x]); //...Do not encrypt the char
      fprintf(file, "%c", subEnc[x]);
    }
    else
    {
      encMsg[x] = ascKey[keyIndex]; //Places the correct encrypted char using the index into encMsg[]. encMsg is of type char, so it converts the ASCII to char
      printf("%c", encMsg[x]); //Prints to terminal
      fprintf(file, "%c", encMsg[x]); //Prints to .txt file
    }
  }
  return encMsg;
}

char *taskFour(char key[], char subDec[])
{
  static char decMsg[1000];
  int ascMsg[1000], ascKey[25]; //Arrays to store ASCII versions of the message and key from subEnc[] and key[] respectively
  printf("Decrypted message is:\n\n");
  fprintf(file, "\nDecrypted message is:\n\n");

  for (int x = 0; x <= 24; x++) //Loop converts key[] (char data type) into ASCII and fills the array
  {
    ascKey[x] = key[x];
  }
  for (int x = 0; x < strlen(subDec); x++) //Decrypts each ASCII char one-by-one. Loops until the end of the array is reached using streln()
  {
    ascMsg[x] = subDec[x]; //Loop converts subDec[] (char data type) into ASCII and fills the array
    const char *keyIndexPointer = strchr(key, subDec[x]); //strchr() returns the pointer to the first occurrence of the char in the array...
    int keyIndex = keyIndexPointer - key; //Index is found using pointer arithmetic
    if (ascMsg[x] < 65 || ascMsg[x] > 90) //If the char is not a letter...
    {
      printf("%c", subDec[x]); //...Do not decrypt the char
      fprintf(file, "%c", subDec[x]);
    }
    else
    {
      decMsg[x] = 'A' + keyIndex; //Base letter + index of where the char was found.
      printf("%c", decMsg[x]); //Prints to terminal
      fprintf(file, "%c", decMsg[x]); //Prints to .txt file
    }
  }

  return decMsg;
}

char *taskFive(char rotDecTxt[])
{
  static char decMsg[1000];
  int lTally[25]; //Stores tallies of chars from message
  int ascMsg[1000]; //Array to store message in ASCII
  int key;
  int i = 65, ascKey[25], dC;

  for (int x = 0; x <= 25; x++)
  {
    lTally[x] = 0; //Initialises each value to 0
  }

  for (int x = 0; x < strlen(rotDecTxt); x++)
  {
    ascMsg[x] = rotDecTxt[x]; //Converts message to ASCII
    switch(ascMsg[x]) //Switch statment tallies how many times each letter appears in the message
    {
      case 65:
        lTally[0] += 1;
        break;
      case 66:
        lTally[1] += 1;
        break;
      case 67:
        lTally[2] += 1;
        break;
      case 68:
        lTally[3] += 1;
        break;
      case 69:
        lTally[4] += 1;
        break;
      case 70:
        lTally[5] += 1;
        break;
      case 71:
        lTally[6] += 1;
        break;
      case 72:
        lTally[7] += 1;
        break;
      case 73:
        lTally[8] += 1;
        break;
      case 74:
        lTally[9] += 1;
        break;
      case 75:
        lTally[10] += 1;
        break;
      case 76:
        lTally[11] += 1;
        break;
      case 77:
        lTally[12] += 1;
        break;
      case 78:
        lTally[13] += 1;
        break;
      case 79:
        lTally[14] += 1;
        break;
      case 80:
        lTally[15] += 1;
        break;
      case 81:
        lTally[16] += 1;
        break;
      case 82:
        lTally[17] += 1;
        break;
      case 83:
        lTally[18] += 1;
        break;
      case 84:
        lTally[19] += 1;
        break;
      case 85:
        lTally[20] += 1;
        break;
      case 86:
        lTally[21] += 1;
        break;
      case 87:
        lTally[22] += 1;
        break;
      case 88:
        lTally[23] += 1;
        break;
      case 89:
        lTally[24] += 1;
        break;
      case 90:
        lTally[25] += 1;
        break;
      default:
        break;
    }
  }

  for (int x = 0; x <= 24; x++) //Fills an array with ASCII values for A-Z
  {
    ascKey[x] = i;
    i++;
  }

  for (int y = 0; y <= 25; y++) //Loop decrypts message using each key and displays them all (brute force method). Everything in this loop is the same as in the function *taskTwo
  {
    key = lTally[y];
    printf("\n\nPotential decryption using key %d:\n\n", y);
    fprintf(file, "\n\nPotential decryption using key %d:\n\n", y);
    for (int x = 0; x < strlen(rotDecTxt); x++)
    {

      if (ascMsg[x] < 65 || ascMsg[x] > 90)
      {
          printf("%c", rotDecTxt[x]);
          fprintf(file, "%c", rotDecTxt[x]);
      }
      else
      {
        if ((ascMsg[x] - ascKey[key]) < 0)
        {
          dC = (((ascMsg[x] - ascKey[key] + 26)) %26) + 65;
        }
        else
          {
                dC = ((ascMsg[x] - ascKey[key])%26) + 65;
          }
          decMsg[x] = dC;
          printf("%c", decMsg[x]);
          fprintf(file, "%c", decMsg[x]);
      }
    }
  }

  return decMsg;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
