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
#include <stdio.h>
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
		int checkchange = 0;
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
						checkchange = 1;
        }
				if (checkchange)
				{
					if (checktag(buf)== 2 && Get_State() == 0)
					{
						SIC4310_write("Door Auto-unlock");
						changePulse_fcn(OPEN);
						delay(15000);               // 15s delay for a person to get in and close the door
						changePulse_fcn(CLOSE);
					}
					else if (checktag(buf)==1 && Get_State() == 0)
					{
					
						SIC4310_write("Door unlock");
						changePulse_fcn(OPEN);
					}
					else if(checktag(buf)==1)
					{
						
						SIC4310_write("Door lock");
						changePulse_fcn(CLOSE);
					}
					checkchange = 0 ;
				}
		
				delay(1000);
				buf[0] = 0;
				
				
    }
}
