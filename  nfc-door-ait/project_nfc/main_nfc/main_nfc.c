/**
* @file      test_sic4310.c
* @author    Supachai Vorapojpisut
* @version   0.1
* @date      November 4, 2014
* @brief     Test code for 
*/

/* Includes -----------------------------------------------------------------------*/
#include "sic4310.h"
#include "util.h"
#include <string.h>
#include "protocol.h"
#include "servolib.h"

/* Private types ------------------------------------------------------------------*/
/* Private constants --------------------------------------------------------------*/
/* Private macro ------------------------------------------------------------------*/
/* Private variables --------------------------------------------------------------*/
/* Private function prototypes ----------------------------------------------------*/
/* Private functions --------------------------------------------------------------*/


/**
* @brief    Check and accept value from SIC4310 module, then echo back
*/
int main()
{
		char buf[20];
		int i = 0;
    //SIC4310_Struct msg;
    
    SIC4310_config();
    timebase_config();
		Servo_fcn();
		//strcpy(buf,"KEY123");
    
		while(1){
        if (SIC4310_available()) 
				{
					
						i = 0;
						do {
							buf[i++] = SIC4310_read();
						} while(SIC4310_available());
						buf[i] = 0;
        }
				
				if (checktag(buf))
				{
					SIC4310_write("true");
					changePulse_fcn(96000);
				}
				else
				{
					SIC4310_write("false");
					changePulse_fcn(0);
				}
				delay(1000);
				buf[0] = 0;
				
				
    }
}
