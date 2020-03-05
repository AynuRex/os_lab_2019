#include "revert_string.h"
#include "../swap/swap.h"

void RevertString(char *str)
{
    int len=0;
    while(str[len]!='\0')
    {
        len++;
    }    
    for(int i=0;i<len/2;i++)
    {        
        Swap( str+i ,str+len -i- 1);
    }

	// your code here

}

