/**
* @file      protocol.c
* @author    Sunny
* @version   1.0
* @date      December 7, 2014
* @brief     protocol check for passcode.
*/

/* Includes -----------------------------------------------------------------------*/
#include "tag_protocol_test.h"
#include<string.h>

/* Private function prototypes ----------------------------------------------------*/
/* Private functions --------------------------------------------------------------*/


int validate_tag(char *string)
{
		
	uint8_t length = (unsigned)strlen(string);
	if (length != 8)
		return 0;
	
	if (strcmp(string,"NFCDATA1") == 0)
	{
			return 1;
	}
	else
		return 0;
	
}



