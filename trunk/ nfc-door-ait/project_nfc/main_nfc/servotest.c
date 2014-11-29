
#include "servolib.h"
#include "util.h"

void setup()
{
	Servo_fcn(); //Setup Servo
}

int main(void)
{
	setup();
	while (1)
	{
		changePulse_fcn(96000);
		delay(5000);
		changePulse_fcn(0);
		delay(5000);
	}		
	
}