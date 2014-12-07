/**
* @file      protocol.c
* @author    Sunny
* @version   1.0
* @date      December 7, 2014
* @brief     protocol check for passcode.
*/

/* Includes -----------------------------------------------------------------------*/
#include "protocol.h"
#include<string.h>

/* Private function prototypes ----------------------------------------------------*/
/* Private functions --------------------------------------------------------------*/


int checktag(char *string)
{
	char buf2[3];
	
	uint8_t length = (unsigned)strlen(string);
	if (length != 6)
		return 0;
	strncpy(buf2, string, 3);
	if (strcmp(buf2,"KEY") == 0)
	{
			strncpy(buf2, string+3, 3);
		if(strcmp(buf2,"456") == 0)
			return 2;
		else if (strcmp(buf2,"123") == 0)
		{ 
			return 1;
		}
		else 
			return 0;
			
	}
	else
		return 0;
	
}



