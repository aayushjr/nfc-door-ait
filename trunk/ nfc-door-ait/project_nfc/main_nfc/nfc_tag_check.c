/**
* @file      nfc_tag_check.c
* @author    Aayush
* @version   0.1
* @date      December 7, 2014
* @brief     Test code for NFC tag
*/

// Includes
#include "tag_protocol_test.h"
#include "util.h"
#include "sic4310.h"

// Need to send NFCDATA1 through SIC4310 module

void setup()
{
	//Setup SIC4310 and system core clock
	SIC4310_config();
  timebase_config(); 
}

int main(void)
{
	char tag[20];
	int i = 0;
	setup();
	
	while (1)
	{
			if (SIC4310_available()) 
			{
				
					i = 0;
					do {
						tag[i++] = SIC4310_read();
					} while(SIC4310_available());
					tag[i] = 0;
			}
			if(validate_tag(tag))
			{
				SIC4310_write("Valid Data Received");
			}
			else
			{
				SIC4310_write("Invalid Data");
			}
			tag[0] = 0;
	}		
	
}