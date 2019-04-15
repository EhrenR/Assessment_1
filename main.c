#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int eX (int a, int b);
int dC (int a, int b);

int main()
{
   int fill = 0; //between -25 & 25
   char alphabet[24]; //array of the alphabet
   for(int i = 97; i<123; i++) //filling alphabet array using ASCII chars
   {
       char c = i;
       alphabet[fill] = c;
       printf("%c\n", alphabet[fill]);
       fill += fill;
       
   }
   //int key = rand()%26; //key is a random number between 0-26
   int key = 1;
   return 0;
}

int eX (int a, int b)
{
    int encryption = (a+b)*(%26);
    if (encryption < 0)
    {
        encryption += 26;
    }
    return encryption;
}

int dC (int a, int b)
{
    int decryption = (a-b)*(%26);
    if (decryption < 0)
    {
        decryption += 26;
    }
    return decryption;
}