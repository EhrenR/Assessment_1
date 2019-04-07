#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
   int key, fill = 0; //between -25 & 25
   char alphabet[24];
   for(int i = 97; i<123; i++) //filling alphabet array using ASCII chars
   {
       char c = i;
       alphabet[fill] = c;
       printf("%c\n", alphabet[fill]);
       fill += fill;
       
   }

return 0;
}

